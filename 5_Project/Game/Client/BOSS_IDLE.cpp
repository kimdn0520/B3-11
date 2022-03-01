#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_IDLE.h"

BOSS_IDLE::BOSS_IDLE(Boss* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossIdle")))
{}

void BOSS_IDLE::Start()
{
	
}

int BOSS_IDLE::FixedUpdate()
{
	if (ref->_isHit)
		return Boss::HIT;

	ref->_attackCoolTime += DELTA_TIME;
	
	// 공격쿨타임이 돌아오면
	if (ref->_attackCoolTime >= 5.f)
	{
		ref->_attackCoolTime = 0;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 3);  // 1, 2, 3

		int randomAtk = dis(gen);

		if (randomAtk == (int)Boss::HORIZONTAL_ATTACK)
		{
			ref->_isHorizontalAtk = true;
			return Boss::HORIZONTAL_ATTACK;
		}
		else if (randomAtk == (int)Boss::VERTICALL_ATTACK)
		{
			ref->_isVerticalAtk = true;
			return Boss::VERTICALL_ATTACK;
		}
		else if (randomAtk == (int)Boss::ENEMY_SUMMON)
		{
			ref->_isEnemySummon = true;
			return Boss::ENEMY_SUMMON;
		}
	}

	return Boss::IDLE;
}

void BOSS_IDLE::Update()
{
	ref->_animator->Play(animClip);
}

void BOSS_IDLE::End()
{
}
