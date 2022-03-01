
// MapToolView.cpp : implementation of the CMapToolView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MapToolDoc.h"
#include "MapToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolView

IMPLEMENT_DYNCREATE(CMapToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMapToolView, CScrollView)
	ON_WM_SIZE()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_TIMER()
END_MESSAGE_MAP()

// CMapToolView construction/destruction

CMapToolView::CMapToolView() noexcept
	:transform(nullptr)
{
	// TODO: add construction code here// Enable D2D support for this window:
	//EnableD2DSupport();


}

CMapToolView::~CMapToolView()
{

}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMapToolView drawing

void CMapToolView::OnDraw(CDC* /*pDC*/)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMapToolView diagnostics

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolDoc* CMapToolView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolView message handlers


void CMapToolView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	int x = cx;
	int y = cy;

	if (GetDocument()->ids.size() > 0)
	{
		x = GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap > cx ? GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap : cx;
		if(GetDocument()->ids[0].size() > 0)
			y = GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap > cy ? GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap : cy;
	}
	CSize sizeTotal(x, y);
	CSize sizePage(x - 50, y - 50);
	CSize sizeLine(50, 50);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

	engine.ResizeScreen(cx, cy);
}



void CMapToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);


	CMapToolDoc* doc = GetDocument();

	float stride = doc->stride;
	float gap = doc->gap;

	POINT scrollPos = GetScrollPosition();

	int x = (point.x - doc->gap + scrollPos.x) / doc->stride;
	int y = (point.y - doc->gap + scrollPos.y) / doc->stride;

	if (x >= doc->ids.size()) return;
	if (y >= doc->ids[0].size()) return;
	doc->ids[x][y] = GetDocument()->id;

}

void CMapToolView::DrawGrid()
{
	CMapToolDoc* doc = GetDocument();
	float gap = doc->gap;
	float stride = doc->stride;
	float maxX = doc->x * doc->stride;
	float maxY = doc->y * doc->stride;
	POINT scrollPos = GetScrollPosition();


	for (int i = 0; i < doc->x + 1; i++)
	{
		engine.DrawLine({ (long)(i * stride + gap - scrollPos.x) , (long)(0.0f + gap - scrollPos.y)}, { (long)(i * stride + gap - scrollPos.x) , (long)(maxY + gap - scrollPos.y) });
	}
	for (int i = 0; i < doc->y + 1; i++)
	{

		engine.DrawLine({ (long)(0.0f + gap - scrollPos.x) , (long)(i * stride + gap - scrollPos.y) }, { (long)(maxX + gap - scrollPos.x) , (long)(i * stride + gap - scrollPos.y) });
	}
}

void CMapToolView::DrawTiles()
{
	CMapToolDoc* doc = GetDocument();
	float gap = doc->gap;
	float stride = doc->stride;
	float maxX = doc->x * doc->stride;
	float maxY = doc->y * doc->stride;
	POINT scrollPos = GetScrollPosition();


	for (int y = 0; y < doc->y; y++)
	{
		for (int x = 0; x < doc->x; x++)
		{
			if (doc->ids[x][y] == "") continue;
			string str = doc->ids[x][y];
			wstring wstr(str.begin(), str.end());

			//engine.DrawTexture(wstr.c_str(), { x * stride + stride * 0.5f + gap - scrollPos.x, y * stride + stride * 0.5f + gap - scrollPos.y });
			ID2D1Bitmap* bitmap = engine.LoadSpriteSheet(wstr.c_str());

			transform.SetLocalPosition({ x * stride + stride * 0.5f + gap - scrollPos.x, y * stride + stride * 0.5f + gap - scrollPos.y });


			float pivotX = bitmap->GetPixelSize().width == 128 ? 0.5f : 0.75f;
			float pivotY = bitmap->GetPixelSize().height == 128 ? 0.5f : 0.25f;
			
			engine.DrawSprite(engine.LoadSpriteFromSheet(wstr.c_str(), { 0,0 }, bitmap->GetPixelSize().width, bitmap->GetPixelSize().height, { pivotX, pivotY }, 1.0f, 1.0f), &transform);

			/*if (doc->ids[x][y] == "")
			{
				engine.DrawTexture(L"Resource/Left_Move1.bmp", { x * stride + stride * 0.5f + gap - scrollPos.x, y * stride + stride * 0.5f + gap - scrollPos.y });
			}
			else if (doc->ids[x][y] == 2)
			{
				transform.SetLocalPosition({ x * stride + stride * 0.5f + gap - scrollPos.x, y * stride + stride * 0.5f + gap - scrollPos.y });
				engine.DrawSprite(engine.LoadSpriteFromSheet(L"Resource/Skul.png", { 0,0 }, 64, 64, { 0.5f,0.5f },0.3f,1.0f), &transform);
			}*/
		}
	}
}

void CMapToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	CSize sizeViewPage;
	sizeViewPage.cx = rc.right - rc.left;
	sizeViewPage.cy = rc.bottom - rc.top;

	CSize sizeViewPageTotal;
	sizeViewPageTotal.cx = sizeViewPage.cx;
	sizeViewPageTotal.cy = sizeViewPage.cy; // 3페이지를 설정하고 싶으면 * 3을 하면 되긋지

	SetScrollSizes(MM_TEXT, sizeViewPageTotal);


	wInf.hWnd = this->m_hWnd;
	wInf.height = rc.Height();
	wInf.width = rc.Width();
	wInf.windowed = false;
	engine.Init(wInf);

	SetTimer(0511, 60 / 1000, NULL);
}


void CMapToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnRButtonDown(nFlags, point);

	CMapToolDoc* doc = GetDocument();

	float stride = doc->stride;
	float gap = doc->gap;

	POINT scrollPos = GetScrollPosition();

	int x = (point.x - doc->gap + scrollPos.x) / doc->stride;
	int y = (point.y - doc->gap + scrollPos.y) / doc->stride;

	if (x >= doc->ids.size()) return;
	if (y >= doc->ids[0].size()) return;
	doc->ids[x][y] = "";

}


void CMapToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CScrollView::OnTimer(nIDEvent);
	engine.BeginRender();

	engine.DrawBackGroundScreen();




	if(GetDocument()->isDrawGrid)
		DrawGrid();

	DrawTiles();



	for (auto path : GetDocument()->buttonImagePath)
	{
		string str = path;

	}

	engine.EndRender();
	
}
