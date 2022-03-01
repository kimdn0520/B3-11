
// AnimationClipGeneratorView.h: CAnimationClipGeneratorView 클래스의 인터페이스
//

#pragma once

class CAnimationClipGeneratorDoc;
class CAnimationClipGeneratorView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CAnimationClipGeneratorView() noexcept;
	DECLARE_DYNCREATE(CAnimationClipGeneratorView)

// 특성입니다.
public:
	CAnimationClipGeneratorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CAnimationClipGeneratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	WindowInfo wInf;
	CPoint oldMousePos;
	bool isMovingBox;

	bool isMovlingLeft;
	bool isMovlingUp;
	bool isMovlingRight;
	bool isMovlingDown;

	const int movingGap;
public:
	JW2DEngine engine;
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // AnimationClipGeneratorView.cpp의 디버그 버전
inline CAnimationClipGeneratorDoc* CAnimationClipGeneratorView::GetDocument() const
   { return reinterpret_cast<CAnimationClipGeneratorDoc*>(m_pDocument); }
#endif

