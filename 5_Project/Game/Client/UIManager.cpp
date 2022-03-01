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
/// �ΰ��� ���� esc ������ ������ �޴� ��Ʈ���̴�.
/// �� ġ������ ����(esc�� �����̽� �Ѵ� �̳� ������� ������ ���������� ����....)
/// �ϴ� ESC�� �޴��� Ű�µ� ���°Ŵ� Space��ư�̳� ���콺 Ŭ������ ����
/// </summary>
void UIManager::InGameMenuControl()
{
	if(_menuButtons.size() == 0)
		return;
		
	if (INPUT->GetButtonDown(KEY_TYPE::ESC) && !_isInGameMenuPanel)
	{
		_isInGameMenuPanel = true;
		
		_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL);	// ���� Ű���彺�����ͽ� �븻��
		_menuInfo = 0;
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);
		SCENE_MANAGER->SetIsReservedTimeControl(true);					
	}

	// �ΰ��� �޴��г��� �����ִٸ� Ű����� �̵��ϴ� ���.. �ſ� �򰥷�..
	if (_inGameMenuPanel->GetEnable())
	{
		if (INPUT->GetButtonDown(KEY_TYPE::UP))
		{
			if(_menuInfo != 0)
				SOUND_MANAGER->MenuMove();
			
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			(_menuInfo == 0) ? 0 : (_menuInfo -= 1);
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::DOWN))
		{
			if (_menuInfo != 2)
				SOUND_MANAGER->MenuMove();

			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			(_menuInfo == 2) ? 2 : (_menuInfo += 1);
		}

		// Ű����� ���õ� ��ư�� ���̶���Ʈ
		_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_menuButtons[_menuInfo]->GetComponent<Button>()->SetSelected(true);
		}
	}

	// Quit �гο����� ���۵�
	if (_inGameQuitPanel->GetEnable())
	{
		if (INPUT->GetButtonDown(KEY_TYPE::LEFT))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			if(_quitInfo != 0)
				SOUND_MANAGER->MenuMove();

			_quitInfo = 0;
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			if(_quitInfo != 1)
				SOUND_MANAGER->MenuMove();

			_quitInfo = 1;
		}
		
		// Ű����� ���õ� ��ư�� ���̶���Ʈ
		_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_quitPanelButtons[_quitInfo]->GetComponent<Button>()->SetSelected(true);
		}

		// Quit���� yes ��ư�� True�� �Ǹ�
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

		// Quit���� No ��ư�� True�� �Ǹ�
		if (_quitPanelButtons[(int)InGameQuitButton::NO]->GetComponent<Button>()->GetSelected())
		{
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameQuitPanel);									// QuitPanel ���ְ� 
			_quitPanelButtons[(int)InGameQuitButton::NO]->GetComponent<Button>()->SetSelected(false);	// true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);									// MenuPanel ���ְ�
		}
	}

	// Setting �гο����� ���۵�
	if (_inGameSettingPanel->GetEnable())
	{
		// Ű����� ���õ� ��ư�� ���̶���Ʈ
		_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
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

		// SettingQuit ��ư�� True�� �Ǹ�
		if (_inGameSettingQuitButton->GetComponent<Button>()->GetSelected())
		{
			SOUND_MANAGER->MenuYesButton();
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameSettingPanel);								// SettingPanel ���ְ� 
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(false);	                    // true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_inGameMenuPanel);									// MenuPanel ���ְ�
		}
	}

	// �ٽ� �������� ���ư��� ��ư�� True�� �Ǹ�
	if (_menuButtons[(int)InGameMenu::RETURN_GAME_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuNoButton();
		_isInGameMenuPanel = false;
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
		SCENE_MANAGER->SetIsReservedTimeControl(false);
		_menuButtons[(int)InGameMenu::RETURN_GAME_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}
	
	// �ɼ� �г��� Ű�� ��ư�� True�� �Ǹ�
	if (_menuButtons[(int)InGameMenu::OPTION_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameSettingPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
		_menuButtons[(int)InGameMenu::OPTION_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}
	
	// QuitPanel�� ���ִ� ��ư�� True�� �Ǹ�
	if (_menuButtons[(int)InGameMenu::GO_TITLE_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		_menuButtons[(int)InGameMenu::GO_TITLE_BUTTON]->GetComponent<Button>()->SetSelected(false);
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameQuitPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_inGameMenuPanel);
	}
}

/// <summary>
/// ü��, ĳ�����̹��� ���� ��Ʈ���̴�.
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
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

				if(_gameOverInfo != 0)
					SOUND_MANAGER->MenuMove();

				_gameOverInfo = 0;
			}
			else if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
			{
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

				if(_gameOverInfo != 1)
					SOUND_MANAGER->MenuMove();

				_gameOverInfo = 1;
			}

			// Ű����� ���õ� ��ư�� ���̶���Ʈ
			_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

			// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
			if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
			{
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
				_gameOverButtons[_gameOverInfo]->GetComponent<Button>()->SetSelected(true);
			}

			// continue ��ư�� True�� �Ǹ�
			if (_gameOverButtons[(int)InGameOverButton::CONTINUE]->GetComponent<Button>()->GetSelected())
			{
				SOUND_MANAGER->MenuYesButton();
				_gameOverButtons[(int)InGameOverButton::CONTINUE]->GetComponent<Button>()->SetSelected(false);
				
				ResetUIVector();

				SCENE_MANAGER->SetIsReservedTimeControl(false);
				_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName(SCENE_MANAGER->GetSavePoint());   // ���̺� ����Ʈ��..

				_fadeInObj->SetActive(true);
				_gameOverInfo = 0;
				_playerHp = 3;
				_isGameOver = false;
				return;
			}

			// Quit ��ư�� True�� �Ǹ�
			if (_gameOverButtons[(int)InGameOverButton::QUIT]->GetComponent<Button>()->GetSelected())
			{
				SOUND_MANAGER->MenuNoButton();
				SOUND_MANAGER->BgmPause("MainBGM");
				SOUND_MANAGER->BgmPlay("TitleBGM");
				_gameOverButtons[(int)InGameOverButton::QUIT]->GetComponent<Button>()->SetSelected(false);

				_gameOverInfo = 0;
				ResetUIVector();			// �ʱ�ȭ..!!
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
			// ���� ����ȭ������..
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
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			if(_introInfo != 0)
				SOUND_MANAGER->MenuMove();

			(_introInfo == 0) ? 0 : (_introInfo -= 1);
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::DOWN))
		{
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::NORMAL); // ���� �� �븻�� �ٲ�

			if (_introInfo != 3)
				SOUND_MANAGER->MenuMove();

			(_introInfo == 3) ? 3 : (_introInfo += 1);
		}

		// Ű����� ���õ� ��ư�� ���̶���Ʈ
		_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
		if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		{
			_introButtons[_introInfo]->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::PRESSED);
			_introButtons[_introInfo]->GetComponent<Button>()->SetSelected(true);
		}

		// New Game Start Button �� True�� �Ǹ�..
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

	// Load Game�� Ű�� ��ư�� True�� �Ǹ�..
	if (_introButtons[(int)IntroMenu::LOAD_GAME_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SOUND_MANAGER->BgmPause("TitleBGM");
		SOUND_MANAGER->BgmPlay("MainBGM");
		_introButtons[(int)IntroMenu::LOAD_GAME_BUTTON]->GetComponent<Button>()->SetSelected(false);
		ResetUIVector();
		_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName(SCENE_MANAGER->GetSavePoint());   // ���̺� ����Ʈ��..
		_fadeInObj->SetActive(true);
		_gameOverInfo = 0;
		_playerHp = 3;
		return;
	}

	// Setting�� ��ư�� True�� �Ǹ�..
	if (_introButtons[(int)IntroMenu::SETTING_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuYesButton();
		SCENE_MANAGER->SetActiveTrueGameObject(_inGameSettingPanel);
		SCENE_MANAGER->SetActiveFalseGameObject(_introPanel);
		_introButtons[(int)IntroMenu::SETTING_BUTTON]->GetComponent<Button>()->SetSelected(false);
	}

	// Quit ��ư�� True�� �Ǹ�..
	if (_introButtons[(int)IntroMenu::QUIT_BUTTON]->GetComponent<Button>()->GetSelected())
	{
		SOUND_MANAGER->MenuNoButton();
		_introButtons[(int)IntroMenu::QUIT_BUTTON]->GetComponent<Button>()->SetSelected(false);
		PostQuitMessage(0);		// �̰� �³�???
	}

	// Setting �гο����� ���۵�
	if (_inGameSettingPanel->GetEnable())
	{
		// Ű����� ���õ� ��ư�� ���̶���Ʈ
		_inGameSettingQuitButton->GetComponent<Button>()->SetKeyBoardStatus(ButtonStatus::HIGHLIGHT);

		// ���̶���Ʈ�� �޴� �����̽��� ������ Ű���彺�����ͽ� ����
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

		// SettingQuit ��ư�� True�� �Ǹ�
		if (_inGameSettingQuitButton->GetComponent<Button>()->GetSelected())
		{
			SOUND_MANAGER->MenuNoButton();
			SCENE_MANAGER->SetActiveFalseGameObject(_inGameSettingPanel);								// SettingPanel ���ְ� 
			_inGameSettingQuitButton->GetComponent<Button>()->SetSelected(false);	                    // true -> false
			SCENE_MANAGER->SetActiveTrueGameObject(_introPanel);									// MenuPanel ���ְ�
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

	// if(���� ������� �ΰ��� ���̶��) InGameMenuControl() �� �����ϰ�
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
