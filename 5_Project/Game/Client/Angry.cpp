#include "pch.h"
#include "State.h"
#include "AngryAnimation.h"
#include "Angry.h"

Angry::Angry(AngryAnimation* ref)
:ref(ref), animClip(AnimClipLoader::LoadClip(AnimClipPath("Angry")))
{
}

void Angry::Start()
{
}

int Angry::FixedUpdate()
{
	return 0;
}

void Angry::Update()
{
}

void Angry::End()
{
}

