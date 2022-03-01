#pragma once



// ToolProperty

class ToolProperty : public CPropertySheet
{
	DECLARE_DYNAMIC(ToolProperty)

public:
	ToolProperty(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	ToolProperty(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~ToolProperty();

protected:
	DECLARE_MESSAGE_MAP()
};


