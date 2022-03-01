#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class AnimationClip;
class Animator;
class Text;

class BrokenWall : public MonoBehaviour
{
public:
	BrokenWall(GameObject* gameObject);
	~BrokenWall();

private:
	GameObject* _gameObject;
	Transform* _transform;
	AnimationClip* _animClip;
	Animator* _animator;

	float _damage;
	const float _destroyDelay;
	float _destroyTimer;

	bool _isDestroy;
	bool _soundPlay;

private:
	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void Update() override;
};

