// ControlView.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ControlView.h"
#include <fstream>

// ControlView

IMPLEMENT_DYNCREATE(ControlView, CFormView)

ControlView::ControlView()
	: CFormView(IDD_ControlView1)
{

}

ControlView::~ControlView()
{
}

void ControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mapSelect);
	DDX_Control(pDX, IDC_LIST1, imageList);
}

BEGIN_MESSAGE_MAP(ControlView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ControlView::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &ControlView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &ControlView::OnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &ControlView::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON3, &ControlView::OnBnClickedButton3)
END_MESSAGE_MAP()


// ControlView 진단

#ifdef _DEBUG
void ControlView::AssertValid() const
{
	CFormView::AssertValid();

}

#ifndef _WIN32_WCE
void ControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

CMapToolDoc* ControlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// ControlView 메시지 처리기


void ControlView::OnCbnSelchangeCombo1()//tileMap Selection
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString mapName;
	mapSelect.GetLBText(mapSelect.GetCurSel(), mapName);
	wstring wstr = mapName.GetString();
	string str(wstr.begin(), wstr.end());
	LoadMap(str);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolView* pView1 = (CMapToolView*)pFrame->main.GetPane(0, 1);

	CRect r;

	pView1->GetWindowRect(r);
	int cx = r.Width();
	int cy = r.Height();
	int x = cx;
	int y = cy;

	if (GetDocument()->ids.size() > 0)
	{
		x = GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap > cx ? GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap : cx;
		if (GetDocument()->ids[0].size() > 0)
			y = GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap > cy ? GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap : cy;
	}
	CSize sizeTotal(x, y);
	CSize sizePage(x - 50, y - 50);
	CSize sizeLine(50, 50);
	pView1->SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}


void ControlView::OnBnClickedButton2()//Create
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//GetDocument()->OnNewDocument();

	//todo : 이름 추가
	CString name;
	GetDlgItemText(IDC_EDIT3, name);
	if (name.GetLength() == 0)
	{
		AfxMessageBox(_T("파일의 이름을 적으세요!"));
		return;
	}

	wstring wstr = L"TileMap\\" + name + L".json";
	if (GetFileAttributes(wstr.c_str()) != -1)
	{
		AfxMessageBox(_T("이미 존재하는 파일 이름입니다!"));
		return;
	}



	if (GetDlgItemInt(IDC_EDIT1) == 0 || GetDlgItemInt(IDC_EDIT2) == 0)
	{
		AfxMessageBox(_T("맵의 크기를 입력하세요!"));
		return;

	}


	GetDocument()->ClearMap();


	GetDocument()->x = GetDlgItemInt(IDC_EDIT1);
	GetDocument()->y = GetDlgItemInt(IDC_EDIT2);

	mapSelect.SetCurSel(mapSelect.AddString(L"TileMap\\" + name + L".json"));

	GetDocument()->ids.resize(GetDocument()->x);
	for (auto& a : GetDocument()->ids)
	{
		a.resize(GetDocument()->y);
	}

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolView* pView1 = (CMapToolView*)pFrame->main.GetPane(0, 1);

	CRect r;

	pView1->GetWindowRect(r);
	int cx = r.Width();
	int cy = r.Height();
	int x = cx;
	int y = cy;

	if (GetDocument()->ids.size() > 0)
	{
		x = GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap > cx ? GetDocument()->ids.size() * GetDocument()->stride + 2 * GetDocument()->gap : cx;
		if (GetDocument()->ids[0].size() > 0)
			y = GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap > cy ? GetDocument()->ids[0].size() * GetDocument()->stride + 2 * GetDocument()->gap : cy;
	}
	CSize sizeTotal(x, y);
	CSize sizePage(x - 50, y - 50);
	CSize sizeLine(50, 50);
	pView1->SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);


	OnClickedButton1();
}

using namespace rapidjson;
void ControlView::OnClickedButton1()//Save
{
	CMapToolDoc* doc = GetDocument();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//errCheck

	//writing
	rapidjson::StringBuffer ss;
	rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
	rapidjson::Document jsonDoc;
	rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
	rapidjson::Value str;

	//빈 오브젝트 {} 생성
	jsonDoc.SetObject();

	Value mapSize(kArrayType);
	mapSize.PushBack(doc->ids.size(), allocator);
	mapSize.PushBack(doc->ids[0].size(), allocator);


	Value gameObjects(kObjectType);
	for (cv::String cvString : doc->buttonImagePath)//게임 오브젝트 정보 넣어주는 곳
	{
		string name = cvString;

		//오브젝트 생성
		Value obj(kObjectType);

		//pos 멤버 생성
		Value posArr(kArrayType);
		for (int x = 0; x < doc->x; x++)
		{
			for (int y = 0; y < doc->y; y++)
			{
				if (doc->ids[x][y] == name)
				{
					Value tempArr(kArrayType);

					tempArr.PushBack(x, allocator);
					tempArr.PushBack(y, allocator);

					posArr.PushBack(tempArr, allocator);
				}
			}
		}
		//오브젝트에 멤버 추가
		obj.AddMember("pos", posArr, allocator);
		//...여기에 멤버 추가하면 됌
		
		//다큐먼트에 오브젝트 추가
		str.SetString(name.c_str(), name.length(), allocator);
		gameObjects.AddMember(str, obj, allocator);
	}

	jsonDoc.AddMember("mapSize", mapSize, allocator);
	jsonDoc.AddMember("gameObjects", gameObjects, allocator);


	jsonDoc.Accept(writer);

	CString path;
	mapSelect.GetLBText(mapSelect.GetCurSel(), path);
	std::ofstream f(path);
	string s = ss.GetString();

	f << s;
	f.flush();
	f.close();
}


void ControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CMapToolDoc* pDoc = (CMapToolDoc*)GetDocument();

	for (auto str : pDoc->maps)
	{
		wstring ws;
		ws.assign(str.begin(), str.end());
		mapSelect.AddString(ws.c_str());


	}

	static CImageList imgList;
	imgList.Create(128, 128, ILC_COLOR32, 4, 4);



	for (auto cvString : pDoc->buttonImagePath)
	{
		string str = cvString;
		static int count = 1;
		imgList.Add(&(pDoc->bitmaps[str]), RGB(0, 0, 0));


		wstring wstr(str.begin(), str.end());
		CString strItem = wstr.c_str();
		//strItem.Format(_T("%s"), str);

		imageList.InsertItem(count, strItem, count++);
	}

	/*for (map<string, CBitmap>::iterator it = pDoc->bitmaps.begin(); it != pDoc->bitmaps.end(); it++)
	{
			static int i = 0;
			imgList.Add(&(it->second), RGB(0, 0, 0));

			imageList.InsertItem(0, _T(""));
	}*/
	imageList.SetImageList(&imgList, LVSIL_NORMAL);

}

void ControlView::LoadMap(const std::string& filePath)
{
	CMapToolDoc* pDoc = (CMapToolDoc*)GetDocument();


	std::ifstream f(filePath);
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();

	rapidjson::Document jsonDoc;

	assert(!jsonDoc.Parse(buffer.str().c_str()).HasParseError());
	pDoc->ClearMap();

	for (auto info = jsonDoc.MemberBegin(); info != jsonDoc.MemberEnd(); info++)
	{
		if (info->name == "mapSize")
		{
			const rapidjson::Value& mapSize = info->value.GetArray();
			pDoc->ids.resize(mapSize[0].GetInt());
			pDoc->x = mapSize[0].GetInt();
			for (int i = 0; i < mapSize[0].GetInt(); i++)
			{
				pDoc->ids[i].resize(mapSize[1].GetInt());
				pDoc->y = mapSize[1].GetInt();
			}
		}
		else if (info->name == "gameObjects")
		{
			for (auto gameObject = info->value.MemberBegin(); gameObject != info->value.MemberEnd(); gameObject++)
			{
				for (auto component = gameObject->value.MemberBegin(); component != gameObject->value.MemberEnd(); component++)
				{
					if (component->name == "pos")
					{
						const rapidjson::Value& poss = component->value.GetArray();
						for (int i = 0; i < poss.Size(); i++)
						{
							const rapidjson::Value& pos = poss[i].GetArray();

							pDoc->ids[pos[0].GetInt()][pos[1].GetInt()] = gameObject->name.GetString();
						}
						//else if other component
					}
				}
			}
		}
	}
}


void ControlView::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	wstring wstr = imageList.GetItemText(pNMListView->iItem, 0).GetString();
	string str(wstr.begin(), wstr.end());
	GetDocument()->id = str;//


	//int idx = pNMListView -> iItem;// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	//CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);
	*pResult = 0;
}

//
//void ControlView::OnBnClickedCheck3()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	GetDocument()->isDrawGrid = IsDlgButtonChecked(IDC_CHECK3);
//
//}


void ControlView::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDocument()->isDrawGrid = !GetDocument()->isDrawGrid;
}
