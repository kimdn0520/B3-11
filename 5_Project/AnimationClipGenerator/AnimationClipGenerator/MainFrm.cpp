
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "AnimationClipGenerator.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	mainSplitter.CreateStatic(this, 1, 2);

	subSplitter0.CreateStatic(&mainSplitter, 2, 1, WS_CHILD | WS_VISIBLE, mainSplitter.IdFromRowCol(0,0));
	subSplitter1.CreateStatic(&mainSplitter, 2, 1, WS_CHILD | WS_VISIBLE, mainSplitter.IdFromRowCol(0, 1));

	subSplitter0.CreateView(0, 0, RUNTIME_CLASS(PreView), CSize(256, 256), pContext);
	subSplitter0.CreateView(1, 0, RUNTIME_CLASS(ControlView), CSize(300, 200), pContext);
	subSplitter1.CreateView(0, 0, RUNTIME_CLASS(PivotView), CSize(800, 400), pContext);
	subSplitter1.CreateView(1, 0, RUNTIME_CLASS(CAnimationClipGeneratorView), CSize(800, 400), pContext);

	preView = (PreView*)subSplitter0.GetPane(0, 0);
	controlView = (ControlView*)subSplitter0.GetPane(1, 0);
	pivotView = (PivotView*)subSplitter1.GetPane(0, 0);
	sheetView = (CAnimationClipGeneratorView*)subSplitter1.GetPane(1, 0);

	mainSplitter.SetColumnInfo(0, 256, 10);

	return TRUE;
}
