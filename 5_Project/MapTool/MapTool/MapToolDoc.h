
// MapToolDoc.h : interface of the CMapToolDoc class
//


#pragma once

#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;

class CMapToolDoc : public CDocument
{
protected: // create from serialization only
	CMapToolDoc() noexcept;
	DECLARE_DYNCREATE(CMapToolDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMapToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	const float gap = 30.0f;//������ ���� ����
	const float stride = 128.0f;//��Ÿ���� ���μ��� ����

	int x = 2;//Ÿ���� ���� ����
	int y = 2;//Ÿ���� ���� ����

	vector<vector<string>> ids;//Ÿ���� id����
	string id;


	vector<cv::String> maps;
	vector<cv::String> buttonImagePath;
	map<string, CBitmap> bitmaps;

	wstring currentFilePath;

	void ClearMap();

	bool isDrawGrid;
};
