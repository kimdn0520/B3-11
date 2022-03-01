// ControlView.cpp: 구현 파일
//

#include "pch.h"
#include <fstream>
#include "AnimationClipGenerator.h"
#include "ControlView.h"
#include "Utility.h"



// ControlView

IMPLEMENT_DYNCREATE(ControlView, CFormView)

ControlView::ControlView()
	: CFormView(IDD_ControlView)
{

}

ControlView::~ControlView()
{
}

void ControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, SpriteSheet);
	DDX_Control(pDX, IDC_COMBO1, animClipComboBox);
	DDX_Control(pDX, IDC_SLIDER1, frameSlider);
	//DDX_Control(pDX, IDC_COMBO3, frameSelection);
	DDX_Control(pDX, IDC_SLIDER3, delayTimeSlider);
	DDX_Control(pDX, IDC_SLIDER2, OpacitySlider);
	DDX_Control(pDX, IDC_EDIT2, delayTimeEdit);
	DDX_Control(pDX, IDC_EDIT3, opacityEdit);
	DDX_Control(pDX, IDC_EDIT4, posXEdit);
	DDX_Control(pDX, IDC_EDIT5, posYEdit);
	DDX_Control(pDX, IDC_EDIT6, sizeXEdit);
	DDX_Control(pDX, IDC_EDIT7, sizeYEdit);
}

BEGIN_MESSAGE_MAP(ControlView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &ControlView::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &ControlView::OnBnClickedButton1)
//	ON_EN_CHANGE(IDC_EDIT1, &ControlView::OnEnChangeEdit1)
ON_CBN_SELCHANGE(IDC_COMBO1, &ControlView::OnCbnSelchangeCombo1)
ON_EN_CHANGE(IDC_EDIT2, &ControlView::OnEnChangeEdit2)
ON_BN_CLICKED(IDC_BUTTON5, &ControlView::OnBnClickedButton5)
//ON_CBN_SELCHANGE(IDC_COMBO3, &ControlView::OnCbnSelchangeCombo3)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_BUTTON3, &ControlView::OnBnClickedButton3)
ON_BN_CLICKED(IDC_CHECK2, &ControlView::OnBnClickedCheck2)
ON_EN_CHANGE(IDC_EDIT3, &ControlView::OnEnChangeEdit3)
ON_EN_CHANGE(IDC_EDIT4, &ControlView::OnEnChangeEdit4)
ON_EN_CHANGE(IDC_EDIT5, &ControlView::OnEnChangeEdit5)
ON_EN_CHANGE(IDC_EDIT6, &ControlView::OnEnChangeEdit6)
ON_EN_CHANGE(IDC_EDIT7, &ControlView::OnEnChangeEdit7)
ON_BN_CLICKED(IDC_BUTTON8, &ControlView::OnBnClickedButton8)
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
#endif //_DEBUG


// ControlView 메시지 처리기


void ControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	string path = "AnimClip\\*.json";
	vector<string> paths;
	cv::glob(path, paths, false);

	for (string p : paths)
	{
		LoadAnimClip(p);
	}

	for (auto str : pDoc->spriteSheets)
	{
		str = Utility::GetFileNameWithoutExtension(str);
		wstring ws;
		ws.assign(str.begin(), str.end());

		SpriteSheet.AddString(ws.c_str());
	}

	frameSlider.SetRange(0, 0);
	frameSlider.SetRangeMin(0);
	frameSlider.SetRangeMax(0);
	frameSlider.SetPos(0);
	frameSlider.SetTicFreq(1);



	delayTimeSlider.SetRange(0, 1000);
	delayTimeSlider.SetRangeMin(0);
	delayTimeSlider.SetRangeMax(1000);
	delayTimeSlider.SetPos(300);
	SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());
	delayTimeSlider.SetTicFreq(100);

	OpacitySlider.SetRange(0, 1000);
	OpacitySlider.SetRangeMin(0);
	OpacitySlider.SetRangeMax(1000);
	OpacitySlider.SetPos(1000);
	SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
	OpacitySlider.SetTicFreq(100);
}


void ControlView::OnCbnSelchangeCombo2()//selectSheet
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();
	CString txt;
	SpriteSheet.GetLBText(SpriteSheet.GetCurSel(), txt);
	wstring wstr = txt.GetString();
	wstr = SPRITE_PATH(wstr);
	pDoc->currentSpriteSheet = wstr;
	pDoc->currentAnimClip = nullptr;
	pDoc->currentFrame = nullptr;
	pDoc->animator.SetCurrentClip(nullptr);

	animClipComboBox.SetCurSel(-1);

	frameSlider.SetPos(0);
	delayTimeSlider.SetPos(0);
	OpacitySlider.SetPos(0);

	SetDlgItemInt(IDC_EDIT2, 300);
	SetDlgItemInt(IDC_EDIT3, 1000);
	SetDlgItemInt(IDC_EDIT4, 0);
	SetDlgItemInt(IDC_EDIT5, 0);
	SetDlgItemInt(IDC_EDIT6, 0);
	SetDlgItemInt(IDC_EDIT7, 0);


	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CAnimationClipGeneratorView* pView1 = (CAnimationClipGeneratorView*)pFrame->subSplitter1.GetPane(1, 0);

	CRect r;
	pView1->GetClientRect(r);

	int x = r.Width();
	int y = r.Height();

	if ((pDoc->currentSpriteSheet.length()) != 0)
	{
		x = pView1->engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().width > x ? pView1->engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().width : x;
		y = pView1->engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().height > y ? pView1->engine.LoadSpriteSheet(pDoc->currentSpriteSheet)->GetPixelSize().height : y;
	}

	CSize sizeTotal(x, y);
	CSize sizePage(x - 50, y - 50);
	CSize sizeLine(50, 50);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

	pView1->engine.ResizeScreen(r.Width(), r.Height());

}


void ControlView::OnBnClickedButton1()//AnimClip Add
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	CString txt;

	GetDlgItemText(IDC_EDIT1, txt);

	if (pDoc->currentSpriteSheet.length() == 0)
	{
		AfxMessageBox(_T("우선 스프라이트 시트를 선택하세요!"));
		return;
	}

	if (txt.GetLength() == 0)
	{
		AfxMessageBox(_T("이름을 입력하세요!"));
		return;
	}


	if (pDoc->anims.find(txt.GetString()) == pDoc->anims.end())
	{
		pDoc->anims[txt.GetString()] = new ToolOnlyAnimClip();
		pDoc->currentAnimClip = pDoc->anims[txt.GetString()];
		pDoc->currentFrame = pDoc->currentAnimClip->AddFrame();
		pDoc->currentFrame->sheetFilePath = pDoc->currentSpriteSheet.c_str();
		pDoc->animator.SetCurrentClip(pDoc->currentAnimClip);
		animClipComboBox.SetCurSel(animClipComboBox.AddString(txt));


		frameSlider.SetRange(0, pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetRangeMax(pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetPos(0);

		delayTimeSlider.SetPos(300);
		SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());


		OpacitySlider.SetPos(1000);
		SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
	}
	else
	{
		AfxMessageBox(_T("같은 이름의 클립이 존재합니다!"));
		return;
	}

}


//void ControlView::OnEnChangeEdit1()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void ControlView::OnCbnSelchangeCombo1()//animClip Change
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();
	CString txt;

	animClipComboBox.GetLBText(animClipComboBox.GetCurSel(), txt);
	pDoc->currentAnimClip = pDoc->anims[txt.GetString()];
	pDoc->currentFrame = pDoc->currentAnimClip->GetFrameByIndex(0);
	pDoc->currentSpriteSheet = pDoc->currentFrame->sheetFilePath;
	SpriteSheet.SetCurSel(SpriteSheet.FindStringExact
	(-1, Utility::ToWstring(Utility::GetFileNameWithoutExtension(Utility::ToString(pDoc->currentSpriteSheet))).c_str()));
	pDoc->animator.SetCurrentClip(pDoc->currentAnimClip);

	frameSlider.SetRange(0, pDoc->currentAnimClip->sprites.size() - 1);
	frameSlider.SetRangeMax(pDoc->currentAnimClip->sprites.size() - 1);
	frameSlider.SetPos(0);

	delayTimeSlider.SetPos((int)(pDoc->currentFrame->delayTime * 1000));
	SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());
	OpacitySlider.SetPos((int)(pDoc->currentFrame->opacity * 1000));
	SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
}





void ControlView::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();
	if (pDoc->currentAnimClip == nullptr)
	{
		AfxMessageBox(_T("클립을 우선 선택하세요!"));
		return;
	}

	if (pDoc->currentFrame != nullptr)
	{
		Sprite old = (*pDoc->currentFrame);

		pDoc->currentFrame = pDoc->currentAnimClip->AddFrame(pDoc->currentAnimClip->GetIndexByFrame(pDoc->currentFrame));
		pDoc->currentFrame->oriPos = old.oriPos;
		pDoc->currentFrame->oriWidth = old.oriWidth;
		pDoc->currentFrame->oriHeight = old.oriHeight;
		pDoc->currentFrame->height = old.height;
		pDoc->currentFrame->width = old.width;
		pDoc->currentFrame->delayTime = old.delayTime;
		pDoc->currentFrame->opacity = old.opacity;
		pDoc->currentFrame->sheetFilePath = pDoc->currentSpriteSheet.c_str();
		pDoc->animator.SetCurrentClip(pDoc->currentAnimClip);

		frameSlider.SetRange(0, pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetRangeMax(pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetPos(pDoc->currentAnimClip->GetIndexByFrame(pDoc->currentFrame));
	}
	else
	{
		pDoc->currentFrame = pDoc->currentAnimClip->AddFrame();
		pDoc->currentFrame->sheetFilePath = pDoc->currentSpriteSheet.c_str();
		pDoc->animator.SetCurrentClip(pDoc->currentAnimClip);

		frameSlider.SetRange(0, pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetRangeMax(pDoc->currentAnimClip->sprites.size() - 1);
		frameSlider.SetPos(pDoc->currentAnimClip->sprites.size() - 1);

	}

}

//
//void ControlView::OnCbnSelchangeCombo3()//프레임 넘버 선택기
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();
//	pDoc->currentFrame = pDoc->currentAnimClip->GetFrameByIndex(frameSelection.GetCurSel());
//
//}


void ControlView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar == (CScrollBar*)&frameSlider)
	{
		pDoc->currentFrame = pDoc->currentAnimClip->GetFrameByIndex(frameSlider.GetPos());
		delayTimeSlider.SetPos((int)(pDoc->currentFrame->delayTime * 1000));
		SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());
		OpacitySlider.SetPos((int)(pDoc->currentFrame->opacity * 1000));
		SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
	}
	else if (pScrollBar == (CScrollBar*)&delayTimeSlider)
	{

		if (IsDlgButtonChecked(IDC_CHECK1))
		{
			for (Sprite* frame : pDoc->currentAnimClip->sprites)
			{
				frame->delayTime = delayTimeSlider.GetPos() / (float)delayTimeSlider.GetRangeMax();
			}
		}
		else
			pDoc->currentFrame->delayTime = delayTimeSlider.GetPos() / (float)delayTimeSlider.GetRangeMax();


		SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());
	}
	else if (pScrollBar == (CScrollBar*)&OpacitySlider)
	{
		if (IsDlgButtonChecked(IDC_CHECK2))
		{
			for (Sprite* frame : pDoc->currentAnimClip->sprites)
			{
				frame->opacity = OpacitySlider.GetPos() / (float)OpacitySlider.GetRangeMax();
			}
		}
		else
			pDoc->currentFrame->opacity = OpacitySlider.GetPos() / (float)OpacitySlider.GetRangeMax();


		SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
	}
}


void ControlView::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SaveAnimClip();
}

void ControlView::LoadAnimClip(const std::string& filePath)
{
	//재영이 참고
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();


	std::ifstream f(filePath);
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();

	//todo : sprite에 sheetFilePath 추가
	using namespace Utility;
	ToolOnlyAnimClip* clip = pDoc->anims[ToWstring(GetFileNameWithoutExtension(filePath))] = new ToolOnlyAnimClip();
	animClipComboBox.AddString(ToWstring(GetFileNameWithoutExtension(filePath)).c_str());

	rapidjson::Document jsonDoc;

	assert(!jsonDoc.Parse(buffer.str().c_str()).HasParseError());
	//이어서 데이터 넣기


	for (auto frame = jsonDoc.MemberBegin(); frame != jsonDoc.MemberEnd(); frame++)
	{
		Sprite* sprite = clip->AddFrame();
		for (auto info = frame->value.MemberBegin(); info != frame->value.MemberEnd(); info++)
		{
			if (info->name == "sheetFilePath")
				sprite->sheetFilePath = Utility::ToWstring(info->value.GetString());
			else if (info->name == "oriPos")
			{
				sprite->oriPos.x = info->value.GetArray()[0].GetFloat();
				sprite->oriPos.y = info->value.GetArray()[1].GetFloat();
			}
			else if (info->name == "oriSize")
			{
				sprite->oriWidth = info->value.GetArray()[0].GetInt();
				sprite->oriHeight = info->value.GetArray()[1].GetInt();
			}
			else if (info->name == "size")
			{
				sprite->width = info->value.GetArray()[0].GetInt();
				sprite->height = info->value.GetArray()[1].GetInt();
			}
			else if (info->name == "pivot")
			{
				sprite->pivot.x = info->value.GetArray()[0].GetFloat();
				sprite->pivot.y = info->value.GetArray()[1].GetFloat();
			}
			else if (info->name == "delayTime")
				sprite->delayTime = info->value.GetFloat();
			else if (info->name == "opacity")
				sprite->opacity = info->value.GetFloat();
		}
	}
}

void ControlView::SaveAnimClip()
{
	using namespace rapidjson;
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();
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

	/*
		format
		{
			0 : {
			"oriPos" : [x,y],
			"oriSize" : [x,y],
			"Size" : [x,y],
			"Pivot" : [x.xf, x.xf],
			"delayTime" : x.xxf;
			"opacity" : x.xf;
			}

			1 : {
			}

			2 : {
			}...
		}
	*/
	int framenum = 0;
	for (Sprite* sprite : pDoc->currentAnimClip->sprites)
	{
		Value frame(kObjectType);//프레임 생성

		//spriteFilePath
		using namespace Utility;
		Value sheetFilePath(kStringType);
		sheetFilePath.SetString(ToString(sprite->sheetFilePath).c_str(), allocator);

		//oriPos
		Value oriPos(kArrayType);
		oriPos.PushBack(sprite->oriPos.x, allocator);
		oriPos.PushBack(sprite->oriPos.y, allocator);

		//oriSize
		Value oriSize(kArrayType);
		oriSize.PushBack(sprite->oriWidth, allocator);
		oriSize.PushBack(sprite->oriHeight, allocator);

		//Size
		Value size(kArrayType);
		size.PushBack(sprite->width, allocator);
		size.PushBack(sprite->height, allocator);

		//Pivot
		Value pivot(kArrayType);
		pivot.PushBack(sprite->pivot.x, allocator);
		pivot.PushBack(sprite->pivot.y, allocator);

		//delayTime
		Value delayTime(kNumberType);
		delayTime.SetFloat(sprite->delayTime);

		//opacity
		Value opacity(kNumberType);
		opacity.SetFloat(sprite->opacity);

		frame.AddMember("sheetFilePath", sheetFilePath, allocator);
		frame.AddMember("oriPos", oriPos, allocator);
		frame.AddMember("oriSize", oriSize, allocator);
		frame.AddMember("size", size, allocator);
		frame.AddMember("pivot", pivot, allocator);
		frame.AddMember("delayTime", delayTime, allocator);
		frame.AddMember("opacity", opacity, allocator);

		Value name(kStringType);
		name.SetString(to_string(framenum++).c_str(), to_string(framenum).length(), allocator);
		jsonDoc.AddMember(name, frame, allocator);//프레임 삽입
	}

	jsonDoc.Accept(writer);

	CString path;
	animClipComboBox.GetLBText(animClipComboBox.GetCurSel(), path);
	std::ofstream f(L"AnimClip\\" + path + L".json");
	string s = ss.GetString();

	f << s;
	f.flush();
	f.close();
}


void ControlView::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void ControlView::OnEnChangeEdit2()//delayTime
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	if (IsDlgButtonChecked(IDC_CHECK1))
	{
		for (Sprite* frame : pDoc->currentAnimClip->sprites)
		{
			frame->delayTime = GetDlgItemInt(IDC_EDIT2) / 1000.0f;
			delayTimeSlider.SetPos(GetDlgItemInt(IDC_EDIT2));
		}
	}
	else
	{
		pDoc->currentFrame->delayTime = GetDlgItemInt(IDC_EDIT2) / 1000.0f;
		delayTimeSlider.SetPos(GetDlgItemInt(IDC_EDIT2));
	}

}

void ControlView::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	if (IsDlgButtonChecked(IDC_CHECK2))
	{
		for (Sprite* frame : pDoc->currentAnimClip->sprites)
		{
			frame->opacity = GetDlgItemInt(IDC_EDIT3) / 1000.0f;
			OpacitySlider.SetPos(GetDlgItemInt(IDC_EDIT3));
		}
	}
	else
	{
		pDoc->currentFrame->opacity = GetDlgItemInt(IDC_EDIT3) / 1000.0f;
		OpacitySlider.SetPos(GetDlgItemInt(IDC_EDIT3));
	}
}


void ControlView::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	pDoc->currentFrame->oriPos.x = (float)GetDlgItemInt(IDC_EDIT4);
}


void ControlView::OnEnChangeEdit5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	pDoc->currentFrame->oriPos.y = (float)GetDlgItemInt(IDC_EDIT5);
}


void ControlView::OnEnChangeEdit6()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	pDoc->currentFrame->oriWidth = (float)GetDlgItemInt(IDC_EDIT6);
	pDoc->currentFrame->width = (float)GetDlgItemInt(IDC_EDIT6);
}


void ControlView::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	pDoc->currentFrame->oriHeight = (float)GetDlgItemInt(IDC_EDIT7);
	pDoc->currentFrame->height = (float)GetDlgItemInt(IDC_EDIT7);
}


void ControlView::OnBnClickedButton8()
{


	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;


	if (pDoc->currentAnimClip->sprites.size() <= 1) 
	{
		AfxMessageBox(_T("최소 한개의 프레임은 존재해야합니다!"));
		return;
	}

	pDoc->currentFrame = pDoc->currentAnimClip->DeleteFrame(frameSlider.GetPos());
	
	Refresh();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void ControlView::Refresh()
{
	CAnimationClipGeneratorDoc* pDoc = (CAnimationClipGeneratorDoc*)GetDocument();

	if (pDoc->currentFrame == nullptr) return;

	frameSlider.SetRange(0, pDoc->currentAnimClip->sprites.size() - 1);
	frameSlider.SetRangeMax(pDoc->currentAnimClip->sprites.size() - 1);
	frameSlider.SetPos(pDoc->currentAnimClip->GetIndexByFrame(pDoc->currentFrame));
	pDoc->animator.Zero();

	delayTimeSlider.SetPos((int)(pDoc->currentFrame->delayTime * 1000));
	SetDlgItemText(IDC_EDIT2, to_wstring(delayTimeSlider.GetPos()).c_str());
	OpacitySlider.SetPos((int)(pDoc->currentFrame->opacity * 1000));
	SetDlgItemText(IDC_EDIT3, to_wstring(OpacitySlider.GetPos()).c_str());
	SetDlgItemInt(IDC_EDIT4, pDoc->currentFrame->oriPos.x);
	SetDlgItemInt(IDC_EDIT5, pDoc->currentFrame->oriPos.y);
	SetDlgItemInt(IDC_EDIT6, pDoc->currentFrame->width);
	SetDlgItemInt(IDC_EDIT7, pDoc->currentFrame->height);
	
}
