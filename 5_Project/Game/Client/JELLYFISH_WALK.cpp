#include "pch.h"
#include "State.h"
#include "JellyFish.h"
#include "JELLYFISH_WALK.h"

JELLYFISH_WALK::JELLYFISH_WALK(JellyFish* ref)
	:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("JellyfishMove")))
{}

void JELLYFISH_WALK::Start()
{
	ref->_speed = 60.f;
}

int JELLYFISH_WALK::FixedUpdate()
{
	if (ref->_isHit)
		return JellyFish::HIT;

	ref->_moveTimer += DELTA_TIME;

	if (ref->_moveTimer >= 2.f)
	{
		ref->_moveTimer = 0;

		ref->_h = -ref->_h;
	}

	ref->_moveDir = Vector2(0, ref->_h);
	//ref->_transform->SetLocalScale({ static_cast<float>(ref->_face), ref->_transform->GetLocalScale().y });
	ref->_transform->Translate(ref->_moveDir * ref->_speed * DELTA_TIME);

	return JellyFish::WALK;
}

void JELLYFISH_WALK::Update()
{
	ref->_animator->Play(animClip);
}

void JELLYFISH_WALK::End()
{}
