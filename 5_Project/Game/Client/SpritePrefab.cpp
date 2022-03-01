#include "pch.h"
#include "prefab.h"
#include "SpritePrefab.h"
#include "EnginePch.h"
#include "JW2DEngine.h"

SpritePrefab::SpritePrefab(string spriteName, wstring filePath, float posX, float posY, float width, float height)
:GameObject(TAG::SPRITE)
{
	SetName(spriteName);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<SpriteRenderer>();
	GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(filePath, Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	GetComponent<SpriteRenderer>()->SetWH(width,height);
	//AddComponent<MovableTile>();
	SetCameraView(true);
	Update();
}

SpritePrefab::~SpritePrefab()
{
}
