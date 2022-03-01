#include "pch.h"
#include "Lazer.h"
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
#include "Text.h"
#include "State.h"
#include "SpritePrefab.h"
#include "B3_11.h"

Lazer::Lazer(GameObject* gameObject)
	:MonoBehaviour(gameObject), _animClip(AnimClipLoader::LoadClip(AnimClipPath(gameObject->GetName()))),
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_animator(gameObject->GetComponent<Animator>()),
	_doDamage(false)
{
	_gameObject->GetComponent<BoxCollider>()->SetTrigger(true);
	_animator->Play(_animClip);
}

Lazer::~Lazer()
{

}

void Lazer::OnTriggerEnter(ColliderBase* collider)
{
}

void Lazer::OnTriggerStay(ColliderBase* collider)
{
	if (_doDamage)
	{
		if (collider->GetGameObject()->GetName() == "Player")
		{
			B3_11* b3_11 = collider->GetGameObject()->GetScriptComponent<B3_11>();
			b3_11->_bHit = true;
			b3_11->_knockBackDiagonal = (b3_11->_boxCollider->GetTransform()->GetLocalPosition() - _gameObject->GetComponent<BoxCollider>()->GetTransform()->GetLocalPosition()).Normalized();
		}
	}
}

void Lazer::FixedUpdate()
{

}

void Lazer::Update()
{
	if (_animator->GetFrameIndex() >= 5 && _animator->GetFrameIndex() <= 13)
		_doDamage = true;
	else
		_doDamage = false;
}
