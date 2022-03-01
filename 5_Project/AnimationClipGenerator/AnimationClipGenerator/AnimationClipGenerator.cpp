
// AnimationClipGenerator.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "AnimationClipGenerator.h"
#include "MainFrm.h"
#include <string>

#include "AnimationClipGeneratorDoc.h"
#include "AnimationClipGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// CAnimationClipGeneratorApp

BEGIN_MESSAGE_MAP(CAnimationClipGeneratorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAnimationClipGeneratorApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CAnimationClipGeneratorApp 생성

CAnimationClipGeneratorApp::CAnimationClipGeneratorApp() noexcept
{

	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 애플리케이션을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AnimationClipGenerator.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.

	GET_SINGLE(Timer)->Init();
}

// 유일한 CAnimationClipGeneratorApp 개체입니다.

CAnimationClipGeneratorApp theApp;


// CAnimationClipGeneratorApp 초기화

BOOL CAnimationClipGeneratorApp::InitInstance()
{
	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 애플리케이션의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnimationClipGeneratorDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CAnimationClipGeneratorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute 열기를 활성화합니다.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CAnimationClipGeneratorView* pView1 = (CAnimationClipGeneratorView*)pFrame->subSplitter1.GetPane(1, 0);
	pView1->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.
	// 끌어서 놓기에 대한 열기를 활성화합니다.
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

// CAnimationClipGeneratorApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CAnimationClipGeneratorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAnimationClipGeneratorApp 메시지 처리기


int CAnimationClipGeneratorApp::Run()
{
//	ASSERT_VALID(this);
//
//	// for tracking the idle time state
//	BOOL bIdle = TRUE;
//	LONG lIdleCount = 0;
//
//	// acquire and dispatch messages until a WM_QUIT message is received.
//	for (;;)
//	{
//		// phase1: check to see if we can do idle work
//		while (bIdle &&
//			!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
//		{
//
//			GET_SINGLE(Timer)->Update();
//
//			CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
//			PreView* pView1 = (PreView*)pFrame->subSplitter0.GetPane(0, 0);
//
//			pView1->OnDraw(nullptr);
//
//			wstring fps = to_wstring((int)GET_SINGLE(Timer)->GetFps()) + L"\n";
//
//			OutputDebugString(fps.c_str());
//
//			// call OnIdle while in bIdle state
//			if (!OnIdle(lIdleCount++))
//				bIdle = FALSE; // assume "no idle" state
//		}
//
//		// phase2: pump messages while available
//		do
//		{
//			// pump message, but quit on WM_QUIT
//			if (!PumpMessage())
//				return ExitInstance();
//
//			// reset "no idle" state after pumping "normal" message
//			if (IsIdleMessage(&m_msgCur))
//			{
//				bIdle = TRUE;
//				lIdleCount = 0;
//			}
//
//		} while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE));
//
//	}
//
//	ASSERT(FALSE);  // not reachable
	return CWinApp::Run();
}
