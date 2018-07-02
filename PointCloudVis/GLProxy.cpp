#include "stdafx.h"
#include "GLProxy.h"

BEGIN_MESSAGE_MAP(GLProxy, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int GLProxy::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetWindowRect(rect);

	ScreenToClient(rect);
	m_GLWindow.oglCreate(rect, this);
	m_GLWindow.m_unpTimer = m_GLWindow.SetTimer(1, 1, 0);
	return 0;
}
