#include "pch.h"
#include "State.h"
#include "Penguin.h"
#include "PENGUIN_GAME_OVER.h"

PENGUIN_GAME_OVER::PENGUIN_GAME_OVER(Penguin* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("PenguinDead")))
{
}

void PENGUIN_GAME_OVER::Start()
{
	ref->GetGameObject()->GetComponent<BoxCollider>()->SetTrigger(true);
	ref->GetGameObject()->GetComponent<Rigidbody>()->OnGravity(false);
}

int PENGUIN_GAME_OVER::FixedUpdate()
{
	if (ref->_deadDelay >= 1.0f)
	{
		ref->Destroy(ref->GetGameObject());
	}

	ref->_deadDelay += DELTA_TIME;

	return Penguin::GAME_OVER;
}

void PENGUIN_GAME_OVER::Update()
{
	ref->_animator->Play(animClip);
}

void PENGUIN_GAME_OVER::End()
{
}
