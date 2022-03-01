#include "pch.h"
#include "Item.h"
#include "Player.h"
#include "GameObject.h"
#include "Transform.h"
#include "ColliderBase.h"

Item::Item(GameObject* gameObject)
	:MonoBehaviour(gameObject)
{
}

Item::~Item()
{
}

// 캐릭터가 트리거에 들어오면 아이템의 이름을 가져와서 캐릭터에게 넘겨준다
// 그러고 아이템은 삭제시킨다.
void Item::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Player))
	{
		Destroy(GetGameObject());
	}
}
