
// MapToolView.h : interface of the CMapToolView class
//

#pragma once

#include "../Game/JW2DEngine/EnginePch.h"
#include "../Game/JW2DEngine/JW2DEngine.h"
#include "../Game/JW2DEngine/Transform.h"

class CMapToolDoc;

class CMapToolView : public CScrollView
{
protected: // create from serialization only
	CMapToolView() noexcept;
	DECLARE_DYNCREATE(CMapToolView)

// Attributes
public:
	CMapToolDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	//afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	void DrawGrid();
	void DrawTiles();
public:
	virtual void OnInitialUpdate();

private:
	WindowInfo wInf;
	JW2DEngine engine;
	Transform transform;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in MapToolView.cpp
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif

