#include "pch.h"
#include "GameProcess.h"
#include "JW2DEngine.h"
#include "GameObject.h"
//#include "TestScene.h"
//#include "TestScene2.h"
#include "TutorialScene.h"
#include "IntroScene.h"
#include "BulletPrefab.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "EnemyController.h"
#include "TestEnemyPrefab.h"
#include "UIManager.h"
#include "MainStage1.h"
#include "DashMap.h"
#include "TransitionDash.h"
#include "TransitionVerti.h"
#include "MiddleSave.h"
#include "AcquireCharge.h"
#include "SavePoint1.h"
#include "SavePoint2.h"
#include "SavePoint3.h"
#include "ChallengeStage.h"
#include "BossMap.h"


GameProcess::GameProcess()
{}

GameProcess::~GameProcess()
{

}

void GameProcess::Init(const WindowInfo& info)
{	
	// ���� �ʱ�ȭ
	GEngine->Init(info);

	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_preTime);

#pragma region Singleton
	{
		GET_SINGLE(Input)->Init(info.hWnd);
		GET_SINGLE(Timer)->Init();
		GET_SINGLE(SoundManager)->Init();
	}
#pragma endregion

#pragma region SheetLoad
	{
		GEngine->LoadSpriteSheet(L"..\\4_Resources\\TestSheet\\Skul.png");
	}
#pragma endregion

#pragma region SceneSave&Load
	{
		SCENE_MANAGER->InputScene<IntroScene>("IntroScene");
		SCENE_MANAGER->InputScene<TutorialScene>("TutorialScene");
		SCENE_MANAGER->InputScene<MainStage1>("MainStage1");
		SCENE_MANAGER->InputScene<TransitionDash>("TransitionDash");
		SCENE_MANAGER->InputScene<TransitionVerti>("TransitionVerti");
		SCENE_MANAGER->InputScene<MiddleSave>("MiddleSave");
		SCENE_MANAGER->InputScene<DashMap>("DashMap");
		SCENE_MANAGER->InputScene<AcquireCharge>("AcquireCharge");
		SCENE_MANAGER->InputScene<SavePoint1>("SavePoint1");
		SCENE_MANAGER->InputScene<SavePoint2>("SavePoint2");
		SCENE_MANAGER->InputScene<ChallengeStage>("ChallengeStage");
		SCENE_MANAGER->InputScene<SavePoint3>("SavePoint3");
		SCENE_MANAGER->InputScene<BossMap>("BossMap");
		SCENE_MANAGER->LoadScene("IntroScene"); 
		//SCENE_MANAGER->LoadScene("ChallengeStage");
		//SCENE_MANAGER->LoadScene("BossMap");
		SCENE_MANAGER->ReservedScene();
		GET_SINGLE(SoundManager)->BgmSoundControl(0.0f);
		GET_SINGLE(SoundManager)->SFXSoundControl(0.0f);
		SOUND_MANAGER->BgmSetting("MainBGM");
		SOUND_MANAGER->BgmSetting("CreditsBGM");
		SOUND_MANAGER->BgmSetting("BossBGM");
		SOUND_MANAGER->BgmPause("MainBGM");
		SOUND_MANAGER->BgmPause("CreditsBGM");
		SOUND_MANAGER->BgmPause("BossBGM");
		SOUND_MANAGER->BgmSetting("TitleBGM");
	}
#pragma endregion

// �̰� ��������.. �׳� ��ü������ �浹 ������ ���ϴ������� ����..? �̰��ϸ� ���� �ž����� ��Ƹ���. ;-;
#pragma region NotColTagSetting
	{
		/*GameObject::_notAffectTag["Player"].push_back("Enemy");
		GameObject::_notAffectTag["Enemy"].push_back("Player");

		GameObject::_notAffectTag["Enemy"].push_back("Enemy");*/
		
		//GameObject::_notAffectTag[(int)TAG::Ground].push_back((int)TAG::Ground);
		//GameObject::_notAffectTag[(int)TAG::Ground].push_back((int)TAG::MovableGround);
		//GameObject::_notAffectTag[(int)TAG::Ground].push_back((int)TAG::GetThroughGround);

		//GameObject::_notAffectTag[(int)TAG::MovableGround].push_back((int)TAG::Ground);
		/*GameObject::_notAffectTag["MovableGround"].push_back("MovableGround");*/
		/*GameObject::_notAffectTag["MovableGround"].push_back("GetThroughGround");

		GameObject::_notAffectTag["GetThroughGround"].push_back("Ground");
		GameObject::_notAffectTag["GetThroughGround"].push_back("MovableGround");
		GameObject::_notAffectTag["GetThroughGround"].push_back("GetThroughGround");*/
	}
#pragma endregion

#pragma region ObjectPool
	{
		//MakePool();
	}
#pragma endregion
}

void GameProcess::Update()
{
	{
		QueryPerformanceCounter(&_curTime);
		_checkTime = (_curTime.QuadPart - _preTime.QuadPart) / (float)_frequency.QuadPart;
	}

	if (_checkTime > _frame)
	{
 		INPUT->Update();
		TIMER->Update();
		
		// ����� ������Ʈ�� �ִٸ� �ҷ��´�.
		SCENE_MANAGER->ReservedInstantiateGameObject();
		
		// ����� ������ ������Ʈ�� �ִٸ� �����Ѵ�.
		SCENE_MANAGER->ReservedRemoveGameObject();

		// ����� True�� ������Ʈ�� �ִٸ� �ҷ��´�.
		SCENE_MANAGER->ReservedActiveTrueGameObject();

		// ����� False�� ������Ʈ�� �ִٸ� �ҷ��´�.
		SCENE_MANAGER->ReservedActiveFalseGameObject();

		// ���� �ð��� ���߰� �����ϴ� ��Ʈ��
		if (SCENE_MANAGER->GetIsReservedTimeControl())
		{
			SCENE_MANAGER->ReservedTimeControl();
		}
		
		// ����� ���� �ִٸ� �ҷ��´�.
		if (SCENE_MANAGER->GetIsReservedLoadScene() &&
			SCENE_MANAGER->GetInstantiateGameObjectQueue().size() == 0 &&
			SCENE_MANAGER->GetDestroyList().size() == 0)
		{
			GET_SINGLE(ObjectPool)->ResetObjectMapList();
			SCENE_MANAGER->ReservedScene();
		}
		else
		{
			GET_SINGLE(UIManager)->Update();
		}

		//�ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�
		GEngine->BeginRender();

		// �ӽ�
		GEngine->DrawBackGroundScreen();

		SCENE_MANAGER->Update();

		GEngine->EndRender();
		//�ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�


		_preTime = _curTime;
	}


	/*string str = "check : " + to_string(check);

	const char* text = str.c_str();

	SetWindowText(GEngine->GetWindow().hWnd, text);*/
}
