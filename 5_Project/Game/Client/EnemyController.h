#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Animator;
class Text;

class EnemyController : public MonoBehaviour
{
public:
	EnemyController(GameObject* gameObject);
	~EnemyController();

private:
	Transform* _transform;

	Animator* _animator;

	Text* _text;

	int _hp;
	int _damage;

private:
	void Move();
	void AnimationUpdate();
	
	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnCollisionStay(ColliderBase* collider) override;
	virtual void OnCollisionExit(ColliderBase* collider) override;
	virtual void OnTriggerEnter(ColliderBase* collider) override;

	virtual void Update() override;
	virtual void FixedUpdate() override;
};

