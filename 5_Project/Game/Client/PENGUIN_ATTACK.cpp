#include "pch.h"
#include "State.h"
#include "Penguin.h"
#include "PENGUIN_ATTACK.h"

PENGUIN_ATTACK::PENGUIN_ATTACK(Penguin* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("PenguinAttack")))
{

}

void PENGUIN_ATTACK::Start()
{
}

int PENGUIN_ATTACK::FixedUpdate()
{
	if (ref->_isHit)
		return Penguin::HIT;

	if (ref->_isInDetect)
		return Penguin::RUN;

	if (ref->_attackCoolTime >= 1.f)
	{
		ref->_attackCoolTime = 0.f;
		ref->_moveDir = (ref->_playerTransform->GetLocalPosition() - ref->_transform->GetLocalPosition()).Normalized();
		ref->_rigidbody->AddForce(ref->_moveDir * 20.f);
	}

	return Penguin::ATTACK;
}

void PENGUIN_ATTACK::Update()
{
	ref->_animator->Play(animClip);
}

void PENGUIN_ATTACK::End()
{

}
