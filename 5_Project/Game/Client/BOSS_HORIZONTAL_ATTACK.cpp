#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_HORIZONTAL_ATTACK.h"
#include "HurdlePrefab.h"
#include "Hurdle.h"

BOSS_HORIZONTAL_ATTACK::BOSS_HORIZONTAL_ATTACK(Boss* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossAttack")))
{}

void BOSS_HORIZONTAL_ATTACK::Start()
{
}

int BOSS_HORIZONTAL_ATTACK::FixedUpdate()
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

	if (ref->_isHorizontalAtk)
	{
		for (int i = 0; i < 5; i++)
		{
			HurdlePrefab* hurdle = new HurdlePrefab("Saw", "Saw", 300.f, 700.f + 130.f * i, 128.f, 128.f);
			hurdle->GetComponent<CircleCollider>()->SetTrigger(true);
			hurdle->AddComponent<Hurdle>();
			hurdle->GetScriptComponent<Hurdle>()->SetIsBossScene(true);
			hurdle->GetScriptComponent<Hurdle>()->SetMoveDir(Vector2(1, 0));
			hurdle->GetScriptComponent<Hurdle>()->Destroy(hurdle, 7.0f);
		}

		for (int i = 0; i < 4; i++)
		{
			HurdlePrefab* hurdle = new HurdlePrefab("Saw", "Saw", 300.f, 1900.f + 130.f * i, 128.f, 128.f);
			hurdle->GetComponent<CircleCollider>()->SetTrigger(true);
			hurdle->AddComponent<Hurdle>();
			hurdle->GetScriptComponent<Hurdle>()->SetIsBossScene(true);
			hurdle->GetScriptComponent<Hurdle>()->SetMoveDir(Vector2(1, 0));
			hurdle->GetScriptComponent<Hurdle>()->Destroy(hurdle, 7.0f);
		}

		ref->_isHorizontalAtk = false;
	}


	return Boss::HORIZONTAL_ATTACK;
}

void BOSS_HORIZONTAL_ATTACK::Update()
{
	ref->_animator->Play(animClip);
}

void BOSS_HORIZONTAL_ATTACK::End()
{
}
