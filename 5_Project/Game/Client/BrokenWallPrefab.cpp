#include "pch.h"
#include "prefab.h"
#include "BrokenWallPrefab.h"

BrokenWallPrefab::BrokenWallPrefab(string name, wstring filePath, float posX, float posY, float width, float height)
	:GameObject(TAG::BrokenWall)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	GetComponent<Animator>();
	AddComponent<Animator>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	AddComponent<SpriteRenderer>();
	GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(filePath, Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	GetComponent<SpriteRenderer>()->SetWH(width, height);
	AddComponent<BrokenWall>();
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

BrokenWallPrefab::~BrokenWallPrefab()
{
}
