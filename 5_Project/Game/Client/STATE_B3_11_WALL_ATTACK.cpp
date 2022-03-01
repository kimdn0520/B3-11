#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_WALL_ATTACK.h"

STATE_B3_11_WALL_ATTACK::STATE_B3_11_WALL_ATTACK(B3_11* ref)
	:ref(ref), animClip{}
{
	animClip[0] = AnimClipLoader::LoadClip(AnimClipPath("BellWallAttack"));
	animClip[1] = AnimClipLoader::LoadClip(AnimClipPath("BellWallAttack2"));
	animClip[2] = AnimClipLoader::LoadClip(AnimClipPath("BellWallAttack3"));
	animClip[3] = AnimClipLoader::LoadClip(AnimClipPath("BellWallAttack4"));
}

void STATE_B3_11_WALL_ATTACK::Start()
{
	ref->_bCheckWall = true;

	ref->_wallEscapeTimer = 0.0f;


	ref->_rigidbody->SetLinearDragY(1.0f);
	ref->_rigidbody->SetVelocityX(0);
	if(ref->_groundWay[1])
		ref->_face = 1;
	else
		ref->_face = -1;
	ref->_transform->SetLocalScale(Vector2(ref->_face, 1));


	ref->_shootWay = -1;
}

int STATE_B3_11_WALL_ATTACK::FixedUpdate()
{

	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_bJumpEntry)  // 벽타기중에 점프시? 
		return B3_11::JUMP_ATTACK;

	if (ref->_bCheckGround)
		return B3_11::WALK_ATTACK;

	if (!ref->_bCheckWall)
		return B3_11::FALL_ATTACK;

	if (ref->_wallEscapeTimer > ref->_wallEscapeTime)
		return B3_11::FALL_ATTACK;

	if ((ref->_wallEscapeTimer > ref->_wallEscapeTime &&
		(ref->_input == 1 && ref->_groundWay[1])) ||
		(ref->_wallEscapeTimer > ref->_wallEscapeTime &&
			(ref->_input == -1 && ref->_groundWay[2])))
		return B3_11::FALL_ATTACK;

	if (!ref->_isAttacking)
		return B3_11::WALL;


	ref->_bOnWall = true;
	ref->_shootWay = -1;


	if (ref->_groundWay[1] && !INPUT->GetButton(KEY_TYPE::LEFT) ||
		ref->_groundWay[2] && !INPUT->GetButton(KEY_TYPE::RIGHT))
	{
		ref->_wallEscapeTimer += DELTA_TIME;
	}

	if (ref->_groundWay[1] && INPUT->GetButton(KEY_TYPE::LEFT) ||
		ref->_groundWay[2] && INPUT->GetButton(KEY_TYPE::RIGHT))
	{
		ref->_wallEscapeTimer = 0.0f;
	}

	return B3_11::WALL_ATTACK;
}

void STATE_B3_11_WALL_ATTACK::Update()
{
	ref->_animator->ContinuosPlay(animClip[ref->_chargeLevel]);
}

void STATE_B3_11_WALL_ATTACK::End()
{

	ref->_bOnWall = false;
	ref->_shootWay = 1;

	ref->_rigidbody->SetLinearDragY(ref->_defaultLinearDragY);

	if (ref->_groundWay[1])
		ref->_face = 1.0f;
	else
		ref->_face = -1.0f;
}


