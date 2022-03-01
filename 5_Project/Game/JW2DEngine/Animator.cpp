#include "pch.h"
#include "JW2DEngine.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "Sprite.h"

Animator::Animator(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::ANIMATOR), _currentCilp(nullptr),
	  _currentIndex(0), _totalFrameOfClip(0), _loadTime(0.f), _name(""), _isPlay(true), _isRender(true)
{
	_transform = gameObject->GetComponent<Transform>();
}

Animator::~Animator()
{}

void Animator::CreateAnimClip(string name)
{
	_aniClipData.insert({ name, new AnimationClip() });
}

void Animator::AddAnimClip(string name, AnimationClip* animClip)
{
	_aniClipData.insert({ name,animClip });
}

void Animator::InputClipData(string name, Sprite* sprite)
{
	_aniClipData[name]->SetSpriteAnimData(sprite);
}

void Animator::Play(const string& name)
{
	if(_name != name)
	{ 
		_name = name;

		_totalFrameOfClip = _aniClipData[_name]->GetAnimTotalFrame();
		_currentIndex = 0;
	}
	_isPlay = true;
}

void Animator::Play(AnimationClip* clip)
{
	if (_currentCilp != clip)
	{
		_currentCilp = clip;

		_totalFrameOfClip = clip->GetAnimTotalFrame();
		_currentIndex = 0;
	}
	_isPlay = true;
}

void Animator::FinalUpdate()
{
	if (_name != "" && _isPlay && _isRender)
	{
		GEngine->DrawSprite
		(
			_aniClipData[_name]->GetFrame(_currentIndex),
			_transform
		);

		// 시간 누적
		_loadTime += DELTA_TIME;

		// 스프라이트가 가지고있는 delayTime과 loadTime으로 적절히 잘 출력 
		if (_loadTime >= _aniClipData[_name]->GetFrame(_currentIndex)->delayTime)
		{
			_currentIndex = (_currentIndex + 1) % _totalFrameOfClip;
			_loadTime = 0.f;
		}

		return;
	}

	if (_currentCilp != nullptr && _isPlay && _isRender)
	{
		GEngine->DrawSprite
		(
			_currentCilp->GetFrame(_currentIndex),
			_transform
		);

		// 시간 누적
		_loadTime += DELTA_TIME;

		// 스프라이트가 가지고있는 delayTime과 loadTime으로 적절히 잘 출력 
		if (_loadTime >= _currentCilp->GetFrame(_currentIndex)->delayTime)
		{
			_currentIndex = (_currentIndex + 1) % _totalFrameOfClip;
			_loadTime = 0.f;
		}

		return;
	}



}

void Animator::ContinuosPlay(AnimationClip* clip)
{
	if (_currentCilp != clip)
	{
		_currentCilp = clip;

		_totalFrameOfClip = clip->GetAnimTotalFrame();
	}
}
