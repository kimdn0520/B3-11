#include "pch.h"
#include "Bullet.h"
#include "Input.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"
#include "ColliderBase.h"
#include "ObjectPool.h"

Bullet::Bullet(GameObject* gameObject)
	: MonoBehaviour(gameObject), _bulletSpeed(18.f), _returnBullet(3.f), _checkReturnBullet(0.f), _damage(1.f), 
	_playerTransform(nullptr), _isShot(false),
	_transform(gameObject->GetComponent<Transform>())
{}

Bullet::~Bullet()
{}

void Bullet::Update()
{
	if (_isShot)
		_transform->SetLocalPosition(_transform->GetLocalPosition() + _pos * _bulletSpeed);


	_checkReturnBullet += DELTA_TIME;

	if (_checkReturnBullet >= _returnBullet)
	{
		_checkReturnBullet = 0;

		_pos = Vector2(0, 0);
		_playerTransform = nullptr;
		_isShot = false;
		Destroy(this->GetGameObject());
		
		//GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}

}

void Bullet::SetBulletInfo(Vector2 pos,Transform* player)
{
 	_pos = pos;

	_playerTransform = player;

	_checkReturnBullet = 0.0f;

	_isShot = true;
}

void Bullet::SetDamageBullet(float damage)
{
	_damage = damage;//TODO : 
}


void Bullet::OnCollisionEnter(ColliderBase* collider)
{

}

void Bullet::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Enemy))
	{
		_pos = Vector2(0, 0);		// 총알이 다시 오브젝트 풀로 돌아갔을 때 bool값을 초기화 해주려고 모두 false로 바꿔줌
		_isShot = false;
		Destroy(this->GetGameObject());
		//GetGameObject()->SetActive(false);
		//GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}
	else if (collider->CompareTag(TAG::Ground))
	{
		_pos = Vector2(0, 0);
		_isShot = false;
		Destroy(this->GetGameObject());
		//GetGameObject()->SetActive(false);
		//GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}
	else if (collider->CompareTag(TAG::BrokenWall))
	{
		OutputDebugString("총알 충돌!");
		_pos = Vector2(0, 0);
		_isShot = false;
		Destroy(this->GetGameObject());
		//GetGameObject()->SetActive(false);
		//GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}

}

