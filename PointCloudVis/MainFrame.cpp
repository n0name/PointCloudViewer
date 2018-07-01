#include "stdafx.h"
#include "MainFrame.h"

#include "resource.h"

#include "PointCloudVis.h"

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	ON_COMMAND(ID_FILE_LOAD, OnLoadFile)
	ON_COMMAND(IDM_ABOUT, OnAbout)
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
	AboutDlg *pAboutDlg = new AboutDlg();
	pAboutDlg->ShowWindow(SW_SHOW);
}

void MainFrame::OnExit()
{
	DestroyWindow();
}

void MainFrame::OnLoadFile()
{
	CString fileName;
	wchar_t* p = fileName.GetBuffer(MAX_PATH);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFile = p;
	ofn.nMaxFile = MAX_PATH;
	dlgFile.DoModal();
	fileName.ReleaseBuffer();

	std::wstring fn = p;
	Application::GetApplication()->LoadModel(fn);
}


AboutDlg::AboutDlg(CWnd * pParentWnd)
	: CDialog(IDD_ABOUTBOX, pParentWnd)
{
	Create(IDD_ABOUTBOX, pParentWnd);
}
