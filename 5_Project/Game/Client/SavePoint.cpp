#include "pch.h"
#include "JW2DEngine.h"
#include "SavePoint.h"
#include "Animator.h"
#include "GameObject.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "B3_11Prefab.h"
#include "Input.h"

SavePoint::SavePoint(GameObject* gameObject)
	:MonoBehaviour(gameObject)
{
}

SavePoint::~SavePoint()
{
}

void SavePoint::OnTriggerStay(ColliderBase* collider)
{
	//if (collider->CompareTag(TAG::Player) && INPUT->GetButtonUp(KEY_TYPE::UP))
	//{
	//	_sprite->GetComponent<SpriteRenderer>()->SetRenderInactive();

	//	_sprite->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Save_Point_Saved (256_256).png", Vector2(0, 0), 2560.f, 2560.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	//
	//	_playerObj->GetComponent<Animator>()->StopPlay();
	//}
	//
}
