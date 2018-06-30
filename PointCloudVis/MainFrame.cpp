#include "stdafx.h"
#include "MainFrame.h"

#include "resource.h"

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	ON_COMMAND(ID_FILE_LOAD, OnLoadFile)
	ON_COMMAND(IDM_ABOUT, OnLoadFile)
	ON_COMMAND(IDM_EXIT, OnExit)
END_MESSAGE_MAP()


MainFrame::MainFrame(const std::wstring & rTitle)
{
	Create(NULL, rTitle.c_str());
	m_Menu.LoadMenuW(IDC_POINTCLOUDVIS);
	SetMenu(&m_Menu);
}

void MainFrame::OnAbout()
{
	/*AboutDlg dlg;
	dlg.ShowWindow(SW_SHOW);*/
	MessageBox(L"Testing");
}

void MainFrame::OnExit()
{
}

void MainFrame::OnLoadFile()
{
}


AboutDlg::AboutDlg(CWnd * pParentWnd)
	: CDialog(IDD_ABOUTBOX, pParentWnd)
{

}
