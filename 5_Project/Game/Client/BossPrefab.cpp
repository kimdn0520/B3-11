#include "pch.h"
#include "prefab.h"
#include "BossPrefab.h"
#include "Boss.h"

BossPrefab::BossPrefab(Vector2 pos, float radius)
	:GameObject(TAG::Enemy)
{
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(pos);
	GetComponent<Transform>()->SetLocalScale(Vector2(1.f, 1.f));
	AddComponent<CircleCollider>();
	GetComponent<CircleCollider>()->SetRadius(radius);
	GetComponent<CircleCollider>()->SetTrigger(true);
	AddComponent<Animator>();
	AddComponent<Boss>();
	SetCameraView(true);
	SetActive(true);
}

BossPrefab::~BossPrefab()
{
}
