#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_FALL_ATTACK.h"

STATE_B3_11_FALL_ATTACK::STATE_B3_11_FALL_ATTACK(B3_11* ref)
	:ref(ref), animClip{}
{
	animClip[0] = AnimClipLoader::LoadClip(AnimClipPath("FallAttack1"));
	animClip[1] = AnimClipLoader::LoadClip(AnimClipPath("FallAttack2"));
	animClip[2] = AnimClipLoader::LoadClip(AnimClipPath("FallAttack3"));
	animClip[3] = AnimClipLoader::LoadClip(AnimClipPath("FallAttack4"));
}

void STATE_B3_11_FALL_ATTACK::Start()
{
}

int STATE_B3_11_FALL_ATTACK::FixedUpdate()
{

	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_bCheckGround)
		return B3_11::IDLE_ATTACK;

	if ((ref->_groundWay[1] && ref->_input == -1) ||
		(ref->_groundWay[2] && ref->_input == 1))
		return B3_11::WALL_ATTACK;

	if (!ref->_isAttacking)
			return B3_11::FALL;

	//물리 구현
	Vector2 forceDir = { static_cast<float>(ref->_input) , 0 };

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);


	return B3_11::FALL_ATTACK;
}

void STATE_B3_11_FALL_ATTACK::Update()
{
	ref->_animator->ContinuosPlay(animClip[ref->_chargeLevel]);
}

void STATE_B3_11_FALL_ATTACK::End()
{
}
