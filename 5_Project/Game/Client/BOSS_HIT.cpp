#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_HIT.h"

BOSS_HIT::BOSS_HIT(Boss* ref)
    :ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossIdle")))
{
}

void BOSS_HIT::Start()
{
    ref->_hp -= ref->_hittedDmg;
}

int BOSS_HIT::FixedUpdate()
{
	if (ref->_hp <= 0)
		return Boss::GAME_OVER;

	ref->_isHit = false;

	return Boss::IDLE;
}

void BOSS_HIT::Update()
{
    ref->_animator->Play(animClip);
}

void BOSS_HIT::End()
{
}
