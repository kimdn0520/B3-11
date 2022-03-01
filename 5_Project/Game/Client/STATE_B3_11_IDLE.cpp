#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_IDLE.h"

STATE_B3_11_IDLE::STATE_B3_11_IDLE(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("B3_11_IDLE")))
{
}

void STATE_B3_11_IDLE::Start()
{
	ref->_rigidbody->SetGravityScale(0.0f);
	ref->_rigidbody->SetVelocityY(0.0f);
}

int STATE_B3_11_IDLE::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_input != 0)
		return B3_11::WALK;

	if (ref->_bJumpEntry)
		return B3_11::JUMP;

	if (!ref->_bCheckGround)
		return B3_11::FALL;

	if (ref->_isAttacking)
		return B3_11::IDLE_ATTACK;


	//ref->_transform->Translate({ ref->_transform->GetLocalPosition().x, ref->_transform->GetLocalPosition().y - 0.1f });

	return B3_11::IDLE;
}

void STATE_B3_11_IDLE::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_IDLE::End()
{
	ref->_rigidbody->SetGravityScale(ref->_defaultGravityScale);
}
