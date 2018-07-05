#include "stdafx.h"
#include "GLWindow.h"
#include "PointCloudVis.h"
#include "DataModel.h"

BEGIN_MESSAGE_MAP(GLWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
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
	glTranslatef(0.0f, 0.0f, -m_camera.m_fZoom);
	glTranslatef(m_camera.m_fPosX, m_camera.m_fPosY, 0.0f);
	glRotatef(m_camera.m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_camera.m_fRotY, 0.0f, 1.0f, 0.0f);
}

void GLWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_camera.m_fLastX);
	int diffY = (int)(point.y - m_camera.m_fLastY);
	m_camera.m_fLastX = (float)point.x;
	m_camera.m_fLastY = (float)point.y;

	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		m_camera.m_fRotX += (float)0.5f * diffY;

		if ((m_camera.m_fRotX > 360.0f) || (m_camera.m_fRotX < -360.0f))
		{
			m_camera.m_fRotX = 0.0f;
		}

		m_camera.m_fRotY += (float)0.5f * diffX;

		if ((m_camera.m_fRotY > 360.0f) || (m_camera.m_fRotY < -360.0f))
		{
			m_camera.m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_camera.m_fZoom -= (float)0.1f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_camera.m_fPosX += (float)0.05f * diffX;
		m_camera.m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
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

inline void GLWindow::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// Model view
	glMatrixMode(GL_MODELVIEW);
}
