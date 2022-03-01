#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_JUMP.h"

STATE_B3_11_JUMP::STATE_B3_11_JUMP(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellJump")))
{
}

void STATE_B3_11_JUMP::Start()
{
	if (ref->_bJumpEntry)
	{
		SOUND_MANAGER->PlayerWallJump();
		if ((ref->_groundWay[1] ||
			ref->_groundWay[2]) && !ref->_bCheckGround)
		{
			Vector2 temp = {};
			if (ref->_groundWay[1])
				temp = { 1, -1.5f };
			else
				temp = { -1, -1.5f };
			ref->_rigidbody->AddForce(temp.Normalized() * ref->_wallJumpPower);
			ref->_isJumping = false;
		}
		else
		{
			ref->_jumpTimer = 0.0f;
			ref->_rigidbody->AddForce(Vector2::Up * ref->_jumpPower);
			ref->_isJumping = true;
		}
	}
	ref->_bJumpEntry = false;
	ref->_bJumpKeyPressed = true;
}

int STATE_B3_11_JUMP::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_rigidbody->GetVelocity().y >= 0)
		return B3_11::FALL;

	if (ref->_isAttacking)
		return B3_11::JUMP_ATTACK;

	//물리 관련 함수 호출 장소

	if (ref->_isJumping &&
		((ref->_jumpTimer < ref->_jumpTime) &&
			ref->_bJumpKeyPressed))
	{
		ref->_jumpTimer += DELTA_TIME;
		ref->_rigidbody->AddForce(Vector2::Up * 3.0f);
	}
	else
		ref->_isJumping = false;

	Vector2 forceDir = { (ref->_input) , 0 };

	ref->_transform->SetLocalScale({ ref->_face, ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);


	return B3_11::JUMP;
}

void STATE_B3_11_JUMP::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_JUMP::End()
{
}
