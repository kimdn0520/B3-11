#include "pch.h"
#include "prefab.h"
#include "ItemPrefab.h"

ItemPrefab::ItemPrefab(string name, Vector2 pos, float radius, bool trigger)
	:GameObject(TAG::Item)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(pos);
	AddComponent<CircleCollider>();
	GetComponent<CircleCollider>()->SetRadius(radius);
	GetComponent<CircleCollider>()->SetTrigger(trigger);
	AddComponent<Animator>();
	GetComponent<Animator>()->AddAnimClip(name + "Item", AnimClipLoader::LoadClip(AnimClipPath(name + "Item")));
	GetComponent<Animator>()->Play(AnimClipLoader::LoadClip(AnimClipPath(name + "Item")));
	AddComponent<Item>();
	SetCameraView(true);
}

ItemPrefab::~ItemPrefab()
{
}
