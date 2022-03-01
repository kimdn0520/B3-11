#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class AnimationClip;
class Text;

class Turtle : public MonoBehaviour
{
public: 
	Turtle(GameObject* gameObject);
	~Turtle();

private:
	Transform* _transform;

	GameObject* _gameObject;

	AnimationClip* _animClip1;
	AnimationClip* _animClip2;
	Animator* _animator;

	BoxCollider* _boxCollider;

	Rigidbody* _rigidbody;

	int _hp;
	int _damage;
	float _speed;
	float _moveTimer;
	float _h;

	Vector2 _moveDir;
	Vector2 _scale;

private:
	virtual void Update() override;
	virtual void FixedUpdate() override;
	
	void Move();
	void AnimationUpdate();

	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnCollisionStay(ColliderBase* collider) override;
	virtual void OnCollisionExit(ColliderBase* collider) override;
	virtual void OnTriggerEnter(ColliderBase* collider) override;

public:
	int GetDamage() {return _damage;}
};

