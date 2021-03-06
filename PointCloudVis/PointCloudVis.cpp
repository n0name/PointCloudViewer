// PointCloudVis.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "PointCloudVis.h"
#include "MainFrame.h"

#include "DataLoader.h"

// Global Application Instance
Application app;

static inline std::wstring LoadStr(HINSTANCE hInstance, int id)
{
	const size_t maxStrLen = 100;
	WCHAR tmp[maxStrLen] = { 0 };
	LoadStringW(hInstance, id, tmp, maxStrLen);
	return { tmp };
}

BOOL Application::InitInstance() {
	std::wstring mainFrameTitle = LoadStr(m_hInstance, IDS_APP_TITLE);
	MainFrame *pMainFrame = new MainFrame(mainFrameTitle);
	m_pMainWnd = pMainFrame;

	pMainFrame->ShowWindow(SW_SHOW);
	pMainFrame->UpdateWindow();
	return TRUE;
}

Application * Application::GetApplication()
{
	return &app;
}

void Application::LoadModel(const std::wstring & rFilePath)
{
	m_Model = Data::LoadFromDat(rFilePath);
}
