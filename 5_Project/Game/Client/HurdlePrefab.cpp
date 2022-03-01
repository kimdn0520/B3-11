#include "pch.h"
#include "prefab.h"
#include "HurdlePrefab.h"

HurdlePrefab::HurdlePrefab(string name, string type, float posX, float posY, float width, float height, bool trigger)
:GameObject(TAG::Hurdle)
{
	SetName(name);
	AddComponent<Transform>();
	AddComponent<Animator>();
	if (type == "Saw")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<CircleCollider>();
		GetComponent<CircleCollider>()->SetRadius(64.f);
		GetComponent<CircleCollider>()->SetTrigger(true);
		AddComponent<Hurdle>();
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Circular_Saw (128_128).png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
	}
	else if (type == "Laser_H_L")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX + 20.f, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width - 40.f, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_L (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	else if (type == "Laser_H_M")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		AddComponent<Lazer>();
	}
	else if (type == "Laser_H_R")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX - 20.f, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width - 40.f, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_R (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	else if (type == "Laser_HR_L")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX + 20.f, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width - 40.f, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_L (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	else if (type == "Laser_HR_M")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		AddComponent<Lazer>();
	}
	else if (type == "Laser_HR_R")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX - 20.f, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width - 40.f, height / 2);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_R (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	else if (type == "Laser_V_B")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width / 2, height);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type V_Off_B (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	else if (type == "Laser_V_M")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width / 2, height);
		GetComponent<BoxCollider>()->SetTrigger(true);
		AddComponent<Lazer>();
	}
	else if (type == "Laser_V_T")
	{
		GetComponent<Transform>()->SetLocalPosition(Vector2(posX, posY));
		AddComponent<BoxCollider>();
		GetComponent<BoxCollider>()->SetWH(width / 2, height);
		GetComponent<BoxCollider>()->SetTrigger(true);
		/*AddComponent<SpriteRenderer>();
		GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type V_Off_T (128_128) 12fps.png", Vector2(0, 0), width, height, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		GetComponent<SpriteRenderer>()->SetWH(width, height);*/
		AddComponent<Lazer>();
	}
	SetCameraView(true);
	Update();
	SetCameraView(false);
}

HurdlePrefab::~HurdlePrefab()
{
}
