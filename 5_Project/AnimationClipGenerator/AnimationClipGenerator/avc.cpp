// avc.cpp: 구현 파일
//

#include "pch.h"
#include "AnimationClipGenerator.h"
#include "avc.h"


// avc

IMPLEMENT_DYNCREATE(avc, CScrollView)

avc::avc()
{

}

avc::~avc()
{
}


BEGIN_MESSAGE_MAP(avc, CScrollView)
END_MESSAGE_MAP()


// avc 그리기

void avc::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void avc::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// avc 진단

#ifdef _DEBUG
void avc::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void avc::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

