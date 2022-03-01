#include "pch.h"
#include "AnimationClip.h"

AnimationClip::AnimationClip()
{
	
}

AnimationClip::~AnimationClip()
{}

void AnimationClip::SetSpriteAnimData(Sprite* sprite)
{
	_spriteAnim.push_back(sprite);
}

Sprite* AnimationClip::GetFrame(int index)
{
	if ((index < 0) || (index >= _spriteAnim.size()))
		return _spriteAnim[0];

	return _spriteAnim[index];
}

int AnimationClip::GetAnimTotalFrame()
{
	return _spriteAnim.size();
}
