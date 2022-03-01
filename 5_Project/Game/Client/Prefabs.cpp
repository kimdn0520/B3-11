#include "pch.h"
#include "Prefabs.h"
#include "GameObject.h"
#include "Transform.h"
#include "Bullet.h"
#include "BoxRenderer.h"
#include "BoxCollider.h"

void Prefabs::Init()
{
	_prefabsMap.insert({ 1, BulletPrefab() });

}

/// <summary>
/// Bullet Prefab을 리턴해주는 함수입니다.
/// </summary>
GameObject* Prefabs::BulletPrefab()
{
	GameObject* bulletObj = new GameObject;
	bulletObj->SetName("bulletPrefab");
	bulletObj->SetTag("Bullet");
	bulletObj->AddComponent<Transform>();
	bulletObj->AddComponent<BoxRenderer>();
	bulletObj->GetComponent<BoxRenderer>()->SetWH(50, 50);
	bulletObj->AddComponent<BoxCollider>();
	bulletObj->GetComponent<BoxCollider>()->SetWH(50, 50);
	bulletObj->GetComponent<BoxCollider>()->SetTrigger(true);
	bulletObj->AddComponent<Bullet>();

	return bulletObj;
}

GameObject* Prefabs::GroundSpritePrefab_1()
{
	return nullptr;
}
