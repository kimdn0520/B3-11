
// AnimationClipGeneratorView.cpp: CAnimationClipGeneratorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AnimationClipGenerator.h"
#endif

#include "AnimationClipGeneratorDoc.h"
#include "AnimationClipGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimationClipGeneratorView

IMPLEMENT_DYNCREATE(CAnimationClipGeneratorView, CScrollView)

BEGIN_MESSAGE_MAP(CAnimationClipGeneratorView, CScrollView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CAnimationClipGeneratorView 생성/소멸

CAnimationClipGeneratorView::CAnimationClipGeneratorView() noexcept
	:movingGap(2)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	isMovingBox = false;

	isMovlingLeft = false;
	isMovlingUp = false;
	isMovlingRight = false;
	isMovlingDown = false;
}

CAnimationClipGeneratorView::~CAnimationClipGeneratorView()
{
}

BOOL CAnimationClipGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CAnimationClipGeneratorView 그리기

void CAnimationClipGeneratorView::OnDraw(CDC* /*pDC*/)
{
	return;
}


// CAnimationClipGeneratorView 진단

#ifdef _DEBUG
void CAnimationClipGeneratorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAnimationClipGeneratorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAnimationClipGeneratorDoc* CAnimationClipGeneratorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimationClipGeneratorDoc)));
	return (CAnimationClipGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnimationClipGeneratorView 메시지 처리기


void CAnimationClipGeneratorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	CSize sizeViewPage;
	sizeViewPage.cx = rc.right - rc.left;
	sizeViewPage.cy = rc.bottom - rc.top;

	CSize sizeViewPageTotal;
	sizeViewPageTotal.cx = sizeViewPage.cx * 3;
	sizeViewPageTotal.cy = sizeViewPage.cy * 3; // 3페이지를 설정하고 싶으면 * 3을 하면 되긋지

	SetScrollSizes(MM_TEXT, sizeViewPageTotal);

	assert(SUCCEEDED(CoInitialize(nullptr)));

	wInf.hWnd = this->m_hWnd;
	wInf.height = rc.Height();
	wInf.width = rc.Width();
	wInf.windowed = false;
	engine.Init(wInf);

	//todo : 스크롤바의 사이즈와 뭔가 연관이 있는 듯
	/*int scrollwidth = GetSystemMetrics(SM_CXHSCROLL);
	int scrollheight = GetSystemMetrics(SM_CXVSCROLL);*/
	

	engine.SetBrushColor(0.0f, 1.0f, 0.0f, 1.0f);
	SetTimer(0511, 1000 / 60, NULL);
	//engine.LoadSpriteSheet(L"Resource/Left_Move1.bmp");
}


void CAnimationClipGeneratorView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CoUninitialize();
}


void CAnimationClipGeneratorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnTimer(nIDEvent);

	POINT scrollPos = GetScrollPosition();

	CAnimationClipGeneratorDoc* pDoc = GetDocument();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	engine.BeginRender();

	engine.DrawBackGroundScreen();

	//engine.DrawTexture(L"Resource/Left_Move1.bmp", {- (float)scrollPos.x,(float) scrollPos.y })


	if (pDoc->currentSpriteSheet.length())
		engine.DrawTexture(pDoc->currentSpriteSheet.c_str(),
			{ engine.LoadSpriteSheet(pDoc->currentSpriteSheet.c_str())->GetPixelSize().width / 2.0f - scrollPos.x,
			engine.LoadSpriteSheet(pDoc->currentSpriteSheet.c_str())->GetPixelSize().height / 2.0f - scrollPos.y});

	if (pDoc->currentFrame != nullptr)
		engine.DrawRectScreen(pDoc->currentFrame->oriPos.x - scrollPos.x, pDoc->currentFrame->oriPos.y - scrollPos.y
			, pDoc->currentFrame->oriPos.x + pDoc->currentFrame->width - scrollPos.x
			, pDoc->currentFrame->oriPos.y + pDoc->currentFrame->height - scrollPos.y
		);

	engine.EndRender();
}


void CAnimationClipGeneratorView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAnimationClipGeneratorDoc* pDoc = GetDocument();

	int x = cx;
	int y = cy;

	if ((pDoc->currentSpriteSheet.length()) != 0)
	{
		x = engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().width > x ? engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().width : x;
		y = engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().height > y ? engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().height : y;
	}

	CSize sizeTotal(x, y);
	CSize sizePage(x - 50, y - 50);
	CSize sizeLine(50, 50);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

	engine.ResizeScreen(cx, cy);
}


void CAnimationClipGeneratorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);
	CAnimationClipGeneratorDoc* doc = GetDocument();
	if (doc->currentFrame == nullptr) return;

	POINT scrollPos = GetScrollPosition();
	point.x += scrollPos.x;
	point.y += scrollPos.y;
	oldMousePos = point;

	//좌변 눌렀는지
	if (doc->currentFrame->oriPos.x - movingGap <= point.x &&
		doc->currentFrame->oriPos.x + movingGap >= point.x &&
		doc->currentFrame->oriPos.y - movingGap <= point.y &&
		doc->currentFrame->oriPos.y + doc->currentFrame->height + movingGap >= point.y)
		isMovlingLeft = true;
	//우변 눌렀는지
	if (doc->currentFrame->oriPos.x + doc->currentFrame->width - movingGap <= point.x &&
		doc->currentFrame->oriPos.x + doc->currentFrame->width + movingGap >= point.x &&
		doc->currentFrame->oriPos.y - movingGap <= point.y &&
		doc->currentFrame->oriPos.y + doc->currentFrame->height + movingGap >= point.y)
		isMovlingRight = true;
	//윗변 눌렀는지
	if (doc->currentFrame->oriPos.x - movingGap <= point.x &&
		doc->currentFrame->oriPos.x + doc->currentFrame->width + movingGap >= point.x &&
		doc->currentFrame->oriPos.y - movingGap <= point.y &&
		doc->currentFrame->oriPos.y + movingGap >= point.y)
		isMovlingUp = true;
	//하변 눌렀는지
	if (doc->currentFrame->oriPos.x - movingGap <= point.x &&
		doc->currentFrame->oriPos.x + doc->currentFrame->width + movingGap >= point.x &&
		doc->currentFrame->oriPos.y + doc->currentFrame->height - movingGap <= point.y &&
		doc->currentFrame->oriPos.y + doc->currentFrame->height + movingGap >= point.y)
		isMovlingDown = true;

	if (isMovlingLeft || isMovlingRight || isMovlingUp || isMovlingDown) return;
	if (doc->currentFrame->oriPos.x <= point.x &&
		doc->currentFrame->oriPos.y <= point.y &&
		doc->currentFrame->oriPos.x + doc->currentFrame->width >= point.x &&
		doc->currentFrame->oriPos.y + doc->currentFrame->height >= point.y)
	{
		isMovingBox = true;
	}
	
}


void CAnimationClipGeneratorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonUp(nFlags, point);
	isMovlingLeft = false;
	isMovlingRight = false;
	isMovlingUp = false;
	isMovlingDown = false;


	isMovingBox = false;
}


void CAnimationClipGeneratorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);
	CAnimationClipGeneratorDoc* doc = GetDocument();
	POINT scrollPos = GetScrollPosition();
	point.x += scrollPos.x;
	point.y += scrollPos.y;

	int xDiff = point.x - oldMousePos.x;
	int yDiff = point.y - oldMousePos.y;

	if (isMovlingLeft)
	{
		doc->currentFrame->oriPos.x += xDiff;
		doc->currentFrame->width -= xDiff;
		doc->currentFrame->oriWidth -= xDiff;
	}
	if (isMovlingRight)
	{
		doc->currentFrame->width += xDiff;
		doc->currentFrame->oriWidth += xDiff;
	}
	if (isMovlingUp)
	{
		doc->currentFrame->oriPos.y += yDiff;
		doc->currentFrame->height -= yDiff;
		doc->currentFrame->oriHeight -= yDiff;
	}
	if (isMovlingDown)
	{
		doc->currentFrame->oriHeight += yDiff;
		doc->currentFrame->height += yDiff;
	}


	if (isMovingBox)
	{

		doc->currentFrame->oriPos.x += xDiff;
		doc->currentFrame->oriPos.y += yDiff;

	}


	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	ControlView* pView1 = (ControlView*)pFrame->subSplitter0.GetPane(1, 0);

	if (doc->currentFrame != nullptr)
	{
		pView1->SetDlgItemText(IDC_EDIT4, to_wstring((int)doc->currentFrame->oriPos.x).c_str());
		pView1->SetDlgItemText(IDC_EDIT5, to_wstring((int)doc->currentFrame->oriPos.y).c_str());
		pView1->SetDlgItemText(IDC_EDIT6, to_wstring(doc->currentFrame->oriWidth).c_str());
		pView1->SetDlgItemText(IDC_EDIT7, to_wstring(doc->currentFrame->oriHeight).c_str());
	}

		oldMousePos = point;
}
