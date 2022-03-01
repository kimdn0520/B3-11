#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_WALK_ATTACK.h"

STATE_B3_11_WALK_ATTACK::STATE_B3_11_WALK_ATTACK(B3_11* ref)
	:ref(ref), animClip{}
{
	animClip[0] = AnimClipLoader::LoadClip(AnimClipPath("BellWalkAttack"));
	animClip[1] = AnimClipLoader::LoadClip(AnimClipPath("WalkAttack2"));
	animClip[2] = AnimClipLoader::LoadClip(AnimClipPath("WalkAttack3"));
	animClip[3] = AnimClipLoader::LoadClip(AnimClipPath("WalkAttack4"));
}

void STATE_B3_11_WALK_ATTACK::Start()
{
	SOUND_MANAGER->PlayerMove();
	ref->_walkSoundTimer += DELTA_TIME;
	ref->_rigidbody->SetGravityScale(0.0f);
	ref->_rigidbody->SetVelocityY(0);
}

int STATE_B3_11_WALK_ATTACK::FixedUpdate()
{

	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_input == 0)
		return B3_11::IDLE_ATTACK;

	if (!ref->_bCheckGround)
		return B3_11::FALL_ATTACK;

	if (ref->_bJumpEntry)
		return B3_11::JUMP_ATTACK;

	if (!ref->_isAttacking)
		return B3_11::WALK;


	//물리 구현
	Vector2 forceDir = { static_cast<float>(ref->_input) , 0 };

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_input), ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);

	if (ref->_bCheckWall &&
		(ref->_boxCollider->GetColDirVec()[1] && ref->_input == -1) ||
		(ref->_boxCollider->GetColDirVec()[2] && ref->_input == 1))
	{
		ref->_rigidbody->SetVelocityX(0);
	}
	return B3_11::WALK_ATTACK;
}

void STATE_B3_11_WALK_ATTACK::Update()
{
	ref->_animator->ContinuosPlay(animClip[ref->_chargeLevel]);
	if (ref->_walkSoundTimer >= ref->_walkSoundCoolTime)
	{
		ref->_walkSoundTimer = 0;
		SOUND_MANAGER->PlayerMove();
	}
}

void STATE_B3_11_WALK_ATTACK::End()
{
	ref->_rigidbody->SetGravityScale(ref->_defaultGravityScale);
}
