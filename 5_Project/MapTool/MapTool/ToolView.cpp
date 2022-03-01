// ToolView.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ToolView.h"


// ToolView

IMPLEMENT_DYNCREATE(ToolView, CView)

ToolView::ToolView()
{

}

ToolView::~ToolView()
{
}

BEGIN_MESSAGE_MAP(ToolView, CView)
END_MESSAGE_MAP()


// ToolView 그리기

void ToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// ToolView 진단

#ifdef _DEBUG
void ToolView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void ToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// ToolView 메시지 처리기
