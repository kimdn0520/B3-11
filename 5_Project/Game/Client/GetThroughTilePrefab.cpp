#include "pch.h"
#include "prefab.h"
#include "GetThroughTilePrefab.h"

GetThroughTilePrefab::GetThroughTilePrefab(string name, float posX, float posY, float width, float height)
	:GameObject(TAG::GetThroughGround)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	AddComponent<GetThroughTile>();
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

GetThroughTilePrefab::~GetThroughTilePrefab()
{
}
