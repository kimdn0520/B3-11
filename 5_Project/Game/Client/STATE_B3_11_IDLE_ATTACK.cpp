#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_IDLE_ATTACK.h"

STATE_B3_11_IDLE_ATTACK::STATE_B3_11_IDLE_ATTACK(B3_11* ref)
	:ref(ref), animClip{}
{
	animClip[0] = AnimClipLoader::LoadClip(AnimClipPath("BellAttack"));
	animClip[1] = AnimClipLoader::LoadClip(AnimClipPath("IdleAttack2"));
	animClip[2] = AnimClipLoader::LoadClip(AnimClipPath("IdleAttack3"));
	animClip[3] = AnimClipLoader::LoadClip(AnimClipPath("IdleAttack4"));
}

void STATE_B3_11_IDLE_ATTACK::Start()
{
	ref->_rigidbody->SetGravityScale(0.0f);
	ref->_rigidbody->SetVelocityY(0.0f);
}

int STATE_B3_11_IDLE_ATTACK::FixedUpdate()
{

	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_input != 0)
		return B3_11::WALK_ATTACK;

	if (ref->_bJumpEntry)
		return B3_11::JUMP_ATTACK;

	if (!ref->_bCheckGround)
		return B3_11::FALL_ATTACK;

	if (!ref->_isAttacking)
		return B3_11::IDLE;


	////물리 구현
	//Vector2 forceDir = { static_cast<float>(ref->_input) , 0 };

	//ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	//ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);


	return B3_11::IDLE_ATTACK;
}

void STATE_B3_11_IDLE_ATTACK::Update()
{
	ref->_animator->ContinuosPlay(animClip[ref->_chargeLevel]);
}

void STATE_B3_11_IDLE_ATTACK::End()
{
	ref->_rigidbody->SetGravityScale(ref->_defaultGravityScale);
}
