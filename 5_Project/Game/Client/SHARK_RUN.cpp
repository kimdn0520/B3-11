#include "pch.h"
#include "State.h"
#include "Shark.h"
#include "SHARK_RUN.h"

SHARK_RUN::SHARK_RUN(Shark* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("SharkMove")))
{}

void SHARK_RUN::Start()
{
	SOUND_MANAGER->SharkAlert();
	ref->_speed = 200.f;
}

int SHARK_RUN::FixedUpdate()
{
	if (ref->_isHit)
		return Shark::HIT;
	
	if (ref->_isInAtkDetect)
		return Shark::ATTACK;
	
	if (!(ref->_isInDetect))
		return Shark::WALK;


	ref->_moveDir = (ref->_playerTransform->GetLocalPosition() - ref->_transform->GetLocalPosition()).Normalized();

	if (ref->_moveDir.x > 0) { ref->_face = 1.f; }
	else if (ref->_moveDir.x < 0) { ref->_face = -1.f; }

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_transform->Translate(ref->_moveDir * ref->_speed * DELTA_TIME);

	return Shark::RUN;
}

void SHARK_RUN::Update()
{
	ref->_animator->Play(animClip);
}

void SHARK_RUN::End()
{
}
