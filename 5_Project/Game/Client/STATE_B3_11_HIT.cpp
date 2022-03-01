#include "pch.h"
#include "State.h"
#include "B3_11.h"
#include "STATE_B3_11_HIT.h"

STATE_B3_11_HIT::STATE_B3_11_HIT(B3_11* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BellHit")))
{
}

void STATE_B3_11_HIT::Start()
{
 	ref->_hp--;
	ref->_transform->SetLocalScale({ ref->_face, ref->_transform->GetLocalScale().y });
	ref->_rigidbody->AddForce(ref->_knockBackDiagonal * ref->_knockBackPower);
	ref->_hitTimer = 0.0f;
	ref->_invincibleTimer = 0.0f;
}

int STATE_B3_11_HIT::FixedUpdate()
{
	ref->_invincible = true;
	if (ref->_hp <= 0)
		return B3_11::GAME_OVER;

	if (ref->_hitTimer >= ref->_recoveryTime)
		return B3_11::IDLE;


	ref->_hitTimer += DELTA_TIME;

	return B3_11::HIT;
}

void STATE_B3_11_HIT::Update()
{
	ref->_animator->Play(animClip);
}

void STATE_B3_11_HIT::End()
{
	ref->_hitTimer = 0.0f;
}
