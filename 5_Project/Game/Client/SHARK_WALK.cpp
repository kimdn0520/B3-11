#include "pch.h"
#include "State.h"
#include "Shark.h"
#include "SHARK_WALK.h"

SHARK_WALK::SHARK_WALK(Shark* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("SharkMove")))
{}

void SHARK_WALK::Start()
{
	ref->_speed = 70.f;
}

int SHARK_WALK::FixedUpdate()
{
	if(ref->_isHit)
		return Shark::HIT;
	
	if (ref->_isInDetect)
		return Shark::RUN;

	if(ref->_isInAtkDetect)
		return Shark::ATTACK;


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
		ref->_v = dis(gen);
		ref->_moveDir = Vector2(ref->_h, ref->_v);

		if(ref->_h > 0) { ref->_face = 1.f; }
		else if(ref->_h < 0) { ref->_face = -1.f; }
	}

	ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_transform->Translate(ref->_moveDir * ref->_speed * DELTA_TIME);

	return Shark::WALK;
}

void SHARK_WALK::Update()
{
	ref->_animator->Play(animClip);
}

void SHARK_WALK::End()
{}
