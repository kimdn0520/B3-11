#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Animator;
class State;

class AngryAnimation : public MonoBehaviour
{
	friend class ENEMY_ANGRY;

public:
	AngryAnimation(GameObject* gameObject);
	~AngryAnimation();

private:
	GameObject* _enemyObj;

	Animator* _animator;

public:
	virtual void FixedUpdate() override;//¹°¸®ÂÊ
	virtual void Update() override;

public:
	void AnimationPlay();
};