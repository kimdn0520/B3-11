#include "pch.h"
#include "EnemyController.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"
#include "ColliderBase.h"
#include "Text.h"
#include "ObjectPool.h"
#include "Bullet.h"

EnemyController::EnemyController(GameObject* gameObject)
	: MonoBehaviour(gameObject),
	_hp(100), _damage(1), 
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>()),
	_text(gameObject->GetComponent<Text>())
{}

EnemyController::~EnemyController()
{}

void EnemyController::Update()
{
	// _text->text = to_string(_hp);
}

void EnemyController::FixedUpdate()
{
	Move();
}

void EnemyController::Move()
{
	
}

void EnemyController::OnCollisionEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet))
	{
		// 원래는 플레이어 공격력 얻어와서 해야함 일단 대충 테슷흐
		_hp -= 10;

		GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}
}

void EnemyController::OnCollisionStay(ColliderBase* collider)
{
}

void EnemyController::OnCollisionExit(ColliderBase* collider)
{
}

void EnemyController::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet))
	{
		// 원래는 플레이어 공격력 얻어와서 해야함 일단 대충 테슷흐
		
		GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
	}
}