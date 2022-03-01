#pragma once



// ControlView 폼 보기

#include <sstream>
#include "MainFrm.h"
#include "MapToolView.h"
#include "MapToolDoc.h"



class CMapToolDoc;

class ControlView : public CFormView
{
	DECLARE_DYNCREATE(ControlView)

protected:
	ControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ControlView1 };
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
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();


	CMapToolDoc* GetDocument() const;
	afx_msg void OnClickedButton1();
	virtual void OnInitialUpdate();
	CComboBox mapSelect;

	void LoadMap(const std::string& filePath);


	CListCtrl imageList;
	CImageList images;
//	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton3();
};


