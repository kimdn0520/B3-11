#include "pch.h"
#include "State.h"
#include "Prefab.h"
#include "AngryMotion.h"
#include "GameObject.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "Shark.h"
#include "Penguin.h"
#include "AnimationClip.h"


AngryMotion::AngryMotion(GameObject* gameObject)
	:MonoBehaviour(gameObject), _animClip(AnimClipLoader::LoadClip(AnimClipPath("MonsterAngry")))
{
}

AngryMotion::~AngryMotion()
{
}


void AngryMotion::Update()
{

	if (_enemyObj->GetName() == "Penguin")
	{
		if (_enemyObj->GetScriptComponent<Penguin>()->GetState() == 1)
		{
			_animationObj->GetComponent<Animator>()->Play(_animClip);
		}
		else
		{
			_animationObj->GetComponent<Animator>()->StopPlay();
		}
	}
	else if (_enemyObj->GetName() == "Shark")
	{
		if (_enemyObj->GetScriptComponent<Shark>()->GetState() == 1)
		{
			_animationObj->GetComponent<Animator>()->Play(_animClip);
		}
		else
		{
			_animationObj->GetComponent<Animator>()->StopPlay();
		}
	}
	


}
