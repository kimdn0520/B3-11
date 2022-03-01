// ToolProperty.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ToolProperty.h"


// ToolProperty

IMPLEMENT_DYNAMIC(ToolProperty, CPropertySheet)

ToolProperty::ToolProperty(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

ToolProperty::ToolProperty(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

ToolProperty::~ToolProperty()
{
}


BEGIN_MESSAGE_MAP(ToolProperty, CPropertySheet)
END_MESSAGE_MAP()


// ToolProperty 메시지 처리기
