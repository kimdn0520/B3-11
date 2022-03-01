#include "pch.h"
#include "State.h"
#include "Penguin.h"
#include "PENGUIN_RUN.h"

PENGUIN_RUN::PENGUIN_RUN(Penguin* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("PenguinMove")))
{

}

void PENGUIN_RUN::Start()
{
	SOUND_MANAGER->PenguinAlert();
}

int PENGUIN_RUN::FixedUpdate()
{
	if (ref->_isHit)
		return Penguin::HIT;

	if (ref->_isInAtkDetect)
		return Penguin::ATTACK;

	if (!(ref->_isInDetect))
		return Penguin::WALK;


	ref->_moveDir = (ref->_playerTransform->GetLocalPosition() - ref->_transform->GetLocalPosition()).Normalized();

	if (ref->_moveDir.x > 0) { ref->_face = 1.f; }
	else if (ref->_moveDir.x < 0) { ref->_face = -1.f; }

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_transform->Translate(ref->_moveDir * ref->_speed * DELTA_TIME);

	return Penguin::RUN;
}

void PENGUIN_RUN::Update()
{
	ref->_animator->Play(animClip);
}

void PENGUIN_RUN::End()
{

}
