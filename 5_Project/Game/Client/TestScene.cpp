#include "pch.h"
#include "JW2DEngine.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "CircleRenderer.h"
#include "BoxRenderer.h"
#include "SpriteRenderer.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Text.h"
#include "TestTxt.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "Camera.h"
#include "CameraController.h"
#include "EnemyController.h"

/// <summary>
/// ※ 주의 사항 ※
/// 1. Trnasform 먼저 addcomponent 할 것
/// 2. Rigidbody는 Collider 보다 먼저 addcomponent 할것 (초기화 할때 값을 못받는 경우 때문에..)
/// 3. 스크립트는 애니메이터 다음에 addcomponent 할것..
/// 4. 처음에 적은 오브제트가 제일 뒤에 있다. 뭐부터 보여야 할 지 잘 할 것..
/// 5. #pragma region 으로 알기쉽게 해준다. 하지말까?
/// 6. 어떤 상호작용을 해야하는 오브젝트의 경우 tag를 적어줄 것(tmpObj->SetTag("Ground");) name 겹쳐두되염
/// </summary>
void TestScene::Init()
{
	//SOUND_MANAGER->Bgm();

#pragma region Ground
	{
		GameObject* tmpObj = new GameObject();
		tmpObj->SetName("ground1");
		tmpObj->SetTag("Ground");
		tmpObj->AddComponent<Transform>();
		tmpObj->GetComponent<Transform>()->SetLocalPosition(Vector2(500.f, 500.f));
		tmpObj->AddComponent<BoxRenderer>();
		tmpObj->GetComponent<BoxRenderer>()->SetWH(500, 50);
		tmpObj->AddComponent<BoxCollider>();
		tmpObj->GetComponent<BoxCollider>()->SetWH(500, 50);
		AddGameObject(tmpObj);

		GameObject* tmpObj2 = new GameObject();
		tmpObj2->SetName("ground2");
		tmpObj2->SetTag("Ground");
		tmpObj2->AddComponent<Transform>();
		tmpObj2->GetComponent<Transform>()->SetLocalPosition(Vector2(600.f, 300.f));
		tmpObj2->AddComponent<BoxRenderer>();
		tmpObj2->GetComponent<BoxRenderer>()->SetWH(300, 50);
		tmpObj2->AddComponent<BoxCollider>();
		tmpObj2->GetComponent<BoxCollider>()->SetWH(300, 50);
		AddGameObject(tmpObj2);
	}
#pragma endregion

#pragma region Portal
	{
		GameObject* tmpObj3 = new GameObject();
		tmpObj3->SetName("Portal1");
		tmpObj3->SetTag("Portal");
		tmpObj3->AddComponent<Transform>();
		tmpObj3->GetComponent<Transform>()->SetLocalPosition(Vector2(700.f, 250.f));
		tmpObj3->AddComponent<BoxCollider>();
		tmpObj3->GetComponent<BoxCollider>()->SetWH(50, 50);
		tmpObj3->GetComponent<BoxCollider>()->SetTrigger(true);
		AddGameObject(tmpObj3);
	}
#pragma endregion

#pragma region Text
	/*{
		GameObject* testTxtObj = new GameObject();
		testTxtObj->SetName("Text");
		testTxtObj->AddComponent<Transform>();
		testTxtObj->GetComponent<Transform>()->SetLocalPosition(Vector2(500.f, 50.f));
		testTxtObj->AddComponent<Text>();
		testTxtObj->AddComponent<TestTxt>();
		AddGameObject(testTxtObj);
	}*/
#pragma endregion

#pragma region Player
	{
		GameObject* gameObject = new GameObject();
		gameObject->SetName("Player");
		gameObject->SetTag("Player");
		gameObject->AddComponent<Transform>();
		gameObject->GetComponent<Transform>()->SetLocalPosition(Vector2(500.f, 200.f));
		// gameObject->GetComponent<Transform>()->SetLocalScale(Vector2(1, 1));
		gameObject->AddComponent<Rigidbody>();
		gameObject->GetComponent<Rigidbody>()->SetLinearDrag(0.05f);
		gameObject->GetComponent<Rigidbody>()->OnGravity(true);
		gameObject->AddComponent<BoxCollider>();
		gameObject->GetComponent<BoxCollider>()->SetWH(50, 50);
		gameObject->AddComponent<Animator>();
		gameObject->GetComponent<Animator>()->CreateAnimClip("Idle");
		gameObject->GetComponent<Animator>()->InputClipData("Idle", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(6, 14), 38, 34, Vector2(0.5f, 0.5f), 0.5f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Idle", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(51, 14), 40, 35, Vector2(0.5f, 0.5f), 0.5f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Idle", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(98, 14), 42, 34, Vector2(0.5f, 0.5f), 0.5f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Idle", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(147, 14), 40, 32, Vector2(0.5f, 0.5f), 0.5f, 1.0f));
		gameObject->GetComponent<Animator>()->CreateAnimClip("Walk");
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(6, 64), 40, 28, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(53, 64), 42, 31, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(102, 64), 40, 32, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(149, 64), 34, 32, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(191, 64), 35, 31, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(233, 64), 41, 34, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(281, 64), 40, 32, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(328, 64), 40, 32, Vector2(0.5f, 0.5f), 0.3f, 1.0f));
		gameObject->GetComponent<Animator>()->CreateAnimClip("Attack");
		gameObject->GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(6, 305), 33, 45, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(45, 305), 33, 44, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(85, 305), 62, 55, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(153, 305), 60, 39, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
		gameObject->GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(219, 305), 40, 34, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
		gameObject->GetComponent<Animator>()->CreateAnimClip("Dash");
		gameObject->GetComponent<Animator>()->InputClipData("Dash", GEngine->LoadSpriteFromSheet(L"..\\4_Resources\\TestSheet\\Skul.png", Vector2(5, 112), 41, 27, Vector2(0.5f, 0.5f), 0.5f, 1.0f));
		gameObject->AddComponent<Text>();
		gameObject->AddComponent<Player>();

		GameObject* childObject = new GameObject();
		childObject->SetName("PlayerAttackPos");
		childObject->SetTag("PlayerAtk");
		childObject->AddComponent<Transform>();
		childObject->GetComponent<Transform>()->SetParent(gameObject->GetComponent<Transform>());
		childObject->AddComponent<BoxCollider>();
		childObject->GetComponent<BoxCollider>()->SetWH(30, 30);
		childObject->GetComponent<BoxCollider>()->SetColliderLocation(Vector2(50, 0));
		childObject->GetComponent<BoxCollider>()->SetTrigger(true);
		childObject->SetActive(false);

		//gameObject->GetScriptComponent<Player>()->SetAttackRange(childObject);
		
		AddGameObject(gameObject);
		AddGameObject(childObject);

		// 카메라
		GameObject* cameraObj = new GameObject();
		cameraObj->AddComponent<Transform>();
		cameraObj->AddComponent<Camera>();
		cameraObj->AddComponent<CameraController>();
		cameraObj->GetScriptComponent<CameraController>()->SetCamera(cameraObj);
		cameraObj->GetScriptComponent<CameraController>()->SetPlayer(gameObject);
		GEngine->SetMainCamera(cameraObj);			// SetMainCamera로 카메라오브젝트 등록해줘야함!!
		AddGameObject(cameraObj);

		// UI 테스트중 카메라의 자식으로 넣어보았다.
		GameObject* testTxtObj = new GameObject();
		testTxtObj->SetName("Text");
		testTxtObj->AddComponent<Transform>();
		testTxtObj->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, -500.f));
		testTxtObj->GetComponent<Transform>()->SetParent(cameraObj->GetComponent<Transform>());
		testTxtObj->AddComponent<Text>();
		testTxtObj->AddComponent<TestTxt>();
		AddGameObject(testTxtObj);
	}
#pragma endregion

#pragma region Enemy
	{
		GameObject* enemy = new GameObject();
		enemy->SetName("enemy");
		enemy->SetTag("Enemy");
		enemy->AddComponent<Transform>();
		enemy->GetComponent<Transform>()->SetLocalPosition(Vector2(600.f, 450.f));
		enemy->AddComponent<BoxCollider>();
		enemy->GetComponent<BoxCollider>()->SetWH(50, 50);
		enemy->AddComponent<Text>();
		enemy->AddComponent<EnemyController>();
		AddGameObject(enemy);
	}
#pragma endregion

}
