// PointCloudVis.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "PointCloudVis.h"
#include "MainFrame.h"

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




//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}


//LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(mhInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case ID_FILE_LOAD:
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	break;
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code that uses hdc here...
//		EndPaint(hWnd, &ps);
//	}
//	break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

