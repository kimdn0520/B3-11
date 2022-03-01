#include "pch.h"
#include "prefab.h"
#include "TilePrefab.h"

TilePrefab::TilePrefab(string name, float posX, float posY, float width, float height)
	:GameObject(TAG::Ground)
{
	SetName("groundCollider");
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

TilePrefab::~TilePrefab()
{}
