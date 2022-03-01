#pragma once
#include "MonoBehaviour.h"

class GameObject;

class AngryMotion : public MonoBehaviour
{
public:
	AngryMotion(GameObject* gameObject);
	~AngryMotion();

	void Set(GameObject* enemyObject) { _enemyObj = enemyObject;}
	void SetAnimation(GameObject* animationObj) { _animationObj = animationObj;}

private:
	GameObject* _enemyObj;

	GameObject* _animationObj;

	AnimationClip* _animClip;

private:
	virtual void Update() override;
};