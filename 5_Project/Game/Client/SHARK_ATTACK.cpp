#include "pch.h"
#include "State.h"
#include "Shark.h"
#include "SHARK_ATTACK.h"

SHARK_ATTACK::SHARK_ATTACK(Shark* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("SharkAttack")))
{}

void SHARK_ATTACK::Start()
{
	ref->_speed = 70.f;
}

int SHARK_ATTACK::FixedUpdate()
{
	if (ref->_isHit)
		return Shark::HIT;

	if (ref->_isInDetect)
		return Shark::RUN;

	if (ref->_attackCoolTime >= 1.f)
	{
		ref->_attackCoolTime = 0.f;
		ref->_moveDir = (ref->_playerTransform->GetLocalPosition() - ref->_transform->GetLocalPosition()).Normalized();

		if (ref->_moveDir.x > 0) { ref->_face = 1.f; }
		else if (ref->_moveDir.x < 0) { ref->_face = -1.f; }
		ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });

		ref->_rigidbody->AddForce(ref->_moveDir * 40.f);
	}

	return Shark::ATTACK;
}

void SHARK_ATTACK::Update()
{
	ref->_animator->Play(animClip);
}

void SHARK_ATTACK::End()
{
}
