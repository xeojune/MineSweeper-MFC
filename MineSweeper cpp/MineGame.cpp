
// MineGame.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MineGame.h"
#include "MineGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMineGameApp

BEGIN_MESSAGE_MAP(CMineGameApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMineGameApp 생성

CMineGameApp::CMineGameApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMineGameApp 개체입니다.

CMineGameApp theApp;


// CMineGameApp 초기화

BOOL CMineGameApp::InitInstance()
{
	CWinApp::InitInstance();


	CMineGameDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

