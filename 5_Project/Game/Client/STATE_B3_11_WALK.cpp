#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_WALK.h"

STATE_B3_11_WALK::STATE_B3_11_WALK(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellWalk")))
{
}

void STATE_B3_11_WALK::Start()
{
	SOUND_MANAGER->PlayerMove();
	ref->_walkSoundTimer += DELTA_TIME;
	ref->_rigidbody->SetGravityScale(0.0f);
	ref->_rigidbody->SetVelocity({ ref->_rigidbody->GetVelocity().x, 0.0f });
}

int STATE_B3_11_WALK::FixedUpdate()
{
	if (ref->_isDashing)
		return B3_11::DASH;

	if (ref->_bHit)
		return B3_11::HIT;

	if (ref->_input == 0)//todo : input ¸»°í velocity·Î
		return B3_11::IDLE;

	if (ref->_bJumpEntry)
		return B3_11::JUMP;

	if (ref->_isAttacking)
		return B3_11::WALK_ATTACK;

	if (!ref->_bCheckGround)
		return B3_11::FALL;


	Vector2 forceDir = { static_cast<float>(ref->_input) , 0 };

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_input), ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(forceDir * ref->_speed * DELTA_TIME);

	if(ref->_bCheckWall && 
		(ref->_boxCollider->GetColDirVec()[1] && ref->_input == -1) || 
		(ref->_boxCollider->GetColDirVec()[2] && ref->_input == 1))
	{
			ref->_rigidbody->SetVelocityX(0);
	}

    return B3_11::WALK;
}

void STATE_B3_11_WALK::Update()
{
	ref->_animator->Play(animClip);
	if (ref->_walkSoundTimer >= ref->_walkSoundCoolTime)
	{
		ref->_walkSoundTimer = 0;
		SOUND_MANAGER->PlayerMove();
	}
}

void STATE_B3_11_WALK::End()
{
	ref->_rigidbody->SetGravityScale(ref->_defaultGravityScale);
}
