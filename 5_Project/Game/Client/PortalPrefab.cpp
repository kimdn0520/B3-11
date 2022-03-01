#include "pch.h"
#include "prefab.h"
#include "Portal.h"
#include "PortalPrefab.h"

PortalPrefab::PortalPrefab(string connectMapName, Vector2 pos, float width, float height, Vector2 playerPos)
:GameObject(TAG::Portal)

{
	SetName(connectMapName);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(pos);
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	GetComponent<BoxCollider>()->SetTrigger(true);
	AddComponent<Portal>();
	GetScriptComponent<Portal>()->nextPlayerPos = playerPos;
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

PortalPrefab::~PortalPrefab()
{

}
