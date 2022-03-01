#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "BOSS_GAME_OVER.h"
#include "UIManager.h"

BOSS_GAME_OVER::BOSS_GAME_OVER(Boss* ref)
    :ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("BossDead")))
{}

void BOSS_GAME_OVER::Start()
{
	ref->GetGameObject()->GetComponent<CircleCollider>()->SetTrigger(true);
}

int BOSS_GAME_OVER::FixedUpdate()
{
	if (ref->_deadDelay >= 1.5f)
	{
		GET_SINGLE(UIManager)->SetIsGameClear(true);
		SCENE_MANAGER->SetActiveTrueGameObject(GET_SINGLE(UIManager)->GetInGameClearPanel());

		ref->Destroy(ref->GetGameObject());
	}

	ref->_deadDelay += DELTA_TIME;

	return Boss::GAME_OVER;
}

void BOSS_GAME_OVER::Update()
{
    ref->_animator->Play(animClip);
}

void BOSS_GAME_OVER::End()
{
}
