#pragma once
#include <afxwin.h>

#include <gl/GL.h>
#include <gl/GLU.h>

class GLWindow : public CWnd
{

private:
	CWnd * m_pHwnd				= nullptr;
	HDC		 m_hdc					= nullptr;
	HGLRC	 m_hglrc				= nullptr;
	int		 m_pixelFormat	= 0;
	CRect	 m_rect;
	CRect	 m_oldWnd;
	CRect	 m_originalRect;


public:
	UINT_PTR m_unpTimer;

	void oglInitialize();
	void oglCreate(const RECT &rRect, CWnd *pParent = nullptr);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDraw(CDC *pDC);
	DECLARE_MESSAGE_MAP();
};
