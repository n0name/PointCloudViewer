#include "stdafx.h"
#include "GLWindow.h"
#include "PointCloudVis.h"
#include "DataModel.h"

#include <cmath>

BEGIN_MESSAGE_MAP(GLWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

int GLWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	oglInitialize();

	return 0;
}

void GLWindow::oglInitialize()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,    // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,    // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	m_hdc = GetDC()->m_hDC;

	// Pixel format.
	m_pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, m_pixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	m_hglrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hglrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POINTS);
	glDepthFunc(GL_LEQUAL);
	glPointSize(5.0);

	// Send draw request
	OnDraw(NULL);
}

void GLWindow::OnDraw(CDC * pDC)
{
	glLoadIdentity();
	if (m_IsPerspective)
		glTranslatef(0.0f, 0.0f, -m_camera.m_fZoom);
	else
		glScalef(1/m_camera.m_fZoom, 1/m_camera.m_fZoom, 1/m_camera.m_fZoom);

	glRotatef(m_camera.m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_camera.m_fRotY, 0.0f, 1.0f, 0.0f);
	glTranslatef(-m_camera.m_fPosX, 0.0, m_camera.m_fPosY);

}

void GLWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	const int diffX = int(point.x - m_camera.m_fLastX);
	const int diffY = int(point.y - m_camera.m_fLastY);
	m_camera.m_fLastX = float(point.x);
	m_camera.m_fLastY = float(point.y);

	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		m_camera.m_fRotX += 0.5f * diffY;

		if ((m_camera.m_fRotX > 360.0f) || (m_camera.m_fRotX < -360.0f))
		{
			m_camera.m_fRotX = 0.0f;
		}

		m_camera.m_fRotY += 0.5f * diffX;

		if ((m_camera.m_fRotY > 360.0f) || (m_camera.m_fRotY < -360.0f))
		{
			m_camera.m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_camera.m_fZoom -= 0.1f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_camera.m_fPosX += 0.01f * diffX;
		m_camera.m_fPosY -= 0.01f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}

BOOL GLWindow::OnMouseWheel(UINT p1, short p2, CPoint p3)
{
	m_camera.m_fZoom -= 0.5f * p2 / abs(p2);
	return true;
}

void GLWindow::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'P':
		m_IsPerspective = !m_IsPerspective;
		SetupProjection(lastCx, lastCy);
		Invalidate();
		break;

	case VK_F4:
		// reset camera
		m_camera.m_fPosX = 0.0f;
		m_camera.m_fPosY = 0.0f;
		m_camera.m_fZoom = 10.0f;
		break;
	}

}

void GLWindow::oglCreate(const RECT & rRect, CWnd * pParent)
{

	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(DKGRAY_BRUSH));

	CreateEx(0, className, L"GLWindow",
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rRect, pParent, 0);

	m_oldWnd = rRect;
	m_originalRect = rRect;

	m_pHwnd = pParent;
}

void GLWindow::OnPaint() {
	ValidateRect(NULL);
}

void GLWindow::oglRenderScene()
{
	const Data::DataModel* model = Application::GetApplication()->GetModel();
	if (model == nullptr)
		return;

	glColor3f(0., 1., 0.);
	glBegin(GL_POINTS);
	for (const auto &feature : model->m_Features)
	{
		for (const auto &pt : feature->m_Points)
		{
			glVertex3f(float(pt.x), float(pt.y), float(pt.z));
			glColor3f(0., 1., 0.);
		}
	}

	glEnd();
}

void GLWindow::OnTimer(UINT_PTR  nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		// Clear color and depth buffer bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw OpenGL scene
		oglRenderScene();

		// Swap buffers
		SwapBuffers(m_hdc);

		break;
	}

	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void GLWindow::SetupProjection(int cx, int cy)
{
	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	if (m_IsPerspective)
	{
		gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);
	}
	else
	{
		const float aspect = (float)cx / (float)cy;
		const float bigger = cx > cy ? cx : cy;
		glOrtho(aspect * -1, aspect * 1, -1, 1, 0.01f, 200000.0f);
		//glOrtho(-cx / 2, cx / 2, -cy / 2, cy / 2, 0.01f, 200000.0f);
	}
	// Model view
	glMatrixMode(GL_MODELVIEW);

}

void GLWindow::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;
	SetupProjection(cx, cy);
	lastCx = cx; lastCy = cy;
}
