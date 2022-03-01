#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class AnimationClip;
class Animator;
class Text;

class Hurdle : public MonoBehaviour
{
public:
	Hurdle(GameObject* gameObject);
	~Hurdle();

private:
	GameObject* _gameObject;
	Transform* _transform;
	AnimationClip* _animClip;
	Animator* _animator;

	float _speed;				// 톱니바퀴 움직일 때 속도
	float _moveTimer;
	float _damage;

	Vector2 _moveDir = { 0.f, 0.f };			// 움직일 방향
	float _h;
	float _v;

	bool _isbossScene = false;

private:
	void Move();
	

	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerStay(ColliderBase* collider) override;

	virtual void FixedUpdate() override;
	virtual void Update() override;

public:
	void SetIsBossScene(bool value) { _isbossScene = value; }
	void SetMoveDir(Vector2 value) { _moveDir = value; }
};

