#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_FALL.h"

STATE_B3_11_FALL::STATE_B3_11_FALL(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellFalling")))
{
}

void STATE_B3_11_FALL::Start()
{
}

int STATE_B3_11_FALL::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;


	if (ref->_bCheckGround)
		return B3_11::IDLE;

	if ((ref->_groundWay[1] && ref->_input == -1) ||
		(ref->_groundWay[2] && ref->_input == 1))
		return B3_11::WALL;


	if (ref->_isAttacking)
		return B3_11::FALL_ATTACK;


	//물리 관련 함수 호출 장소
	Vector2 forceDir = { (ref->_input) , 0 };

	ref->_transform->SetLocalScale({ ref->_face, ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);

	return B3_11::FALL;
}

void STATE_B3_11_FALL::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_FALL::End()
{
}
