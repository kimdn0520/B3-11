#include "pch.h"
#include "Hurdle.h"
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
#include  "B3_11.h"

Hurdle::Hurdle(GameObject* gameObject)
	:MonoBehaviour(gameObject), _animClip(AnimClipLoader::LoadClip(AnimClipPath("Saw"))),
	_speed(280.f), _moveTimer(0.f), _h(5.f),
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>())
{
	_gameObject->GetComponent<CircleCollider>()->SetTrigger(true);
	_animator->Play(_animClip);
}

Hurdle::~Hurdle()
{
}

// 톱니바퀴가 일정시간동안 움직이게 하는 함수
void Hurdle::Move()
{
	_transform->Translate(_moveDir * _speed * DELTA_TIME);
}

void Hurdle::OnTriggerEnter(ColliderBase* collider)
{
}

void Hurdle::OnTriggerStay(ColliderBase* collider)
{
	if (collider->GetGameObject()->GetName() == "Player")
	{
		B3_11* b3_11 = collider->GetGameObject()->GetScriptComponent<B3_11>();
		b3_11->_bHit = true;
		b3_11->_knockBackDiagonal = (b3_11->_boxCollider->GetTransform()->GetLocalPosition() - _gameObject->GetComponent<CircleCollider>()->GetTransform()->GetLocalPosition()).Normalized();
	}
}

void Hurdle::FixedUpdate()
{
	if(_isbossScene)
		Move();
}

void Hurdle::Update()
{
}
