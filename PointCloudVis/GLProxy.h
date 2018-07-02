#pragma once

#include <afxwin.h>
#include "GLWindow.h"

struct GLProxy : public CWnd
{
	GLWindow m_GLWindow;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};
