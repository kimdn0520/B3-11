// Page1.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "Page1.h"
#include "afxdialogex.h"


// Page1 대화 상자

IMPLEMENT_DYNAMIC(Page1, CPropertyPage)

Page1::Page1()
	: CPropertyPage(IDD_Page1)
{

}

Page1::~Page1()
{
}

void Page1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Page1, CPropertyPage)
END_MESSAGE_MAP()


// Page1 메시지 처리기
