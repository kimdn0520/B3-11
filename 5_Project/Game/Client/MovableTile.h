#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class Text;
class BoxCollider;

class MovableTile : public MonoBehaviour
{
public:
	MovableTile(GameObject* gameObject);
	~MovableTile();

private:
	Transform* _transform;

	Rigidbody* _rigidbody;

	Animator* _animator;

	GameObject* _gameObject;

	Text* _text;

	GameObject* _tmpObj;

	Vector2 _scale;

	float _speed;				// Ÿ���� ������ �� �ӵ�
	float _moveTimer;
	float _moveTime;

	Vector2 _moveDir;			// ������ ����
	float _h;

	BoxCollider* _boxCollider;
private:
	void Move();

	virtual void OnCollisionEnter(ColliderBase* col) override;
	virtual void OnCollisionStay(ColliderBase* col) override;
	virtual void OnCollisionExit(ColliderBase* col) override;
	virtual void OnTriggerEnter(ColliderBase* col) override;
	

	virtual void FixedUpdate() override;

	virtual void Update() override;
};

