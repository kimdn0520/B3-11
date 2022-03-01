#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_ENEMY_SUMMON.h"
#include "EnemyPrefab.h"
#include "Shark.h"
#include "UIManager.h"

BOSS_ENEMY_SUMMON::BOSS_ENEMY_SUMMON(Boss* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossAttack")))
{
}

void BOSS_ENEMY_SUMMON::Start()
{
}

int BOSS_ENEMY_SUMMON::FixedUpdate()
{
	if (ref->_isHit)
		return Boss::HIT;

	if (ref->_attackDelay >= 2.0f)
	{
		{
			ref->_attackDelay = 0;
			return Boss::IDLE;
		}
	}

	ref->_attackDelay += DELTA_TIME;

	if (ref->_isEnemySummon)
	{
		for (int i = 0; i < 2; i++)
		{
			EnemyPrefab* enemyObj = new EnemyPrefab("Shark", Vector2(128.f * 4 + 256 * i, 128.f * 16 - 256 * i), 240, 150);
			enemyObj->AddComponent<Shark>();
			enemyObj->GetScriptComponent<Shark>()->SetPlayerTransform(GET_SINGLE(UIManager)->GetPlayerTransform());
		}

		ref->_isEnemySummon = false;
	}

	return Boss::ENEMY_SUMMON;
}

void BOSS_ENEMY_SUMMON::Update()
{
	ref->_animator->Play(animClip);
}

void BOSS_ENEMY_SUMMON::End()
{
}
