#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_VERTICAL_ATTACK.h"
#include "HurdlePrefab.h"
#include "Hurdle.h"

BOSS_VERTICAL_ATTACK::BOSS_VERTICAL_ATTACK(Boss* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossAttack")))
{
}

void BOSS_VERTICAL_ATTACK::Start()
{
}

int BOSS_VERTICAL_ATTACK::FixedUpdate()
{
	if (ref->_isHit)
		return Boss::HIT;

	if (ref->_attackDelay >= 2.0f)
	{
		ref->_attackDelay = 0;
		return Boss::IDLE;
	}

	ref->_attackDelay += DELTA_TIME;

	if (ref->_isVerticalAtk)
	{
		for (int i = 0; i < 5; i++)
		{
			HurdlePrefab* hurdle = new HurdlePrefab("Saw", "Saw", 300.f + 130.f * i, 800.f, 128.f, 128.f);
			//hurdle->AddComponent<Hurdle>();
			hurdle->GetComponent<CircleCollider>()->SetTrigger(true);

			hurdle->GetScriptComponent<Hurdle>()->SetIsBossScene(true);
			hurdle->GetScriptComponent<Hurdle>()->SetMoveDir(Vector2(0, 1));
			hurdle->GetScriptComponent<Hurdle>()->Destroy(hurdle, 6.0f);
		}

		for (int i = 0; i < 4; i++)
		{
			HurdlePrefab* hurdle = new HurdlePrefab("Saw", "Saw", 1900.f + 130.f * i, 800.f, 128.f, 128.f);
			//hurdle->AddComponent<Hurdle>();
			hurdle->GetComponent<CircleCollider>()->SetTrigger(true);

			hurdle->GetScriptComponent<Hurdle>()->SetIsBossScene(true);
			hurdle->GetScriptComponent<Hurdle>()->SetMoveDir(Vector2(0, 1));
			hurdle->GetScriptComponent<Hurdle>()->Destroy(hurdle, 6.0f);
		}

		ref->_isVerticalAtk = false;
	}


	return Boss::VERTICALL_ATTACK;
}

void BOSS_VERTICAL_ATTACK::Update()
{
	ref->_animator->Play(animClip);
}

void BOSS_VERTICAL_ATTACK::End()
{
}
