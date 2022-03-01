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

// ĳ���� �Ӹ��� �ִ� Ʈ���Ű� ���� ĳ������ Ʈ���Ÿ� true�� �ٲ���
void PlayerHeadTrigger::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::GetThroughGround) || collider->CompareTag(TAG::MovableGround))
	{ 
		_playerObj->GetComponent<BoxCollider>()->SetTrigger(true);
	}
}

// ĳ���� �Ӹ��� �ִ� Ʈ���Ű� ������ ĳ������ Ʈ���Ÿ� false�� �ٲ���
void PlayerHeadTrigger::OnTriggerExit(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::GetThroughGround) || collider->CompareTag(TAG::MovableGround))
	{
		_playerObj->GetComponent<BoxCollider>()->SetTrigger(false);
	}
}
