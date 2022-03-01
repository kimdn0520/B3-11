#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_WALL.h"

STATE_B3_11_WALL::STATE_B3_11_WALL(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellWall")))
{
}

void STATE_B3_11_WALL::Start()
{
	ref->_bCheckWall = true;

	ref->_wallEscapeTimer = 0.0f;

	ref->_rigidbody->SetLinearDragY(1.0f);
	ref->_rigidbody->SetVelocityX(0);
	if (ref->_groundWay[1])
		ref->_face = 1.0f;
	else
		ref->_face = -1.0f;
	ref->_transform->SetLocalScale(Vector2(ref->_face, 1));
	
	ref->_shootWay = -1;
}

int STATE_B3_11_WALL::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;
	
	if(ref->_bJumpEntry)  // 벽타기중에 점프시? 
		return B3_11::JUMP;

	if (ref->_bCheckGround)//todo : input 말고 velocity로
		return B3_11::WALK;

	if (!ref->_bCheckWall)
		return B3_11::FALL; 

	if(ref->_wallEscapeTimer > ref->_wallEscapeTime)
		return B3_11::FALL;

	if((ref->_wallEscapeTimer > ref->_wallEscapeTime && 
		(ref->_input == 1 && ref->_groundWay[1])) ||
		(ref->_wallEscapeTimer > ref->_wallEscapeTime &&
			(ref->_input == -1 && ref->_groundWay[2])))
		return B3_11::FALL;

	if (ref->_isAttacking)
		return B3_11::WALL_ATTACK;


	ref->_bOnWall = true;

	ref->_shootWay = -1;

	//물리 구현
	if (ref->_groundWay[1] && !INPUT->GetButton(KEY_TYPE::LEFT)||
		ref->_groundWay[2] && !INPUT->GetButton(KEY_TYPE::RIGHT))
	{
		ref->_wallEscapeTimer += DELTA_TIME;
	}

	if (ref->_groundWay[1] && INPUT->GetButton(KEY_TYPE::LEFT) ||
		ref->_groundWay[2] && INPUT->GetButton(KEY_TYPE::RIGHT))
	{
		ref->_wallEscapeTimer = 0.0f;
	}


	return B3_11::WALL;
}

void STATE_B3_11_WALL::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_WALL::End()
{

	ref->_bOnWall = false;
	ref->_shootWay = 1;

	ref->_rigidbody->SetLinearDragY(ref->_defaultLinearDragY);

	if (ref->_groundWay[1])
		ref->_face = 1.0f;
	else
		ref->_face = -1.0f;
}
