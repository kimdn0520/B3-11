#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class AnimationClip;
class Animator;
class Text;


class Lazer : public MonoBehaviour
{
public:
	Lazer(GameObject* gameObject);
	~Lazer();

private:
	GameObject* _gameObject;

	Transform* _transform;

	AnimationClip* _animClip;

	Animator* _animator;

	bool _doDamage;

private:
	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerStay(ColliderBase* collider) override;

	virtual void FixedUpdate() override;
	virtual void Update() override;

};

