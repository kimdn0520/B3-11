#pragma once


// PivotView 보기

#include "AnimationClipGeneratorDoc.h"
class PivotView : public CView
{
	DECLARE_DYNCREATE(PivotView)

protected:
	PivotView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~PivotView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	WindowInfo wInf;
	JW2DEngine engine;
	Transform transform;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


