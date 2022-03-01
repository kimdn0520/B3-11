#include "pch.h"
#include "UIManager.h"
#include "Input.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Transform.h"
#include "TutorialScene.h"
#include "Panel.h"
#include "Transform.h"
#include "FadeIn.h"
#include "SoundManager.h"
#include "MainStage1.h"
#include "B3_11Prefab.h"
#include "B3_11.h"
#include "JW2DEngine.h"

Transform* UIManager::GetPlayerTransform()
{
	return _player->GetComponent<Transform>();
}

/// <summary>
/// 인게임 내의 esc 누르면 나오는 메뉴 컨트롤이다.
/// ※ 치명적인 버그(esc랑 스페이스 둘다 겁나 눌러대면 로직이 꼬여버린다 ㅋㅋ....)
/// 일단 ESC로 메뉴는 키는데 끄는거는 Space버튼이나 마우스 클릭으로 하자
/// </summary>
void UIManager::InGameMenuControl()
{
	if(_menuButtons.size() == 0)
		return;
		
	if (INPUT->GetButtonDown(KEY_TYPE::ESC) && !_isInGameMenuPanel)
	{
		_isInGameMenuPanel = true;
		
		_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL);	// 이전 키보드스테이터스 노말로
		_menuInfo = 0;
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);
		SCENE_MANAGER->SetIsReservedTimeControl(true);					
	}

	// 인게임 메뉴패널이 켜져있다면 키보드로 이동하는 경우.. 매우 헷갈려..
	if (_inGameMenuPanel->GetEnable())
	{
		if (INPUT->GetButtonDown(KEY_TYPE::UP))
		{
			if(_menuInfo != 0)
				SOUND_MANAGER->MenuMove();
			
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			(_menuInfo == 0) ? 0 : (_menuInfo -= 1);
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::DOWN))
		{
			if (_menuInfo != 2)
				SOUND_MANAGER->MenuMove();

			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			(_menuInfo == 2) ? 2 : (_menuInfo += 1);
		}

		// 키보드로 선택된 버튼은 하이라이트
		_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetSelected(true);
		}
	}

	// Quit 패널에서의 동작들
	if (_inGameQuitPanel->GetEnable())
	{
		if (INPUT->GetButtonDown(KEY_TYPE::LEFT))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			if(_quitInfo != 0)
				SOUND_MANAGER->MenuMove();

			_quitInfo = 0;
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			if(_quitInfo != 1)
				SOUND_MANAGER->MenuMove();

			_quitInfo = 1;
		}
		
		// 키보드로 선택된 버튼은 하이라이트
		_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetSelected(true);
		}

		// Quit에서 yes 버튼이 True가 되면
		if (_quitPanelButtons[(int)InGameQuitButton::YES]->GetComponent<Button>()->GetSelected())
		{
			SOUND_MANAGER->BgmPause("MainBGM");
			SOUND_MANAGER->BgmPlay("TitleBGM");
			_quitPanelButtons[(int)InGameQuitButton::YES]->GetComponent<Button>()->SetSelected(false);

			_quitInfo = 1;
			ResetUIVector();
			_isInGameMenuPanel = false;
			_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName("IntroScene");
			_fadeInObj->SetActive(true);
			_playerHp = 3;
			return;
		}

		// Quit에서 No 버튼이 True가 되면
		if (_quitPanelButtons[(int)InGameQuitButton::NO]->GetComponent<Button>()->GetSelected())
		{
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameQuitPanel);									// QuitPanel 꺼주고 
			_quitPanelButtons[(int)InGameQuitButton::NO]->GetComponent<Button>()->SetSelected(false);	// true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);									// MenuPanel 켜주고
		}
	}

	// Setting 패널에서의 동작들
	if (_inGameSettingPanel->GetEnable())
	{
		// 키보드로 선택된 버튼은 하이라이트
		_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(true);
		}

		if (_inGameSettingVolumeBalls[(int)InGameSettingBall::MASTER]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{
			_masterSetX = INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if(_masterSetX <= -250.f)
				_masterSetX = -250.f;
			else if(_masterSetX >= 450.f)
				_masterSetX = 450.f;
			
			_masterVol = (_masterSetX + 250.f) / 600.f;
		}
		else if (_inGameSettingVolumeBalls[(int)InGameSettingBall::SFX]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{	
			_sfxSetX = INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if (_sfxSetX <= -250.f)
				_sfxSetX = -250.f;
			else if (_sfxSetX >= 450.f)
				_sfxSetX = 450.f;
			
			_sfxVol = (_sfxSetX + 250.f) / 600.f;
		}
		else if (_inGameSettingVolumeBalls[(int)InGameSettingBall::MUSIC]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{
			_musicSetX = INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if (_musicSetX <= -250.f)
				_musicSetX = -250.f;
			else if (_musicSetX >= 450.f)
				_musicSetX = 450.f;

			_musicVol = (_musicSetX + 250.f) / 600.f;
		}

		// SettingQuit 버튼이 True가 되면
		if (_inGameSettingQuitButton->GetComponent<Button>()->GetSelected())
		{
			SOUND_MANAGER->MenuYesButton();
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameSettingPanel);								// SettingPanel 꺼주고 
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(false);	                    // true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);									// MenuPanel 켜주고
		}
	}

	// 다시 게임으로 돌아가는 버튼이 True가 되면
	if (_menuButtons[(int)InGameMenu::RETURN_GAME_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuNoButton();
		_isInGameMenuPanel = false;
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
		SCENE_MANAGER->SetIsReservedTimeControl(false);
		_menuButtons[(int)InGameMenu::RETURN_GAME_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}
	
	// 옵션 패널을 키는 버튼이 True가 되면
	if (_menuButtons[(int)InGameMenu::OPTION_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameSettingPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
		_menuButtons[(int)InGameMenu::OPTION_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}
	
	// QuitPanel을 켜주는 버튼이 True가 되면
	if (_menuButtons[(int)InGameMenu::GO_TITLE_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		_menuButtons[(int)InGameMenu::GO_TITLE_BUTTON]->GetComponent<Button>()->SetSelected(false);
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameQuitPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
	}
}

/// <summary>
/// 체력, 캐릭터이미지 등의 컨트롤이다.
/// </summary>
void UIManager::InGameImageUIControl()
{
	if (_player != nullptr && _menuButtons.size() != 0)
	{
		if (_player->GetScriptComponent<B3_11>()->GetIsDashSkill())
		{
			_dashImageSpriteRenderer->SetSprite(_dashImages[(int)DashImage::DASH_ON]);
			_isDash = true;
		}
		else
		{
			_dashImageSpriteRenderer->SetSprite(_dashImages[(int)DashImage::DASH_OFF]);
			_isDash = false;
		}

		if (_player->GetScriptComponent<B3_11>()->GetIsChargeSkill())
		{
			_chargeImageSpriteRenderer->SetSprite(_chargeImages[(int)ChargeImage::CHARGE_ON]);
			_isCharge = true;
		}
		else
		{
			_chargeImageSpriteRenderer->SetSprite(_chargeImages[(int)ChargeImage::CHARGE_OFF]);
			_isCharge = false;
		}

		if (_player->GetScriptComponent<B3_11>()->GetHp() == 3)
		{
			_chracterImageSpriteRenderer->SetSprite(_chracterImages[(int)ChracterImage::HP_3]);
			_heartImagesSpriteRenderer[0]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_heartImagesSpriteRenderer[1]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_heartImagesSpriteRenderer[2]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_playerHp = 3;
		}	
		else if (_player->GetScriptComponent<B3_11>()->GetHp() == 2)
		{
			_chracterImageSpriteRenderer->SetSprite(_chracterImages[(int)ChracterImage::HP_3]);
			_heartImagesSpriteRenderer[0]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_heartImagesSpriteRenderer[1]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_playerHp = 2;
			_heartImagesSpriteRenderer[2]->SetSprite(_heartImages[(int)HeartImage::OFF]);
		}
		else if(_player->GetScriptComponent<B3_11>()->GetHp() == 1)
		{
			_chracterImageSpriteRenderer->SetSprite(_chracterImages[(int)ChracterImage::HP_2]);
			_heartImagesSpriteRenderer[0]->SetSprite(_heartImages[(int)HeartImage::ON]);
			_heartImagesSpriteRenderer[1]->SetSprite(_heartImages[(int)HeartImage::OFF]);
			_playerHp = 1;
			_heartImagesSpriteRenderer[2]->SetSprite(_heartImages[(int)HeartImage::OFF]);
		}
		else
		{
			_chracterImageSpriteRenderer->SetSprite(_chracterImages[(int)ChracterImage::HP_1_0]);
			_heartImagesSpriteRenderer[0]->SetSprite(_heartImages[(int)HeartImage::OFF]);
			_heartImagesSpriteRenderer[1]->SetSprite(_heartImages[(int)HeartImage::OFF]);
			_playerHp = 0;
			_heartImagesSpriteRenderer[2]->SetSprite(_heartImages[(int)HeartImage::OFF]);
		}
	}
}

void UIManager::InGameOverControl()
{
	if (_player != nullptr)
	{
		if (_isGameOver)
		{
			if (INPUT->GetButtonDown(KEY_TYPE::LEFT))
			{
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

				if(_gameOverInfo != 0)
					SOUND_MANAGER->MenuMove();

				_gameOverInfo = 0;
			}
			else if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
			{
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

				if(_gameOverInfo != 1)
					SOUND_MANAGER->MenuMove();

				_gameOverInfo = 1;
			}

			// 키보드로 선택된 버튼은 하이라이트
			_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

			// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
			if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
			{
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetSelected(true);
			}

			// continue 버튼이 True가 되면
			if (_gameOverButtons[(int)InGameOverButton::CONTINUE]->GetComponent<Button>()->GetSelected())
			{
				SOUND_MANAGER->MenuYesButton();
				_gameOverButtons[(int)InGameOverButton::CONTINUE]->GetComponent<Button>()->SetSelected(false);
				
				ResetUIVector();

				SCENE_MANAGER->SetIsReservedTimeControl(false);
				_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName(SCENE_MANAGER->GetSavePoint());   // 세이브 포인트로..

				_fadeInObj->SetActive(true);
				_gameOverInfo = 0;
				_playerHp = 3;
				_isGameOver = false;
				return;
			}

			// Quit 버튼이 True가 되면
			if (_gameOverButtons[(int)InGameOverButton::QUIT]->GetComponent<Button>()->GetSelected())
			{
				SOUND_MANAGER->MenuNoButton();
				SOUND_MANAGER->BgmPause("MainBGM");
				SOUND_MANAGER->BgmPlay("TitleBGM");
				_gameOverButtons[(int)InGameOverButton::QUIT]->GetComponent<Button>()->SetSelected(false);

				_gameOverInfo = 0;
				ResetUIVector();			// 초기화..!!
				_isInGameMenuPanel = false;
				_isGameOver = false;
				_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName("IntroScene");
				_fadeInObj->SetActive(true);
				_playerHp = 3;
				return;
			}
		}
	}
}

void UIManager::InGameClearControl()
{
	if(_isGameClear)
	{
		SOUND_MANAGER->BgmPause("BossBGM");
		SOUND_MANAGER->BgmPlay("CreditsBGM");
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			SCENE_MANAGER->SetSavePoint("TutorialScene");
			SCENE_MANAGER->SetPlayerPos( { 2 * 128.f, 5 * 128.f } );
			SOUND_MANAGER->BgmPause("CreditsBGM");
			// 대충 시작화면으로..
			SOUND_MANAGER->MenuYesButton();
			SOUND_MANAGER->BgmPlay("TitleBGM");
			ResetUIVector();
			_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName("IntroScene");
			_fadeInObj->SetActive(true);
			_isGameClear = false;
		}
	}
}

void UIManager::SetIsTrueInGameOverPanel()
{
	SCENE_MANAGER->SetActiveTrueGameObject(_inGameOverPanel);
}

void UIManager::IntroMenuControl()
{
	if(_introButtons.size() == 0)
		return;
	
	if (_introPanel->GetEnable())
	{
		if (INPUT->GetButtonDown(KEY_TYPE::UP))
		{
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			if(_introInfo != 0)
				SOUND_MANAGER->MenuMove();

			(_introInfo == 0) ? 0 : (_introInfo -= 1);
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::DOWN))
		{
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // 이전 값 노말로 바꿈

			if (_introInfo != 3)
				SOUND_MANAGER->MenuMove();

			(_introInfo == 3) ? 3 : (_introInfo += 1);
		}

		// 키보드로 선택된 버튼은 하이라이트
		_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_introButtons[_introInfo]->GetComponent<Button>()->SetSelected(true);
		}

		// New Game Start Button 이 True가 되면..
		if (_introButtons[(int)IntroMenu::NEW_GAME_START_BUTTON]->GetComponent<Button>()->GetSelected())
		{
			_introButtons[(int)IntroMenu::NEW_GAME_START_BUTTON]->GetComponent<Button>()->SetSelected(false);
			SOUND_MANAGER->BgmPause("TitleBGM");
			SOUND_MANAGER->BgmPlay("MainBGM");
			/*_introButtons.clear();
			_inGameSettingVolumeBalls.clear();*/
			ResetUIVector();
			_isDash = false;
			_isCharge = false;
			_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName("TutorialScene");
			_fadeInObj->SetActive(true);
			return;
		}
	}

	// Load Game을 키는 버튼이 True가 되면..
	if (_introButtons[(int)IntroMenu::LOAD_GAME_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SOUND_MANAGER->BgmPause("TitleBGM");
		SOUND_MANAGER->BgmPlay("MainBGM");
		_introButtons[(int)IntroMenu::LOAD_GAME_BUTTON]->GetComponent<Button>()->SetSelected(false);
		ResetUIVector();
		_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName(SCENE_MANAGER->GetSavePoint());   // 세이브 포인트로..
		_fadeInObj->SetActive(true);
		_gameOverInfo = 0;
		_playerHp = 3;
		return;
	}

	// Setting을 버튼이 True가 되면..
	if (_introButtons[(int)IntroMenu::SETTING_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameSettingPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_introPanel);
		_introButtons[(int)IntroMenu::SETTING_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}

	// Quit 버튼이 True가 되면..
	if (_introButtons[(int)IntroMenu::QUIT_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuNoButton();
		_introButtons[(int)IntroMenu::QUIT_BUTTON]->GetComponent<Button>()->SetSelected(false);
		PostQuitMessage(0);		// 이게 맞나???
	}

	// Setting 패널에서의 동작들
	if (_inGameSettingPanel->GetEnable())
	{
		// 키보드로 선택된 버튼은 하이라이트
		_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// 하이라이트된 메뉴 스페이스바 누르면 키보드스테이터스 셀렉
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(true);
		}

		if (_inGameSettingVolumeBalls[(int)InGameSettingBall::MASTER]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{
			_masterSetX= INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if (_masterSetX <= -250.f)
				_masterSetX = -250.f;
			else if (_masterSetX >= 450.f)
				_masterSetX = 450.f;

			_masterVol = (_masterSetX + 250.f) / 600.f;
		}
		else if (_inGameSettingVolumeBalls[(int)InGameSettingBall::SFX]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{
			_sfxSetX = INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if (_sfxSetX <= -250.f)
				_sfxSetX = -250.f;
			else if (_sfxSetX >= 450.f)
				_sfxSetX = 450.f;

			_sfxVol = (_sfxSetX + 250.f) / 600.f;
		}
		else if (_inGameSettingVolumeBalls[(int)InGameSettingBall::MUSIC]->GetComponent<Button>()->GetButtonStatus() == ButtonStatus::PRESSED)
		{
			_musicSetX = INPUT->GetMousePos().x - (SCREEN_WIDTH / 2);

			if (_musicSetX <= -250.f)
				_musicSetX = -250.f;
			else if (_musicSetX >= 450.f)
				_musicSetX = 450.f;

			_musicVol = (_musicSetX + 250.f) / 600.f;
		}

		// SettingQuit 버튼이 True가 되면
		if (_inGameSettingQuitButton->GetComponent<Button>()->GetSelected())
		{
			SOUND_MANAGER->MenuNoButton();
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameSettingPanel);								// SettingPanel 꺼주고 
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(false);	                    // true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_introPanel);									// MenuPanel 켜주고
		}
	}
}

void UIManager::Update()
{
	SOUND_MANAGER->BgmSoundControl(_musicVol * _masterVol);
	SOUND_MANAGER->SFXSoundControl(_sfxVol * _masterVol);

	if (_inGameSettingVolumeBalls.size() != 0) 
	{
		_inGameSettingVolumeBalls[(int)InGameSettingBall::MASTER]->GetComponent<Transform>()->SetLocalPosition(Vector2(_masterSetX, -400.f));
		_inGameSettingVolumeBalls[(int)InGameSettingBall::SFX]->GetComponent<Transform>()->SetLocalPosition(Vector2(_sfxSetX, -100.f));
		_inGameSettingVolumeBalls[(int)InGameSettingBall::MUSIC]->GetComponent<Transform>()->SetLocalPosition(Vector2(_musicSetX, 200.f));
	}

	// if(대충 현재씬이 인게임 씬이라면) InGameMenuControl() 이 가능하게
	if (SCENE_MANAGER->GetActiveScene() == SCENE_MANAGER->GetSceneList()["IntroScene"])
	{
		IntroMenuControl();
	}
	else if (SCENE_MANAGER->GetActiveScene() != SCENE_MANAGER->GetSceneList()["IntroScene"] && _menuButtons.size() != 0)
	{
		if (!_isGameOver)
		{
			InGameMenuControl();
			InGameImageUIControl();
			InGameClearControl();
		}
		else if (_isGameOver)
		{
			InGameOverControl();
		}
	}
}
