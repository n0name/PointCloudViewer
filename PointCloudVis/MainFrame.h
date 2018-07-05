#pragma once
#include <string>
#include <afxwin.h>
#include "GLProxy.h"

struct MainFrame : public CFrameWnd
{
	CMenu m_Menu;
	MainFrame(const std::wstring &rTitle);

	void OnAbout();
	void OnExit();
	void OnLoadFile();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	//GLProxy m_GLProxy;

	GLWindow m_GLWindow;
};

struct AboutDlg : public CDialog
{
	AboutDlg(CWnd* pParentWnd = NULL);
};
