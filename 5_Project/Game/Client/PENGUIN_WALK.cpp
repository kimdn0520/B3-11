#include "pch.h"
#include "State.h"
#include "Penguin.h"
#include "PENGUIN_WALK.h"

PENGUIN_WALK::PENGUIN_WALK(Penguin* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("PenguinMove")))
{

}

void PENGUIN_WALK::Start()
{
}

int PENGUIN_WALK::FixedUpdate()
{
	if (ref->_isHit)
		return Penguin::HIT;

	if (ref->_isInDetect)
		return Penguin::RUN;

	if (ref->_isInAtkDetect)
		return Penguin::ATTACK;

	ref->_moveTimer += DELTA_TIME;

	if (ref->_moveTimer >= 2.f)
	{
		ref->_moveTimer = 0;
		// 랜덤한 값을 넣어주자.
		// _h = -1, 0, 1   _v = -1, 0, 1
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(-1, 1);

		ref->_h = dis(gen);
		ref->_moveDir = Vector2(ref->_h, 0);

		if (ref->_h > 0) { ref->_face = 1.f; }
		else if (ref->_h < 0) { ref->_face = -1.f; }
	}

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_transform->Translate(ref->_moveDir * ref->_speed * DELTA_TIME);

	return Penguin::WALK;
}

void PENGUIN_WALK::Update()
{
	ref->_animator->Play(animClip);
}

void PENGUIN_WALK::End()
{

}
