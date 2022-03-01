#include "pch.h"
#include "State.h"
#include "Penguin.h"
#include "PENGUIN_HIT.h"

PENGUIN_HIT::PENGUIN_HIT(Penguin* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("PenguinMove")))
{

}

void PENGUIN_HIT::Start()
{
	ref->_hp -= ref->_hittedDmg;
}

int PENGUIN_HIT::FixedUpdate()
{
	if (ref->_hp <= 0)
		return Penguin::GAME_OVER;

	ref->_isHit = false;

	if (ref->_isInAtkDetect)
		return Penguin::ATTACK;

	if (ref->_isInDetect)
		return Penguin::RUN;

	if (!(ref->_isInDetect))
		return Penguin::WALK;

	return Penguin::HIT;
}

void PENGUIN_HIT::Update()
{
	ref->_animator->Play(animClip);
}

void PENGUIN_HIT::End()
{

}
