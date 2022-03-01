// PivotView.cpp: 구현 파일
//

#include "pch.h"
#include "AnimationClipGenerator.h"
#include "PivotView.h"


// PivotView

IMPLEMENT_DYNCREATE(PivotView, CView)

PivotView::PivotView()
	:transform(nullptr)
{

}

PivotView::~PivotView()
{
}

BEGIN_MESSAGE_MAP(PivotView, CView)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PivotView 그리기

void PivotView::OnDraw(CDC* pDC)
{
}


// PivotView 진단

#ifdef _DEBUG
void PivotView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void PivotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// PivotView 메시지 처리기


void PivotView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	CSize sizeViewPage;
	sizeViewPage.cx = rc.right - rc.left;
	sizeViewPage.cy = rc.bottom - rc.top;

	CSize sizeViewPageTotal;
	sizeViewPageTotal.cx = sizeViewPage.cx;
	sizeViewPageTotal.cy = sizeViewPage.cy; // 3페이지를 설정하고 싶으면 * 3을 하면 되긋지

	assert(SUCCEEDED(CoInitialize(nullptr)));

	wInf.hWnd = this->m_hWnd;
	wInf.height = rc.Height();
	wInf.width = rc.Width();
	wInf.windowed = false;
	engine.Init(wInf);

	SetTimer(0511, 1000 / 60, NULL);
	//engine.LoadSpriteSheet(L"Resource/Left_Move1.bmp");
}


void PivotView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	transform.SetLocalPosition({ cx / 2.0f, cy / 2.0f });

	engine.ResizeScreen(cx, cy);
}


void PivotView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnTimer(nIDEvent);

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	// TODO: 여기에 그리기 코드를 추가합니다.engine.BeginRender();

	engine.BeginRender();
	//engine.DrawBackGroundScreen();

	//engine.DrawTexture(L"Resource/Left_Move1.bmp", {- (float)scrollPos.x,(float) scrollPos.y })

	if (pDoc->currentFrame != nullptr)
		engine.DrawSprite(pDoc->currentFrame, &transform);


	engine.EndRender();
}
