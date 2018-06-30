#pragma once
#include <string>
#include <afxwin.h>

struct MainFrame : public CFrameWnd
{
	CMenu m_Menu;
	MainFrame(const std::wstring &rTitle);

	void OnAbout();
	void OnExit();
	void OnLoadFile();

	DECLARE_MESSAGE_MAP()
};

struct AboutDlg : public CDialog
{
	AboutDlg(CWnd* pParentWnd = NULL);
};
