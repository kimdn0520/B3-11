// PreView.cpp: 구현 파일
//

#include "pch.h"
#include "AnimationClipGenerator.h"
#include "PreView.h"


// PreView

IMPLEMENT_DYNCREATE(PreView, CView)

PreView::PreView()
	:transform(nullptr)
{
}

PreView::~PreView()
{
}

BEGIN_MESSAGE_MAP(PreView, CView)	
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PreView 그리기

void PreView::OnDraw(CDC* pDC)
{
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc * )GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 그리기 코드를 추가합니다.
	//while (true)
	//{
	//}

}


// PreView 진단

#ifdef _DEBUG
void PreView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void PreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// PreView 메시지 처리기


void PreView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetTimer(1000, 60 / 1000, NULL);

	CRect rc;
	GetClientRect(&rc);

	assert(SUCCEEDED(CoInitialize(nullptr)));

	wInf.hWnd = this->m_hWnd;
	wInf.height = rc.Height();
	wInf.width = rc.Width();
	wInf.windowed = false;
	engine.Init(wInf);




	transform.SetLocalPosition({ 64,64 });
	transform.Update();

}


void PreView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CoUninitialize();
}


void PreView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	GET_SINGLE(Timer)->Update();
	wstring fps = to_wstring((int)GET_SINGLE(Timer)->GetFps()) + L"\n";

	OutputDebugString(fps.c_str());


	engine.BeginRender();

	//engine.DrawBackGroundScreen();

	//engine.DrawTexture(L"Resource/skul.png", {50,50});

	//engine.DrawSprite(temp, &transform);
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if(pDoc->animator.GetCurrentClip() != nullptr)
	pDoc->animator.Play(engine);


	engine.EndRender();

}
