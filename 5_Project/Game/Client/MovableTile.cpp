#include "pch.h"
#include "MovableTile.h"
#include "Input.h"
#include "Timer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Text.h"
#include "ColliderBase.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BulletPrefab.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "ObjectPool.h"

MovableTile::MovableTile(GameObject* gameObject)
	: MonoBehaviour(gameObject),
	_speed(500.f), _moveTimer(0.f), _h(-1.f), _moveTime(4.f),
	_scale(_transform->GetLocalScale()), _gameObject(nullptr),
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>()),
	_text(gameObject->GetComponent<Text>()),
	_boxCollider(gameObject->GetComponent<BoxCollider>())
{
	_boxCollider->SetTrigger(true);
}

MovableTile::~MovableTile()
{
}

void MovableTile::Move()
{
	//if (_gameObject->GetName() == "short")
	//	_moveTime = 3.f;

	_moveTimer += DELTA_TIME;
	if (_moveTimer >= _moveTime)
	{
		_moveTimer = 0;
		_h = -_h;
	}

	_moveDir = Vector2(0, _h);
	_transform->Translate(_moveDir * _speed * DELTA_TIME);
}

void MovableTile::OnCollisionEnter(ColliderBase* col)
{
}

void MovableTile::OnCollisionStay(ColliderBase* col)
{
	if (col->CompareTag(TAG::Player))
	{
		if (col->GetColDir() == (int)COL_DIR::DOWN)
		{
			col->GetTransform()->Translate(_moveDir * _speed * DELTA_TIME);
		}
	}
}

void MovableTile::OnCollisionExit(ColliderBase* col)
{
	_boxCollider->SetTrigger(true);
}

void MovableTile::OnTriggerEnter(ColliderBase* col)
{
	if (col->GetGameObject()->GetName() == "Player")
	{
		BoxCollider* playerBox = col->GetGameObject()->GetComponent<BoxCollider>();
		int this_x1 = (_boxCollider->GetPosition().x - (_boxCollider->GetWidth() / 2.0f));
		int this_x2 = (_boxCollider->GetPosition().x + (_boxCollider->GetWidth() / 2.0f));
		int this_y1 = (_boxCollider->GetPosition().y - (_boxCollider->GetHeight() / 2.0f));
		int this_y2 = (_boxCollider->GetPosition().y + (_boxCollider->GetHeight() / 2.0f));

		int other_x1 = (playerBox->GetPosition().x - (playerBox->GetWidth() / 2.0f));
		int other_x2 = (playerBox->GetPosition().x + (playerBox->GetWidth() / 2.0f));
		int other_y1 = (playerBox->GetPosition().y - (playerBox->GetHeight() / 2.0f));
		int other_y2 = (playerBox->GetPosition().y + (playerBox->GetHeight() / 2.0f));

		int minDiff = INT_MAX;
		int rightDiff = abs(this_x2 - other_x1);
		int leftDiff = abs(this_x1 - other_x2);
		int upDiff = abs(this_y1 - other_y2);
		int downDiff = abs(this_y2 - other_y1);

		minDiff = minDiff < rightDiff ? minDiff : rightDiff;
		minDiff = minDiff < leftDiff ? minDiff : leftDiff;
		minDiff = minDiff < downDiff ? minDiff : downDiff;
		minDiff = minDiff < upDiff ? minDiff : upDiff;

		if (minDiff == upDiff)
			_boxCollider->SetTrigger(false);
	}
}

void MovableTile::FixedUpdate()
{
	Move();
}

void MovableTile::Update()
{
}
