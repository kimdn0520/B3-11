#pragma once

#include "../../Game/JW2DEngine/Transform.h"
using namespace std;

class ToolOnlyAnimClip
{
public:
	ToolOnlyAnimClip();
	~ToolOnlyAnimClip();

	Sprite* AddFrame();
	Sprite* AddFrame(int curretIndex);
	Sprite* DeleteFrame(int index);
	Sprite* GetFrameByIndex(int index);
	int GetIndexByFrame(Sprite* frame);

	wstring name;

	const wchar_t* filePath;

	list<Sprite*> sprites;


	float delayTime;
private:
	int totalFrameOfClip;
};

class ToolOnlyAnimator
{
public:
	ToolOnlyAnimator();
	~ToolOnlyAnimator();

	ToolOnlyAnimClip* GetCurrentClip() { return currentClip; }
	void SetCurrentClip(ToolOnlyAnimClip* clip) 
	{
		currentClip = clip;
		_currentIndex
			= 0;
	}

	void Play(JW2DEngine& engine);

	void Zero() { _currentIndex = 0; }

private:
	Transform transform;
	ToolOnlyAnimClip* currentClip;

	int _currentIndex;

	float _loadTime;

	string name;
};