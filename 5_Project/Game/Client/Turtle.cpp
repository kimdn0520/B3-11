#include "pch.h"
#include "prefab.h"
#include "Turtle.h"
#include "AnimClipLoader.h"
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "Player.h"

Turtle::Turtle(GameObject* gameObject)
	:MonoBehaviour(gameObject),
	_hp(3), _damage(1), _speed(80.f), _moveTimer(0.f), _h(1.f),
	_scale(_transform->GetLocalScale()),
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>()),
	_rigidbody(gameObject->GetComponent<Rigidbody>()),
	_animClip1(AnimClipLoader::LoadClip(AnimClipPath("TurtleMove"))),
	_animClip2(AnimClipLoader::LoadClip(AnimClipPath("TurtleDead"))),
	_boxCollider(gameObject->GetComponent<BoxCollider>())
{
}

Turtle::~Turtle()
{
}

void Turtle::Update()
{
	AnimationUpdate();
}

void Turtle::FixedUpdate()
{
	Move();
}


void Turtle::Move()
{
	if (_hp <= 0)
	{
		_transform->Translate(0, 0);
	}
	else
	{
		_moveTimer += DELTA_TIME;

		if (_moveTimer >= 6.f)
		{
			_moveTimer = 0;
			_h = -_h;
		}

		_moveDir = Vector2(_h, 0);
		_transform->Translate(_moveDir * _speed * DELTA_TIME);

	}

}

void Turtle::AnimationUpdate()
{
	if (_hp <= 0)
	{
		_animator->Play(_animClip2);
	}
	else
	{
		_animator->Play(_animClip1);

		if (_h == 1)
		{
			_transform->SetLocalScale(Vector2(1 * _scale.x, _scale.y));

		}
		else if (_h == -1)
		{
			_transform->SetLocalScale(Vector2(-1 * _scale.x, _scale.y));

		}

	}
}


void Turtle::OnCollisionEnter(ColliderBase* collider)
{

}

void Turtle::OnCollisionStay(ColliderBase* collider)
{
}

void Turtle::OnCollisionExit(ColliderBase* collider)
{
}

void Turtle::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet))
	{
		_hp -= collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet();

		if (_hp <= 0)
		{
			// 체력이 끝나면 적 자체를 삭제(임시방편)
			_boxCollider->SetTrigger(true);
			_rigidbody->OnGravity(false);
			Destroy(GetGameObject(), 0.5f);

			// 나중에는 적도 오브젝트 풀로 변경해줘야 함
			//GetGameObject()->SetActive(false);
			//GET_SINGLE(ObjectPool)->ReturnObject(this->GetGameObject());
		}
	}
}
