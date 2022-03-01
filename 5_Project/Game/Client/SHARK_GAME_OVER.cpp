#include "pch.h"
#include "State.h"
#include "Shark.h"
#include "SHARK_GAME_OVER.h"

SHARK_GAME_OVER::SHARK_GAME_OVER(Shark* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("SharkDead")))
{
}

void SHARK_GAME_OVER::Start()
{
	ref->GetGameObject()->GetComponent<Rigidbody>()->OnGravity(false);
	ref->GetGameObject()->GetComponent<BoxCollider>()->SetTrigger(true);
}

int SHARK_GAME_OVER::FixedUpdate()
{
	if (ref->_deadDelay >= 0.5f)
	{
		ref->Destroy(ref->GetGameObject());
	}

	ref->_deadDelay += DELTA_TIME;

	return Shark::GAME_OVER;
}

void SHARK_GAME_OVER::Update()
{
	ref->_animator->Play(animClip);
}

void SHARK_GAME_OVER::End()
{
}
