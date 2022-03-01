#include "pch.h"
#include "JW2DEngine.h"
#include "GameObject.h"
#include "AngryAnimation.h"
#include "Animator.h"
#include "State.h"
#include "Angry.h"
#include "Shark.h"

AngryAnimation::AngryAnimation(GameObject* gameObject)
	:MonoBehaviour(gameObject),
	_enemyObj(gameObject),
	_animator(gameObject->GetComponent<Animator>())

{
}

AngryAnimation::~AngryAnimation()
{
}

void AngryAnimation::FixedUpdate()
{
}

void AngryAnimation::Update()
{
}

void AngryAnimation::AnimationPlay()
{
	if (_enemyObj->GetScriptComponent<Shark>()->GetState())
	{
		
	}
}
