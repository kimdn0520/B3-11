#include "pch.h"
#include "State.h"
#include "JellyFish.h"
#include "JELLYFISH_HIT.h"

JELLYFISH_HIT::JELLYFISH_HIT(JellyFish* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("JellyfishMove")))
{
}

void JELLYFISH_HIT::Start()
{
	ref->_hp -= ref->_hittedDmg;
}

int JELLYFISH_HIT::FixedUpdate()
{
	if (ref->_hp <= 0)
		return JellyFish::GAME_OVER;

	ref->_isHit = false;

	if (!(ref->_isInDetect))
		return JellyFish::WALK;

	return JellyFish::HIT;
}

void JELLYFISH_HIT::Update()
{
	ref->_animator->Play(animClip);
}

void JELLYFISH_HIT::End()
{
}
