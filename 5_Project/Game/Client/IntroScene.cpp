#include "pch.h"
#include "IntroScene.h"
#include "JW2DEngine.h"
#include "TutorialScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "CircleRenderer.h"
#include "BoxRenderer.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "CameraController.h"
#include "Canvas.h"
#include "Button.h"
#include "Panel.h"
#include "UIManager.h"
#include "Sprite.h"
#include "FadeIn.h"
#include "Animator.h"
#include "SpriteRenderer.h"

void IntroScene::Init()
{
	// SOUND_MANAGER->Bgm();

	GEngine->SetMainCamera(nullptr);
	            
	GameObject* background = new GameObject(TAG::UI);
	background->SetName("Background");
	background->AddComponent<Transform>();
	background->GetComponent<Transform>()->SetLocalPosition(Vector2(960.f, 540.f));
	background->AddComponent<SpriteRenderer>();
	background->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TItle_BG.png", Vector2(0, 0), 1920.f, 1080.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	background->GetComponent<SpriteRenderer>()->SetWH(1980.f, 1080.f);
	background->SetCameraView(true);

	GameObject* IntroPanel = new GameObject(TAG::UI);
	IntroPanel->SetName("IntroPanel");
	IntroPanel->AddComponent<Transform>();
	IntroPanel->GetComponent<Transform>()->SetLocalPosition(Vector2(960.f, 540.f));
	IntroPanel->AddComponent<Panel>();
	//IntroPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	IntroPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
	IntroPanel->SetCameraView(true);
	GET_SINGLE(UIManager)->SetIntroPanel(IntroPanel);

	GameObject* titleText = new GameObject(TAG::UI);
	titleText->SetName("TitleText");
	titleText->AddComponent<Transform>();
	titleText->GetComponent<Transform>()->SetParent(IntroPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
	titleText->GetComponent<Transform>()->SetLocalPosition(Vector2(-500.f, -350.f));
	titleText->AddComponent<SpriteRenderer>();
	titleText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\Title_Logo.png", Vector2(0, 0), 906, 266, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	titleText->GetComponent<SpriteRenderer>()->SetWH(906.f, 266.f);
	titleText->SetCameraView(true);

	GameObject* newGameButton = new GameObject(TAG::UI);
	newGameButton->SetName("NewGameButton");
	newGameButton->AddComponent<Transform>();
	newGameButton->GetComponent<Transform>()->SetParent(IntroPanel->GetComponent<Transform>());	
	newGameButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-500.f, -150.f));
	newGameButton->AddComponent<Button>();
	newGameButton->GetComponent<Button>()->SetCanvas(IntroPanel->GetComponent<Transform>());				// 패널을 캔버스삼는당..
	newGameButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_StartNewGame_Text.png", Vector2(0, 0), 936, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	newGameButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_StartNewGame_OnMouse.png", Vector2(0, 0), 936, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	newGameButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_StartNewGame_Click.png", Vector2(0, 0), 936, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	newGameButton->GetComponent<Button>()->SetWH(936.f, 180.f);
	newGameButton->SetCameraView(true);
	GET_SINGLE(UIManager)->SetIntroButtons(newGameButton);

	GameObject* loadGameButton = new GameObject(TAG::UI);
	loadGameButton->SetName("LoadGameButton");
	loadGameButton->AddComponent<Transform>();
	loadGameButton->GetComponent<Transform>()->SetParent(IntroPanel->GetComponent<Transform>());	
	loadGameButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-640.f, 40.f));
	loadGameButton->AddComponent<Button>();
	loadGameButton->GetComponent<Button>()->SetCanvas(IntroPanel->GetComponent<Transform>());				/// 패널을 캔버스삼는당..
	loadGameButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TItleUI_LoadGame_Text.png", Vector2(0, 0), 659, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	loadGameButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TItleUI_LoadGame_OnMouse.png", Vector2(0, 0), 659, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	loadGameButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TItleUI_LoadGame_Click.png", Vector2(0, 0), 659, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	loadGameButton->GetComponent<Button>()->SetWH(659.f, 180.f);
	loadGameButton->SetCameraView(true);
	GET_SINGLE(UIManager)->SetIntroButtons(loadGameButton);

	GameObject* settingButton = new GameObject(TAG::UI);
	settingButton->SetName("SettingButton");
	settingButton->AddComponent<Transform>();
	settingButton->GetComponent<Transform>()->SetParent(IntroPanel->GetComponent<Transform>());
	settingButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-675.f, 230.f));
	settingButton->AddComponent<Button>();
	settingButton->GetComponent<Button>()->SetCanvas(IntroPanel->GetComponent<Transform>());				/// 패널을 캔버스삼는당..
	settingButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Settings_Text.png", Vector2(0, 0), 583, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Settings_OnMouse.png", Vector2(0, 0), 583, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Settings_Click.png", Vector2(0, 0), 583, 180, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingButton->GetComponent<Button>()->SetWH(583.f, 180.f);
	settingButton->SetCameraView(true);
	GET_SINGLE(UIManager)->SetIntroButtons(settingButton);

	GameObject* quitButton = new GameObject(TAG::UI);
	quitButton->SetName("QuitButton");
	quitButton->AddComponent<Transform>();
	quitButton->GetComponent<Transform>()->SetParent(IntroPanel->GetComponent<Transform>());
	quitButton->GetComponent<Transform>()->SetLocalPosition(Vector2(-800.f, 420.f));
	quitButton->AddComponent<Button>();
	quitButton->GetComponent<Button>()->SetCanvas(IntroPanel->GetComponent<Transform>());				/// 패널을 캔버스삼는당..
	quitButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Quit_Text.png", Vector2(0, 0), 333, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	quitButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Quit_OnMouse.png", Vector2(0, 0), 333, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	quitButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Title UI\\TitleUI_Quit_Click.png", Vector2(0, 0), 333, 179, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	quitButton->GetComponent<Button>()->SetWH(333.f, 179.f);
	quitButton->SetCameraView(true);
	GET_SINGLE(UIManager)->SetIntroButtons(quitButton);

	// 세팅 패널
	GameObject* introSettingPanel = new GameObject(TAG::UI);
	introSettingPanel->SetName("IntroSettingPanel");
	introSettingPanel->AddComponent<Transform>();
	introSettingPanel->GetComponent<Transform>()->SetLocalPosition(Vector2(960.f, 540.f));
	introSettingPanel->AddComponent<Panel>();
	introSettingPanel->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	introSettingPanel->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
	introSettingPanel->SetActive(false);
	introSettingPanel->SetCameraView(true);
	GET_SINGLE(UIManager)->SetInGameSettingPanel(introSettingPanel); // 걍 똑같이 넣어주장

	GameObject* masterVolumeText = new GameObject(TAG::UI);
	masterVolumeText->SetName("MasterVolumeText");
	masterVolumeText->AddComponent<Transform>();
	masterVolumeText->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());
	masterVolumeText->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, -400.f));
	masterVolumeText->AddComponent<SpriteRenderer>();
	masterVolumeText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_MasterVolume_Text.png", Vector2(0, 0), 562, 275, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	masterVolumeText->GetComponent<SpriteRenderer>()->SetWH(562.f, 275.f);
	masterVolumeText->SetActive(false);
	masterVolumeText->SetCameraView(true);

	GameObject* sfxVolumeText = new GameObject(TAG::UI);
	sfxVolumeText->SetName("SfxVolumeText");
	sfxVolumeText->AddComponent<Transform>();
	sfxVolumeText->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());
	sfxVolumeText->GetComponent<Transform>()->SetLocalPosition(Vector2(-700.f, -100.f));
	sfxVolumeText->AddComponent<SpriteRenderer>();
	sfxVolumeText->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_SFXVolume_Text.png", Vector2(0, 0), 562, 275, Vector2(0.5f, 0.5f), 0.f, 1.0f));
	sfxVolumeText->GetComponent<SpriteRenderer>()->SetWH(562.f, 275.f);
	sfxVolumeText->SetActive(false);
	sfxVolumeText->SetCameraView(true);

	GameObject* musicVolumeText = new GameObject(TAG::UI);
	musicVolumeText->SetName("MusicVolumeText");
	musicVolumeText->AddComponent<Transform>();
	musicVolumeText->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());
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
		settingVolumeBarBg->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());
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
		settingBall->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());
		settingBall->GetComponent<Transform>()->SetLocalPosition(Vector2(100.f, 300.f * i - 400.f));
		settingBall->AddComponent<Button>();
		settingBall->GetComponent<Button>()->SetCanvas(introSettingPanel->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
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
	settingQuitButton->GetComponent<Transform>()->SetParent(introSettingPanel->GetComponent<Transform>());	// 버튼은 메뉴패널을 부모로 삼는다.
	settingQuitButton->GetComponent<Transform>()->SetLocalPosition(Vector2(700.f, 400.f));
	settingQuitButton->AddComponent<Button>();
	settingQuitButton->GetComponent<Button>()->SetCanvas(introSettingPanel->GetComponent<Transform>());				// 캔버스의 위치값을 가져와서 계산해서 버튼의 위치를 알아내야한다.
	settingQuitButton->GetComponent<Button>()->SetNormalSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_Text.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingQuitButton->GetComponent<Button>()->SetHighlightSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_OnMouse.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingQuitButton->GetComponent<Button>()->SetPressedSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Settings UI\\SettingsUI_Quit_Click.png", Vector2(0, 0), 350, 161, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	settingQuitButton->GetComponent<Button>()->SetWH(350.f, 161.f);
	settingQuitButton->SetActive(false);
	settingQuitButton->SetCameraView(true);
	GET_SINGLE(UIManager)->SetInGameSettingQuitButton(settingQuitButton);

	// Fade In
	GameObject* fadeInObj = new GameObject(TAG::NONE);
	fadeInObj->SetName("FadeIn");
	fadeInObj->AddComponent<Transform>();
	fadeInObj->GetComponent<Transform>()->SetLocalPosition(Vector2(960.f, 540.f));
	fadeInObj->AddComponent<Panel>();
	fadeInObj->AddComponent<FadeIn>();
	fadeInObj->GetComponent<Panel>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\UI\\Pause UI\\Black_FadeIn.png", Vector2(0, 0), 1280, 749, Vector2(0.5f, 0.5f), 1.0f, 1.0f));
	fadeInObj->GetComponent<Panel>()->GetSprite()->opacity = 0.f;		// 저 시트는 아마 이미 엔진내부에 있어서 opacity 조정해두면 그대로 바뀌어서 다시 0.f로 바꿔주었다..
	fadeInObj->GetComponent<Panel>()->SetWH(1920.f, 1080.f);
	fadeInObj->SetActive(false);
	fadeInObj->SetCameraView(true);
	GET_SINGLE(UIManager)->SetFadeInObj(fadeInObj);
}
