#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_JUMP_ATTACK.h"

STATE_B3_11_JUMP_ATTACK::STATE_B3_11_JUMP_ATTACK(B3_11* ref)
	:ref(ref), animClip{}
{
	animClip[0] = AnimClipLoader::LoadClip(AnimClipPath("JumpAttack1"));
	animClip[1] = AnimClipLoader::LoadClip(AnimClipPath("JumpAttack2"));
	animClip[2] = AnimClipLoader::LoadClip(AnimClipPath("JumpAttack3"));
	animClip[3] = AnimClipLoader::LoadClip(AnimClipPath("JumpAttack4"));
}

void STATE_B3_11_JUMP_ATTACK::Start()
{
	if (ref->_bJumpEntry)
	{
		SOUND_MANAGER->PlayerWallJump();
		if ((ref->_groundWay[1] ||
			ref->_groundWay[2]) && !ref->_bCheckGround)
		{
			Vector2 temp = {};
			if (ref->_groundWay[1])
				temp = { 1, -2 };
			else
				temp = { -1, -2 };
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

int STATE_B3_11_JUMP_ATTACK::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_rigidbody->GetVelocity().y >= 0)
		return B3_11::FALL_ATTACK;

	if (!ref->_isAttacking)
		return B3_11::JUMP;

	if (ref->_isJumping &&
		((ref->_jumpTimer < ref->_jumpTime) &&
			ref->_bJumpKeyPressed))
	{
		ref->_jumpTimer += DELTA_TIME;
		ref->_rigidbody->AddForce(Vector2::Up * 3.0f);
	}
	else
		ref->_isJumping = false;

	//물리 구현
	Vector2 forceDir = { static_cast<float>(ref->_input) , 0 };

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);


	return B3_11::JUMP_ATTACK;
}

void STATE_B3_11_JUMP_ATTACK::Update()
{
	ref->_animator->ContinuosPlay(animClip[ref->_chargeLevel]);
}

void STATE_B3_11_JUMP_ATTACK::End()
{
}
