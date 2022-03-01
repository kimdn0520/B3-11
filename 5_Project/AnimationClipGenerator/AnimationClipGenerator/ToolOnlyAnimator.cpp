#include "pch.h"
#include "ToolOnlyAnimator.h"
#include "MainFrm.h"


ToolOnlyAnimator::ToolOnlyAnimator()
	:transform(nullptr), _currentIndex(0), _loadTime(0.0f), currentClip(nullptr)
{
	transform.SetLocalPosition({ 128,128 });
	//transform.SetLocalScale({ 2, 2 });
	transform.Update();
}

ToolOnlyAnimator::~ToolOnlyAnimator()
{
}

void ToolOnlyAnimator::Play(JW2DEngine& engine)
{
	if (currentClip == nullptr) return;

	engine.DrawSprite
	(
		currentClip->GetFrameByIndex(_currentIndex), &transform
	);

	//// 시간 누적
	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	//PreView* pView1 = (PreView*)pFrame->subSplitter0.GetPane(0, 0);



	_loadTime += DELTA_TIME;

	// 스프라이트가 가지고있는 delayTime과 loadTime으로 적절히 잘 출력 
	if (_loadTime >= currentClip->GetFrameByIndex(_currentIndex)->delayTime)
	{
		_currentIndex = (_currentIndex + 1) % currentClip->sprites.size();
		_loadTime = 0.f;
	}
}

ToolOnlyAnimClip::ToolOnlyAnimClip()
	:totalFrameOfClip(0), name(L""), filePath(L""), sprites{},delayTime(0.3f)
{
}

ToolOnlyAnimClip::~ToolOnlyAnimClip()
{
	for (auto sprite : sprites)
	{
		delete sprite;
	}
}

Sprite* ToolOnlyAnimClip::AddFrame()
{
	Sprite* sprite = new Sprite(L"", { 0,0 }, 100, 100, { 0.5f,0.5f }, 0.15f,1.0f);


	sprites.push_back(sprite);

	totalFrameOfClip++;

	return sprite;
}

Sprite* ToolOnlyAnimClip::AddFrame(int curretIndex)
{
	Sprite* ret = new Sprite(L"", { 0,0 }, 100, 100, { 0.5f,0.5f }, 0.15f, 1.0f);
	list<Sprite*>::iterator it = sprites.begin();
	for (int i = 0; i <= curretIndex; i++)
	{
		it++;
	}
	
	sprites.insert(it, ret);

	return ret;
}

Sprite* ToolOnlyAnimClip::DeleteFrame(int index)
{
	Sprite* ret = nullptr;
	list<Sprite*>::iterator it = sprites.begin();
	for (int i = 0; i < index; i++)
	{
		ret = *it;
		it++;
		if (it == sprites.end())
			ret = (*sprites.begin());
	}

	delete (*it);
	sprites.erase(it);


	if (index == 0)
		ret = sprites.front();

	return ret;//삭제하고 이터레이터 뭐지...?
}

Sprite* ToolOnlyAnimClip::GetFrameByIndex(int index)
{
	Sprite* ret;
	list<Sprite*>::iterator it = sprites.begin();
	for (int i = 0; i < index; i++)
	{
		it++;
	}
	ret = (*it);
	return ret;
}

int ToolOnlyAnimClip::GetIndexByFrame(Sprite* frame)
{
	list<Sprite*>::iterator it = sprites.begin();
	for (int i = 0;it != sprites.end() ; i++)
	{
		if((*it++) == frame)
			return i;
	}
	return INFINITE;
}
