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

// ĳ���Ͱ� Ʈ���ſ� ������ �������� �̸��� �����ͼ� ĳ���Ϳ��� �Ѱ��ش�
// �׷��� �������� ������Ų��.
void Item::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Player))
	{
		Destroy(GetGameObject());
	}
}
