#include "pch.h"
#include "State.h"
#include "JellyFish.h"
#include "JELLYFISH_GAME_OVER.h"

JELLYFISH_GAME_OVER::JELLYFISH_GAME_OVER(JellyFish* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("JellyfishDead")))
{
}

void JELLYFISH_GAME_OVER::Start()
{
	ref->GetGameObject()->GetComponent<Rigidbody>()->OnGravity(false);
	ref->GetGameObject()->GetComponent<BoxCollider>()->SetTrigger(true);
}

int JELLYFISH_GAME_OVER::FixedUpdate()
{
	if (ref->_deadDelay >= 0.5f)
	{
		ref->Destroy(ref->GetGameObject());
	}

	ref->_deadDelay += DELTA_TIME;

	return JellyFish::GAME_OVER;
}

void JELLYFISH_GAME_OVER::Update()
{
	ref->_animator->Play(animClip);
}

void JELLYFISH_GAME_OVER::End()
{
}
