#include "pch.h"
#include "prefab.h"
#include "SavePoint.h"
#include "SavePointPrefab.h"

SavePointPrefab::SavePointPrefab(string Name, float posX, float posY, float width, float height, string savePointName)
	:GameObject(TAG::SavePoint)
{
	SetName(Name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	GetComponent<BoxCollider>()->SetTrigger(true);
	AddComponent<SpriteRenderer>();
	GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Save_Point_Open (256_256).png", Vector2(0, 0), posX, posY, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	GetComponent<SpriteRenderer>()->SetWH(width, height);
	AddComponent<SavePoint>();
	GetScriptComponent<SavePoint>()->savePoint = savePointName;
	GetScriptComponent<SavePoint>()->SetSprite(this);
	SetCameraView(true);

}

SavePointPrefab::~SavePointPrefab()
{
}
