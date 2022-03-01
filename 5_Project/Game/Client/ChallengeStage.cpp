#include "pch.h"
#include "JW2DEngine.h"
#include "ChallengeStage.h"
#include "GameObject.h"
#include "Transform.h"
#include "CircleRenderer.h"
#include "BoxRenderer.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "OBBCollider.h"
#include "Rigidbody.h"
#include "Text.h"
#include "TestTxt.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "CameraController.h"
#include "EnemyController.h"
#include "BulletPrefab.h"
#include "ObjectPool.h"
#include "MapDataTable.h"
#include "Canvas.h"
#include "Button.h"
#include "Panel.h"
#include "UIManager.h"
#include "B3_11Prefab.h"
#include "ItemPrefab.h"
#include "HurdlePrefab.h"
#include "SpritePrefab.h"
#include "MovableTilePrefab.h"
#include "GetThroughTilePrefab.h"
#include "BrokenWallPrefab.h"
#include "TilePrefab.h"
#include "CameraPrefab.h"
#include "FadeOut.h"
#include "EnemyPrefab.h"
#include "Turtle.h"
#include "Penguin.h"
#include "FadeIn.h"
#include "PortalPrefab.h"
#include "B3_11.h"
#include "Shark.h"
#include "MapLoader.h"
#include "GameOverTextPrefab.h"
#include "FallGround.h"

void ChallengeStage::Init()
{
	//SOUND_MANAGER->Bgm();

	GameObject* stageBackground = new GameObject(TAG::UI);
	stageBackground->SetName("StageBackground");
	stageBackground->AddComponent<Transform>();
	stageBackground->GetComponent<Transform>()->SetLocalPosition(Vector2(3200.f, 3200.f));
	stageBackground->AddComponent<SpriteRenderer>();
	stageBackground->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Wall_Tower 50 x 50 (6400_6400).png", Vector2(0, 0), 6400.f, 6400.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	stageBackground->GetComponent<SpriteRenderer>()->SetWH(6400.f, 6400.f);
	stageBackground->SetCameraView(true);

	// Camera
	CameraPrefab* cameraObj = new CameraPrefab(1920.f, 1080.f, true, true);
	cameraObj->GetScriptComponent<CameraController>()->SetCamera(cameraObj);
	GEngine->SetMainCamera(cameraObj);		// SetMainCamera로 카메라오브젝트 등록

	/*GameObject* stageBackground = new GameObject(TAG::UI);
	stageBackground->SetName("StageBackground");
	stageBackground->AddComponent<Transform>();
	stageBackground->GetComponent<Transform>()->SetLocalPosition(Vector2(3520.f, 1280.f));
	stageBackground->AddComponent<SpriteRenderer>();
	stageBackground->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Wall_Tutorial 55 x 20 (7040_2560).png", Vector2(0, 0), 7040.f, 2560.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	stageBackground->GetComponent<SpriteRenderer>()->SetWH(7040.f, 2560.f);
	stageBackground->SetCameraView(true);*/

	MapLoader::LoadMap("MapData\\ChallengeStage.json", cameraObj);

	FallGround* fallObj = new FallGround("fallGround", 25 * 128.f, 49.5 * 128.f, 48 * 128.f, 128.f );

	// Dash Item
	ItemPrefab* itemObj1 = new ItemPrefab("Dash", { 0.f,0.f }, 10, true);

	// Charge Item
	ItemPrefab* itemObj2 = new ItemPrefab("Charge", { 0.f,0.f }, 8, true);

	// Player
	B3_11Prefab* playerObj = new B3_11Prefab(SCENE_MANAGER->GetPlayerPos());
	GET_SINGLE(UIManager)->SetPlayer(playerObj);
	playerObj->GetScriptComponent<B3_11>()->SetDashExist(GET_SINGLE(UIManager)->GetIsDash());
	playerObj->GetScriptComponent<B3_11>()->SetChargeExist(GET_SINGLE(UIManager)->GetIsCharge());

	// 카메라에 플레이어 등록
	cameraObj->GetScriptComponent<CameraController>()->SetPlayer(playerObj);

	// 총알이 닿으면 사라지는 벽
	//BrokenWallPrefab* brokenWallObj = new BrokenWallPrefab("BrokenWall", 300.f, 2000.f, 30, 200);

	// 적
	//EnemyPrefab* enemyObj = new EnemyPrefab("Turtle", { 1000.f,500.f }, 240, 150);
	//enemyObj->AddComponent<Turtle>();


	//EnemyPrefab* enemyObj = new EnemyPrefab("Shark", { 1500.f,800.f }, 240, 150);
	//enemyObj->AddComponent<Shark>();
	//enemyObj->GetScriptComponent<Shark>()->SetPlayerTransform(playerObj->GetComponent<Transform>());

	//EnemyPrefab* enemyObj2 = new EnemyPrefab("Penguin", { 1500.f,600.f }, 240, 150);
	//enemyObj2->AddComponent<Penguin>();
	//enemyObj2->GetScriptComponent<Penguin>()->SetPlayerTransform(playerObj->GetComponent<Transform>());

	// 다음맵 포탈
	PortalPrefab* portalObj1 = new PortalPrefab("SavePoint2", { 0.5 * 128.f, 44.5 * 128.f }, 100.f, 400.f, { 13.5 * 128.f, 5 * 128.f });
	PortalPrefab* portalObj2 = new PortalPrefab("SavePoint3", { 28 * 128.f, 1 * 128.f }, 400.f, 100.f, { 1.5 * 128.f, 5 * 128.f });

#pragma region UI
	{
		GameObject* canvas = new GameObject(TAG::UI);
		canvas->SetName("Canvas");
		canvas->AddComponent<Transform>();
		canvas->AddComponent<Canvas>();
		canvas->GetComponent<Canvas>()->SetRenderCamera(cameraObj);
		canvas->SetCameraView(true);									// 카메라에 보이고 싶으면 생성할때 true하고 들어가야댐(콜라이더가 아니면 충돌처리가 안되기때문에)

		GameObject* chracterImage = new GameObject(TAG::UI);
		chracterImage->SetName("ChracterImage");
		chracterImage->AddComponent<Transform>();
		chracterImage->GetComponent<Transform>()->SetLocalPosition(Vector2(-850.f, -420.f));
		chracterImage->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		chracterImage->AddComponent<SpriteRenderer>();
		chracterImage->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Face1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		chracterImage->GetComponent<SpriteRenderer>()->SetWH(221.f, 221.f);
		chracterImage->SetCameraView(true);
		GET_SINGLE(UIManager)->SetChracterImageObject(chracterImage->GetComponent<SpriteRenderer>());
		GET_SINGLE(UIManager)->SetChracterImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Face1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		GET_SINGLE(UIManager)->SetChracterImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Face2.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		GET_SINGLE(UIManager)->SetChracterImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Face3.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));


		GameObject* dashImage = new GameObject(TAG::UI);
		dashImage->SetName("DashImage");
		dashImage->AddComponent<Transform>();
		dashImage->GetComponent<Transform>()->SetLocalPosition(Vector2(-850.f, -430.f));
		dashImage->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		dashImage->AddComponent<SpriteRenderer>();
		dashImage->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Charge1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		dashImage->GetComponent<SpriteRenderer>()->SetWH(221.f, 221.f);
		dashImage->SetCameraView(true);
		GET_SINGLE(UIManager)->SetDashImageObject(dashImage->GetComponent<SpriteRenderer>());
		GET_SINGLE(UIManager)->SetDashImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Charge1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		GET_SINGLE(UIManager)->SetDashImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Charge0.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));


		GameObject* chargeImage = new GameObject(TAG::UI);
		chargeImage->SetName("ChargeImage");
		chargeImage->AddComponent<Transform>();
		chargeImage->GetComponent<Transform>()->SetLocalPosition(Vector2(-850.f, -430.f));
		chargeImage->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		chargeImage->AddComponent<SpriteRenderer>();
		chargeImage->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Dash1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		chargeImage->GetComponent<SpriteRenderer>()->SetWH(221.f, 221.f);
		chargeImage->SetCameraView(true);
		GET_SINGLE(UIManager)->SetChargeImageObject(chargeImage->GetComponent<SpriteRenderer>());
		GET_SINGLE(UIManager)->SetChargeImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Dash1.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		GET_SINGLE(UIManager)->SetChargeImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_Dash0.png", Vector2(0, 0), 221, 221, Vector2(0.5f, 0.5f), 0.f, 1.0f));


		//GameObject* TextHP = new GameObject();
		//TextHP->SetName("TextPause");
		//TextHP->SetTag("Default");
		//TextHP->AddComponent<Transform>();
		//TextHP->GetComponent<Transform>()->SetLocalPosition(Vector2(0.f, 0.f));
		//TextHP->GetComponent<Transform>()->SetLocalScale(Vector2(5.f, 5.f));				// 텍스트 폰트 크기를 이걸로 바꿔준다.
		//TextHP->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		//TextHP->AddComponent<Text>();
		//TextHP->GetComponent<Text>()->text = "P A U S E";
		//AddGameObject(TextHP);

		for (int i = 0; i < 3; i++)
		{
			GameObject* heartImage = new GameObject(TAG::UI);
			heartImage->SetName("HeartImage");
			heartImage->AddComponent<Transform>();
			heartImage->GetComponent<Transform>()->SetLocalPosition(Vector2(-670.f + i * 100.f, -420.f));
			heartImage->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
			heartImage->AddComponent<SpriteRenderer>();
			heartImage->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_0.png", Vector2(0, 0), 118, 118, Vector2(0.5f, 0.5f), 0.f, 1.0f));
			heartImage->GetComponent<SpriteRenderer>()->SetWH(118.f, 118.f);
			heartImage->SetCameraView(true);
			GET_SINGLE(UIManager)->SetHeartImageObject(heartImage->GetComponent<SpriteRenderer>());
		}
		GET_SINGLE(UIManager)->SetHeartImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_0.png", Vector2(0, 0), 118, 118, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		GET_SINGLE(UIManager)->SetHeartImages(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\HP UI\\HP_UI_1.png", Vector2(0, 0), 118, 118, Vector2(0.5f, 0.5f), 0.f, 1.0f));

		GameObject* inGameMenuPanel = new GameObject(TAG::UI);
		inGameMenuPanel->SetName("InGameMenuPanel");
		inGameMenuPanel->AddComponent<Transform>();
		inGameMenuPanel->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		inGameMenuPanel->AddComponent<Panel>();
		inGameMenuPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 0.5f));
		inGameMenuPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		inGameMenuPanel->SetActive(false);
		inGameMenuPanel->SetCameraView(true);
		GET_SINGLE(UIManager)->SetInGameMenuPanel(inGameMenuPanel);

		GameObject* pauseText = new GameObject(TAG::UI);
		pauseText->SetName("PAUSE_TEXT");
		pauseText->AddComponent<Transform>();
		pauseText->GetComponent<Transform>()->SetParent(inGameMenuPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		pauseText->GetComponent<Transform>()->SetLocalPosition(Vector2(0, -300.f));
		pauseText->AddComponent<SpriteRenderer>();
		pauseText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Text.png", Vector2(0, 0), 529, 135, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		pauseText->GetComponent<SpriteRenderer>()->SetWH(529.f, 135.f);
		pauseText->SetActive(false);
		pauseText->SetCameraView(true);

		GameObject* returnGame = new GameObject(TAG::UI);
		returnGame->SetName("ReturnGameButton");
		returnGame->AddComponent<Transform>();
		returnGame->GetComponent<Transform>()->SetParent(inGameMenuPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		returnGame->GetComponent<Transform>()->SetLocalPosition(Vector2(0, -100.f));
		returnGame->AddComponent<Button>();
		returnGame->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		returnGame->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Resume_Text.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		returnGame->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Resume_OnMouse.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		returnGame->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Resume_Click.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		returnGame->GetComponent<Button>()->SetWH(737.f, 179.f);
		returnGame->SetActive(false);
		returnGame->SetCameraView(true);
		//GET_SINGLE(UIManager)->SetReturnGameButton(returnGame);
		GET_SINGLE(UIManager)->SetMenuButtons(returnGame);

		GameObject* option = new GameObject(TAG::UI);
		option->SetName("OptionButton");
		option->AddComponent<Transform>();
		option->GetComponent<Transform>()->SetParent(inGameMenuPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		option->GetComponent<Transform>()->SetLocalPosition(Vector2(0, 100.f));
		option->AddComponent<Button>();
		option->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		option->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Settings_Text.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		option->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Settings_OnMouse.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		option->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Settings_Click.png", Vector2(0, 0), 737, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		option->GetComponent<Button>()->SetWH(737.f, 179.f);
		option->SetActive(false);
		option->SetCameraView(true);
		//GET_SINGLE(UIManager)->SetOptionButton(option);
		GET_SINGLE(UIManager)->SetMenuButtons(option);

		GameObject* goTitle = new GameObject(TAG::UI);
		goTitle->SetName("GoTitleButton");
		goTitle->AddComponent<Transform>();
		goTitle->GetComponent<Transform>()->SetParent(inGameMenuPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		goTitle->GetComponent<Transform>()->SetLocalPosition(Vector2(0, 300.f));
		goTitle->AddComponent<Button>();
		goTitle->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		goTitle->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Quit_Text.png", Vector2(0, 0), 477, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		goTitle->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Quit_OnMouse.png", Vector2(0, 0), 477, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		goTitle->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Pause_Quit_Click.png", Vector2(0, 0), 477, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		goTitle->GetComponent<Button>()->SetWH(477.f, 179.f);
		goTitle->SetActive(false);
		goTitle->SetCameraView(true);
		//GET_SINGLE(UIManager)->SetGoTitleButton(goTitle);
		GET_SINGLE(UIManager)->SetMenuButtons(goTitle);

		// InGameMenuPanel의 Quit 버튼 눌렀을때 나오는 패널
		GameObject* inGameQuitPanel = new GameObject(TAG::UI);
		inGameQuitPanel->SetName("InGameQuitPanel");
		inGameQuitPanel->AddComponent<Transform>();
		inGameQuitPanel->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		inGameQuitPanel->AddComponent<Panel>();
		inGameQuitPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 0.5f));
		inGameQuitPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		inGameQuitPanel->SetActive(false);
		inGameQuitPanel->SetCameraView(true);
		GET_SINGLE(UIManager)->SetInGameQuitPanel(inGameQuitPanel);

		GameObject* quitText = new GameObject(TAG::UI);
		quitText->SetName("QuitText");
		quitText->AddComponent<Transform>();
		quitText->GetComponent<Transform>()->SetParent(inGameQuitPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		quitText->GetComponent<Transform>()->SetLocalPosition(Vector2(0, -150.f));
		quitText->AddComponent<SpriteRenderer>();
		quitText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_Text.png", Vector2(0, 0), 1399, 258, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		quitText->GetComponent<SpriteRenderer>()->SetWH(1399.f, 258.f);
		quitText->SetActive(false);
		quitText->SetCameraView(true);

		GameObject* quitYesButton = new GameObject(TAG::UI);
		quitYesButton->SetName("QuitYesButton");
		quitYesButton->AddComponent<Transform>();
		quitYesButton->GetComponent<Transform>()->SetParent(inGameQuitPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		quitYesButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-400.f, 250.f));
		quitYesButton->AddComponent<Button>();
		quitYesButton->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		quitYesButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_Yes_Text.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitYesButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_Yes_OnMouse.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitYesButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_Yes_Click.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitYesButton->GetComponent<Button>()->SetWH(736.f, 197.f);
		quitYesButton->SetActive(false);
		quitYesButton->SetCameraView(true);
		GET_SINGLE(UIManager)->SetQuitButtons(quitYesButton);

		GameObject* quitNoButton = new GameObject(TAG::UI);
		quitNoButton->SetName("quitNoButton");
		quitNoButton->AddComponent<Transform>();
		quitNoButton->GetComponent<Transform>()->SetParent(inGameQuitPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		quitNoButton->GetComponent<Transform>()->SetLocalPosition(Vector2(400.f, 250.f));
		quitNoButton->AddComponent<Button>();
		quitNoButton->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		quitNoButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_No_Text.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitNoButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_No_OnMouse.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitNoButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Quit UI\\QuitUI_No_Click.png", Vector2(0, 0), 736, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		quitNoButton->GetComponent<Button>()->SetWH(736.f, 196.f);
		quitNoButton->SetActive(false);
		quitNoButton->SetCameraView(true);
		GET_SINGLE(UIManager)->SetQuitButtons(quitNoButton);

		// InGameMenuPanel의 Setting 버튼 눌렀을때 나오는 패널
		GameObject* inGameSettingPanel = new GameObject(TAG::UI);
		inGameSettingPanel->SetName("InGameSettingPanel");
		inGameSettingPanel->AddComponent<Transform>();
		inGameSettingPanel->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		inGameSettingPanel->AddComponent<Panel>();
		inGameSettingPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 0.5f));
		inGameSettingPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		inGameSettingPanel->SetActive(false);
		inGameSettingPanel->SetCameraView(true);
		GET_SINGLE(UIManager)->SetInGameSettingPanel(inGameSettingPanel);

		GameObject* masterVolumeText = new GameObject(TAG::UI);
		masterVolumeText->SetName("MasterVolumeText");
		masterVolumeText->AddComponent<Transform>();
		masterVolumeText->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());
		masterVolumeText->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, -400.f));
		masterVolumeText->AddComponent<SpriteRenderer>();
		masterVolumeText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_MasterVolume_Text.png", Vector2(0, 0), 562, 275, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		masterVolumeText->GetComponent<SpriteRenderer>()->SetWH(562.f, 275.f);
		masterVolumeText->SetActive(false);
		masterVolumeText->SetCameraView(true);

		GameObject* sfxVolumeText = new GameObject(TAG::UI);
		sfxVolumeText->SetName("SfxVolumeText");
		sfxVolumeText->AddComponent<Transform>();
		sfxVolumeText->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());
		sfxVolumeText->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, -100.f));
		sfxVolumeText->AddComponent<SpriteRenderer>();
		sfxVolumeText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_SFXVolume_Text.png", Vector2(0, 0), 562, 275, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		sfxVolumeText->GetComponent<SpriteRenderer>()->SetWH(562.f, 275.f);
		sfxVolumeText->SetActive(false);
		sfxVolumeText->SetCameraView(true);

		GameObject* musicVolumeText = new GameObject(TAG::UI);
		musicVolumeText->SetName("MusicVolumeText");
		musicVolumeText->AddComponent<Transform>();
		musicVolumeText->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());
		musicVolumeText->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, 200.f));
		musicVolumeText->AddComponent<SpriteRenderer>();
		musicVolumeText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_MusicVolume_Text.png", Vector2(0, 0), 562, 275, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		musicVolumeText->GetComponent<SpriteRenderer>()->SetWH(562.f, 275.f);
		musicVolumeText->SetActive(false);
		musicVolumeText->SetCameraView(true);

		for (int i = 0; i < 3; i++)
		{
			// 볼륨 게이지 백그라운드
			GameObject* settingVolumeBarBg = new GameObject(TAG::UI);
			settingVolumeBarBg->SetName("SettingVolumeBarBg");
			settingVolumeBarBg->AddComponent<Transform>();
			settingVolumeBarBg->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());
			settingVolumeBarBg->GetComponent<Transform>()->SetLocalPosition(Vector2(100.f, 300.f * i - 400.f));
			settingVolumeBarBg->AddComponent<SpriteRenderer>();
			settingVolumeBarBg->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_VolumeBar_BG.png", Vector2(0, 0), 748, 58, Vector2(0.5f, 0.5f), 0.f, 1.0f));
			settingVolumeBarBg->GetComponent<SpriteRenderer>()->SetWH(748.f, 58.f);
			settingVolumeBarBg->SetActive(false);
			settingVolumeBarBg->SetCameraView(true);
		}

		for (int i = 0; i < 3; i++)
		{
			// 볼륨 볼
			GameObject* settingBall = new GameObject(TAG::UI);
			settingBall->SetName("SettingBall");
			settingBall->AddComponent<Transform>();
			settingBall->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());
			settingBall->GetComponent<Transform>()->SetLocalPosition(Vector2(100.f, 300.f * i - 400.f));
			settingBall->AddComponent<Button>();
			settingBall->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
			settingBall->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_VolumeBar_Circle.png", Vector2(0, 0), 95, 96, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
			settingBall->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_VolumeBar_Circle.png", Vector2(0, 0), 95, 96, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
			settingBall->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_VolumeBar_Circle.png", Vector2(0, 0), 95, 96, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
			settingBall->GetComponent<Button>()->SetWH(95.f, 96.f);
			settingBall->SetActive(false);
			settingBall->SetCameraView(true);
			GET_SINGLE(UIManager)->SetInGameSettingVolumeBalls(settingBall);
		}

		GameObject* settingQuitButton = new GameObject(TAG::UI);
		settingQuitButton->SetName("SettingQuitButton");
		settingQuitButton->AddComponent<Transform>();
		settingQuitButton->GetComponent<Transform>()->SetParent(inGameSettingPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		settingQuitButton->GetComponent<Transform>()->SetLocalPosition(Vector2(700.f, 400.f));
		settingQuitButton->AddComponent<Button>();
		settingQuitButton->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		settingQuitButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_Text.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		settingQuitButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_OnMouse.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		settingQuitButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_Click.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		settingQuitButton->GetComponent<Button>()->SetWH(350.f, 161.f);
		settingQuitButton->SetActive(false);
		settingQuitButton->SetCameraView(true);
		GET_SINGLE(UIManager)->SetInGameSettingQuitButton(settingQuitButton);

		// 게임오버 패널(esc가 작동되면 안된다. 주의)
		GameObject* gameOverPanel = new GameObject(TAG::UI);
		gameOverPanel->SetName("GameOverPanel");
		gameOverPanel->AddComponent<Transform>();
		gameOverPanel->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		gameOverPanel->AddComponent<Panel>();
		gameOverPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverPanel.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		gameOverPanel->SetActive(false);
		gameOverPanel->SetCameraView(true);
		GET_SINGLE(UIManager)->SetInGameOverPanel(gameOverPanel);

		GameOverTextPrefab* gameOverTextPrefab = new GameOverTextPrefab(Vector2(0.f, -400.f), gameOverPanel->GetComponent<Transform>());
		gameOverTextPrefab->SetActive(false);

		GameObject* gameOverBellUI = new GameObject(TAG::UI);
		gameOverBellUI->SetName("GameOverBellUI");
		gameOverBellUI->AddComponent<Transform>();
		gameOverBellUI->GetComponent<Transform>()->SetParent(gameOverPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		gameOverBellUI->AddComponent<SpriteRenderer>();
		gameOverBellUI->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Bell.png", Vector2(0, 0), 220, 110, Vector2(0.5f, 0.5f), 0.f, 1.0f));
		gameOverBellUI->GetComponent<SpriteRenderer>()->SetWH(220.f, 110.f);
		gameOverBellUI->SetActive(false);
		gameOverBellUI->SetCameraView(true);

		GameObject* gameOverContinueButton = new GameObject(TAG::UI);
		gameOverContinueButton->SetName("GameOverContinueButton");
		gameOverContinueButton->AddComponent<Transform>();
		gameOverContinueButton->GetComponent<Transform>()->SetParent(gameOverPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		gameOverContinueButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-500.f, 300.f));
		gameOverContinueButton->AddComponent<Button>();
		gameOverContinueButton->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		gameOverContinueButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Continue_Text.png", Vector2(0, 0), 727, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverContinueButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Continue_OnMouse.png", Vector2(0, 0), 727, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverContinueButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Continue_Click.png", Vector2(0, 0), 727, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverContinueButton->GetComponent<Button>()->SetWH(727.f, 196.f);
		gameOverContinueButton->SetActive(false);
		gameOverContinueButton->SetCameraView(true);
		GET_SINGLE(UIManager)->SetGameOverPanelButtons(gameOverContinueButton);

		GameObject* gameOverQuitButton = new GameObject(TAG::UI);
		gameOverQuitButton->SetName("GameOverQuitButton");
		gameOverQuitButton->AddComponent<Transform>();
		gameOverQuitButton->GetComponent<Transform>()->SetParent(gameOverPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
		gameOverQuitButton->GetComponent<Transform>()->SetLocalPosition(Vector2(500.f, 300.f));
		gameOverQuitButton->AddComponent<Button>();
		gameOverQuitButton->GetComponent<Button>()->SetCanvas(canvas->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
		gameOverQuitButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Quit_Text.png", Vector2(0, 0), 467, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverQuitButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Quit_OnMouse.png", Vector2(0, 0), 467, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverQuitButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\GameOver UI\\GameOverUI_Quit_Click.png", Vector2(0, 0), 467, 196, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		gameOverQuitButton->GetComponent<Button>()->SetWH(467.f, 196.f);
		gameOverQuitButton->SetActive(false);
		gameOverQuitButton->SetCameraView(true);
		GET_SINGLE(UIManager)->SetGameOverPanelButtons(gameOverQuitButton);

		// Fade Out
		GameObject* fadeOutObj = new GameObject(TAG::UI);
		fadeOutObj->SetName("FadeOut");
		fadeOutObj->AddComponent<Transform>();
		fadeOutObj->AddComponent<Panel>();
		fadeOutObj->AddComponent<FadeOut>();
		fadeOutObj->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		fadeOutObj->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black_FadeOut.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		//fadeOutObj->GetComponent<FadeOut>()->GetSprite();
		fadeOutObj->GetComponent<Panel>()->GetSprite()->opacity = 1.0f;		// 저 시트는 아마 이미 있어서 opacity 조정해두면 그대로 바뀌어서 다시 1.0f로 바꿔주었다..
		fadeOutObj->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		fadeOutObj->SetCameraView(true);

		// Fade In 씬전환 오브젝트
		GameObject* fadeInObj = new GameObject(TAG::UI);
		fadeInObj->SetName("FadeIn");
		fadeInObj->AddComponent<Transform>();
		fadeInObj->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		fadeInObj->AddComponent<Panel>();
		fadeInObj->AddComponent<FadeIn>();
		fadeInObj->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black_FadeIn.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		fadeInObj->GetComponent<Panel>()->GetSprite()->opacity = 0.f;		// 저 시트는 아마 이미 엔진내부에 있어서 opacity 조정해두면 그대로 바뀌어서 다시 0.f로 바꿔주었다..
		fadeInObj->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		fadeInObj->SetActive(false);
		fadeInObj->SetCameraView(true);
		GET_SINGLE(UIManager)->SetFadeInObj(fadeInObj);
		playerObj->GetScriptComponent<B3_11>()->SetFadeInObj(fadeInObj);

		//// Fade In 씬전환 오브젝트
		//GameObject* fadeInObjMainStage1 = new GameObject(TAG::UI);
		//fadeInObjMainStage1->SetName("FadeIn");
		//fadeInObjMainStage1->AddComponent<Transform>();
		//fadeInObjMainStage1->GetComponent<Transform>()->SetParent(canvas->GetComponent<Transform>());
		//fadeInObjMainStage1->AddComponent<Panel>();
		//fadeInObjMainStage1->AddComponent<FadeIn>();
		//fadeInObjMainStage1->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black_FadeIn.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
		//fadeInObjMainStage1->GetComponent<Panel>()->GetSprite()->opacity = 0.f;		// 저 시트는 아마 이미 엔진내부에 있어서 opacity 조정해두면 그대로 바뀌어서 다시 0.f로 바꿔주었다..
		//fadeInObjMainStage1->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
		//fadeInObjMainStage1->SetActive(false);
		//fadeInObjMainStage1->SetCameraView(true);


	}

	// playerObj->GetScriptComponent<B3_11>()->SetFadeInObj(fadeInObj);//todo : 여기 잠깐 막아둠

#pragma endregion
	//GameObject* obb = new GameObject();
	//obb->SetName("obb"); 
	//obb->SetTag("OBB");
	//obb->AddComponent<Transform>();
	//obb->GetComponent<Transform>()->SetLocalPosition(Vector2(400.f, 700.f));
	//obb->GetComponent<Transform>()->SetLocalRotation(70.f);
	//obb->AddComponent<OBBCollider>();
	//obb->GetComponent<OBBCollider>()->SetRotation(70.f);						// OBB는 예외적으로 로테이션 따로 추가해준당..
	//obb->GetComponent<OBBCollider>()->SetWH(100, 100);
	//obb->GetComponent<OBBCollider>()->SetTrigger(true);
}