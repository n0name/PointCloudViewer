#pragma once
#include <afxwin.h>

#include <gl/GL.h>
#include <gl/GLU.h>

class GLWindow : public CWnd
{
	struct GLCamera {
		float m_fPosX = 0.0f;    // X position of model in camera view
		float m_fPosY = 0.0f;    // Y position of model in camera view
		float m_fZoom = 10.0f;   // Zoom on model in camera view
		float m_fRotX = 0.0f;    // Rotation on model in camera view
		float m_fRotY = 0.0f;    // Rotation on model in camera view
		float m_fLastX = 0.0f;
		float m_fLastY = 0.0f;
	};


private:
	CWnd * m_pHwnd				= nullptr;
	HDC		 m_hdc					= nullptr;
	HGLRC	 m_hglrc				= nullptr;
	int		 m_pixelFormat	= 0;
	CRect	 m_rect;
	CRect	 m_oldWnd;
	CRect	 m_originalRect;

	GLCamera m_camera;

public:
	UINT_PTR m_unpTimer;

	void oglInitialize();
	void oglCreate(const RECT &rRect, CWnd *pParent = nullptr);
	void oglRenderScene();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};
