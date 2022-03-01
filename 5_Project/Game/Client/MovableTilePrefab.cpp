#include "pch.h"
#include "prefab.h"
#include "MovableTilePrefab.h"
#include "SpritePrefab.h"

MovableTilePrefab::MovableTilePrefab(string name, float posX, float posY, float width, float height)
	:GameObject(TAG::MovableGround)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	AddComponent<SpriteRenderer>();
	GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Floating_Type A (128_128).png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	GetComponent<SpriteRenderer>()->SetWH(width, height);
	AddComponent<MovableTile>();
	//AddComponent<GetThroughTile>();
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

MovableTilePrefab::~MovableTilePrefab()
{
}
