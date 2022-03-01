#include "pch.h"
#include "FallGround.h"
#include "prefab.h"

FallGround::FallGround(string name, float posX, float posY, float width, float height)
	:GameObject(TAG::FallGround)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	GetComponent<BoxCollider>()->SetTrigger(true);
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

FallGround::~FallGround()
{

}
