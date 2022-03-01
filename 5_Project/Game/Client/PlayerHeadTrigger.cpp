#include "pch.h"
#include "PlayerHeadTrigger.h"
#include "GameObject.h"
#include "ColliderBase.h"
#include "BoxCollider.h"

PlayerHeadTrigger::PlayerHeadTrigger(GameObject* gameObject)
	:MonoBehaviour(gameObject)
{

}

PlayerHeadTrigger::~PlayerHeadTrigger()
{
}

// 캐릭터 머리에 있는 트리거가 들어가면 캐릭터의 트리거를 true로 바꿔줌
void PlayerHeadTrigger::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::GetThroughGround) || collider->CompareTag(TAG::MovableGround))
	{ 
		_playerObj->GetComponent<BoxCollider>()->SetTrigger(true);
	}
}

// 캐릭터 머리에 있는 트리거가 끝나면 캐릭터의 트리거를 false로 바꿔줌
void PlayerHeadTrigger::OnTriggerExit(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::GetThroughGround) || collider->CompareTag(TAG::MovableGround))
	{
		_playerObj->GetComponent<BoxCollider>()->SetTrigger(false);
	}
}
