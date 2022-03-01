#pragma once
#include "MonoBehaviour.h"

class GameObject;

class Bullet : public MonoBehaviour
{
public:
	Bullet(GameObject* gameObject);
	~Bullet();

private:
	Transform* _transform;

	Transform* _playerTransform;

	bool _isShot;

	//ColliderBase* _boxCollider;

	float _bulletSpeed;
	float _checkReturnBullet;
	float _returnBullet;
	float _damage;

	Vector2 _pos;
public:

	void SetBulletInfo(Vector2 pos, Transform* player);

	float GetDamageBullet() {return _damage;}
	void SetDamageBullet(float damage);

	virtual void Update() override;

	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnTriggerEnter(ColliderBase* collider) override;
};

