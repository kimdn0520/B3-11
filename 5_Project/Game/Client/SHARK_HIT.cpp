#include "pch.h"
#include "State.h"
#include "Shark.h"
#include "SHARK_HIT.h"

SHARK_HIT::SHARK_HIT(Shark* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("SharkMove")))
{
}

void SHARK_HIT::Start()
{
	ref->_hp -= ref->_hittedDmg;
}

int SHARK_HIT::FixedUpdate()
{
	if (ref->_hp <= 0)
		return Shark::GAME_OVER;
	
	ref->_isHit = false;

	if (ref->_dist > 300.f && ref->_dist <= 800.f)
	{
		return Shark::RUN;
	}
	else if (ref->_dist <= 300.f)
	{
		return Shark::ATTACK;
	}
	else if (ref->_dist > 800.f)
	{
		return Shark::WALK;
	}

	return Shark::HIT;
}

void SHARK_HIT::Update()
{
}

void SHARK_HIT::End()
{
}
