// temp2.cpp: 구현 파일
//

#include "pch.h"
#include "AnimationClipGenerator.h"
#include "temp2.h"


// temp2

IMPLEMENT_DYNCREATE(temp2, CScrollView)

temp2::temp2()
{

}

temp2::~temp2()
{
}


BEGIN_MESSAGE_MAP(temp2, CScrollView)
END_MESSAGE_MAP()


// temp2 그리기

void temp2::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void temp2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// temp2 진단

#ifdef _DEBUG
void temp2::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void temp2::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// temp2 메시지 처리기
