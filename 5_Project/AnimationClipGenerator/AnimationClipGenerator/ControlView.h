#pragma once



// ControlView 폼 보기
#include "AnimationClipGeneratorDoc.h"

class CAnimationClipGeneratorDoc;

class ControlView : public CFormView
{
	DECLARE_DYNCREATE(ControlView)

protected:
	ControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ControlView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox SpriteSheet;
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo2();//spriteSheetChange
	CComboBox animClipComboBox;
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();//animClipChange
	CSliderCtrl frameSlider;
	afx_msg void OnBnClickedButton5();//AddFrame
	CComboBox frameSelection;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl delayTimeSlider;
	CSliderCtrl OpacitySlider;
	afx_msg void OnBnClickedButton3();

	void LoadAnimClip(const std::string& filePath);
	void SaveAnimClip();
	afx_msg void OnBnClickedCheck2();

	afx_msg void OnEnChangeEdit2();//delayTime
	CEdit delayTimeEdit;

	afx_msg void OnEnChangeEdit3();//opacity
	CEdit opacityEdit;

	afx_msg void OnEnChangeEdit4();//posX
	CEdit posXEdit;

	afx_msg void OnEnChangeEdit5();//posY
	CEdit posYEdit;

	afx_msg void OnEnChangeEdit6();//sizeX
	CEdit sizeXEdit;

	afx_msg void OnEnChangeEdit7();//sizeY
	CEdit sizeYEdit;

	afx_msg void OnBnClickedButton8();//frameDelete 버튼

	void Refresh();
};


