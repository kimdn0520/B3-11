#include "pch.h"
#include "BrokenWall.h"
#include "Player.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"
#include "ColliderBase.h"
#include "BoxRenderer.h"
#include "BoxCollider.h"
#include "CircleRenderer.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "State.h"
#include "Text.h"
#include "SpriteRenderer.h"
#include "EnemyPrefab.h"
#include "Penguin.h"
#include "Turtle.h"
#include "Shark.h"
#include "UIManager.h"


BrokenWall::BrokenWall(GameObject* gameObject)
	:MonoBehaviour(gameObject), _animClip(AnimClipLoader::LoadClip(AnimClipPath("GlassExplode"))), _destroyDelay(1.f), _destroyTimer(0.f), _isDestroy(false), _soundPlay(false),
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>())
{
}

BrokenWall::~BrokenWall()
{
}

void BrokenWall::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet))
	{
		if (collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet() >= 3)
		{
			_isDestroy = true;
		}
	}
}

void BrokenWall::Update()
{
	if (_isDestroy)
	{
		_gameObject->GetComponent<SpriteRenderer>()->SetRenderInactive();
		if (!_soundPlay)
		{
			SOUND_MANAGER->ObjectBreak();
			_soundPlay = true;
		}
		_destroyTimer += DELTA_TIME;
		_animator->Play(_animClip);
	}

	if (_destroyTimer >= _destroyDelay)
	{
		if (_gameObject->GetName() == "penguinGlass")
		{
			EnemyPrefab* enemyObj = new EnemyPrefab("Penguin", _transform->GetLocalPosition(), 120, 150);
			enemyObj->AddComponent<Penguin>();
			enemyObj->GetScriptComponent<Penguin>()->SetPlayerTransform(GET_SINGLE(UIManager)->GetPlayerTransform());
		}
		else if (_gameObject->GetName() == "sharkGlass")
		{
			EnemyPrefab* enemyObj = new EnemyPrefab("Shark", _transform->GetLocalPosition(), 240, 150);
			enemyObj->AddComponent<Shark>();
			enemyObj->GetScriptComponent<Shark>()->SetPlayerTransform(GET_SINGLE(UIManager)->GetPlayerTransform());
		}
		else if (_gameObject->GetName() == "turtleGlass")
		{
			EnemyPrefab* enemyObj = new EnemyPrefab("Turtle", _transform->GetLocalPosition(), 240, 150);
			enemyObj->AddComponent<Turtle>();
		}
		Destroy(GetGameObject());
		_destroyTimer = 0;
	}
}
