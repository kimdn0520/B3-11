#pragma once


// Page1 대화 상자

class Page1 : public CPropertyPage
{
	DECLARE_DYNAMIC(Page1)

public:
	Page1();
	virtual ~Page1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Page1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
