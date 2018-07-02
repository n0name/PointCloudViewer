#include "stdafx.h"
#include "GLWindow.h"

BEGIN_MESSAGE_MAP(GLWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	//ON_WM_MOUSEMOVE()
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
	glClearColor(0.1, 0.1, 0.12, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);
}

void GLWindow::OnDraw(CDC * pDC)
{
	// TODO: Camera
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

void GLWindow::OnTimer(UINT_PTR  nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		// Clear color and depth buffer bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw OpenGL scene
		// oglDrawScene();

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
