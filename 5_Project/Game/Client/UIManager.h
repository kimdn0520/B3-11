#pragma once

class GameObject;
class Button;
class Text;
class SpriteRenderer;
class Sprite;
class Player;
class Transform;
class B3_11Prefab;

enum class InGameMenu
{
	RETURN_GAME_BUTTON,
	OPTION_BUTTON,
	GO_TITLE_BUTTON,
};

enum class InGameQuitButton
{
	YES,
	NO,
};

enum class InGameOverButton
{
	CONTINUE,
	QUIT,
};

enum class InGameSettingBall
{
	MASTER,
	SFX,
	MUSIC,
};

enum class DashImage
{
	DASH_OFF,
	DASH_ON,
};

enum class ChargeImage
{
	CHARGE_OFF,
	CHARGE_ON,
};

enum class ChracterImage
{
	HP_3,
	HP_2,
	HP_1_0,
};

enum class HeartImage
{
	ON,
	OFF,
};

enum class IntroMenu
{
	NEW_GAME_START_BUTTON,
	LOAD_GAME_BUTTON,
	SETTING_BUTTON,
	QUIT_BUTTON,
};


/// <summary>
/// UIManager 겸 GameManager의 역할을 맡고있는 매니저 입니다..
/// 플레이어의 체력상태, 대시스킬이나 차지스킬의 보유 여부 등을 저장하고 있고
/// 각 종 UI상태를 체크합니다.
/// </summary>
class UIManager
{
	DECLARE_SINGLE(UIManager);

private:
	// Fade In 할 오브젝트 패널
	GameObject* _fadeInObj;

	//◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 인게임 ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 
	SpriteRenderer* _chracterImageSpriteRenderer;		// 인게임 내의 캐릭터 이미지 스프라이트렌더러
	vector<Sprite*> _chracterImages;					// 인게임 내의 캐릭터 이미지 3개 모음

	SpriteRenderer* _dashImageSpriteRenderer;			// 인게임 내의 대시 이미지 스프라이트렌더러
	vector<Sprite*> _dashImages;						// 인게임 내의 대시 이미지 2개 모음

	SpriteRenderer* _chargeImageSpriteRenderer;			// 인게임 내의 차지 이미지 스프라이트렌더러
	vector<Sprite*> _chargeImages;						// 인게임 내의 차지 이미지 2개 모음

	vector<SpriteRenderer*> _heartImagesSpriteRenderer;	// 체력 이미지 오브젝트들 
	vector<Sprite*> _heartImages;						// 체력 이미지 2개 모음

	GameObject* _inGameMenuPanel;						// 인게임 메뉴 패널
	vector<GameObject*> _menuButtons;					// 인게임 내의 메뉴 버튼 오브젝트 3개 모음

	GameObject* _inGameSettingPanel;					// 인게임 세팅 패널 오브젝트
	GameObject* _inGameSettingQuitButton;				// 인게임 세팅 Quit 버튼
	vector<GameObject*> _inGameSettingVolumeBalls;		// 인게임 세팅 볼륨 조절 볼
	float _masterVol = 0.5f;							// 마스터볼륨 일단 0.5f 로 절반
	float _sfxVol = 0.5f;								// SFX볼륨 일단 0.5f 로 절반
	float _musicVol = 0.5f;								// 음악볼륨 일단 0.5f 로 절반
	float _masterSetX = 100.f;
	float _sfxSetX = 100.f;
	float _musicSetX = 100.f; 

	GameObject* _inGameQuitPanel;						// 인게임 Quit패널
	vector<GameObject*> _quitPanelButtons;				// 인게임 Quit패널의 버튼들(yes, no)

	B3_11Prefab* _player;								// 플레이어 정보를 담을 거임

	bool _isInGameMenuPanel = false;					// 얘는 필요함
	int _menuInfo = 0;

	bool _isInGameQuitPanel = false;					// 필요없는듯?
	int _quitInfo = 1;

	GameObject* _inGameOverPanel;						// 게임 오버 패널
	vector<GameObject*> _gameOverButtons;

	bool _isDash;				// 씬전환시 플레이어한테 전달!
	bool _isCharge;				// 씬전환시 플레이어한테 전달!
	int _playerHp = 3;			// 씬전환시 플레이어한테 전달!
	bool _isGameOver = false;
	int _gameOverInfo = 0;

	GameObject* _inGameClearPanel;						// 게임 클리어 패널

	bool _isGameClear = false;

	//◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 인트로  ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 
	GameObject* _introPanel;
	vector<GameObject*> _introButtons;
	int _introInfo = 0;

public:
	// Fade In 할 오브젝트 패널을 넣어주는 함수
	void SetFadeInObj(GameObject* fadeInObj) { _fadeInObj = fadeInObj; }

	//◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 인게임 ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 
	void SetChracterImageObject(SpriteRenderer* chracterImageSpriteRenderer) { _chracterImageSpriteRenderer = chracterImageSpriteRenderer;}
	void SetDashImageObject(SpriteRenderer* dashImageSpriteRenderer) { _dashImageSpriteRenderer = dashImageSpriteRenderer; }
	void SetChargeImageObject(SpriteRenderer* chargeImageSpriteRenderer) { _chargeImageSpriteRenderer = chargeImageSpriteRenderer; }
	void SetHeartImageObject(SpriteRenderer* heartImagesSpriteRenderer) { _heartImagesSpriteRenderer.push_back(heartImagesSpriteRenderer); }

	void SetChracterImages(Sprite* characterImage) { _chracterImages.push_back(characterImage); }
	void SetDashImages(Sprite* dashImage) { _dashImages.push_back(dashImage); }
	void SetChargeImages(Sprite* chargeImage) { _chargeImages.push_back(chargeImage); }
	void SetHeartImages(Sprite* heartImage) { _heartImages.push_back(heartImage); }

	void SetInGameMenuPanel(GameObject* inGameMenuPanel) { _inGameMenuPanel = inGameMenuPanel;}
	vector<GameObject*> GetMenuButtons() { return _menuButtons; }
	void SetMenuButtons(GameObject* menuButton) { _menuButtons.push_back(menuButton); }
	
	void SetInGameSettingPanel(GameObject* inGameSettingPanel) { _inGameSettingPanel = inGameSettingPanel;}
	void SetInGameSettingQuitButton(GameObject* inGameSettingQuitButton) { _inGameSettingQuitButton = inGameSettingQuitButton; }
	void SetInGameSettingVolumeBalls(GameObject* inGameSettingVolumeBalls) { _inGameSettingVolumeBalls.push_back(inGameSettingVolumeBalls); }
	
	void SetInGameQuitPanel(GameObject* inGameQuitPanel) { _inGameQuitPanel = inGameQuitPanel; }
	void SetQuitButtons(GameObject* quitButton) { _quitPanelButtons.push_back(quitButton); }

	Transform* GetPlayerTransform();
	void SetPlayer(B3_11Prefab* player) { _player = player; }

	void InGameMenuControl();

	void InGameImageUIControl();

	void InGameOverControl();

	void InGameClearControl();

	bool GetIsDash() { return _isDash; }
	bool GetIsCharge() { return _isCharge; }
	int GetPlayerHp() { return _playerHp; }

	GameObject* GetInGameOverPanel() { return _inGameOverPanel; }
	void SetInGameOverPanel(GameObject* inGameOverPanel) { _inGameOverPanel = inGameOverPanel; }
	void SetIsTrueInGameOverPanel();
	void SetGameOverPanelButtons(GameObject* gameOverButtons) { _gameOverButtons.push_back(gameOverButtons); }
	
	bool GetIsGameOver() { return _isGameOver; }
	void SetIsGameOver(bool value) { _isGameOver = value; }
	void SetIsGameClear(bool value) { _isGameClear = value; }

	GameObject* GetInGameClearPanel() { return _inGameClearPanel; }
	void SetInGameClearPanel(GameObject* inGameClearPanel) { _inGameClearPanel = inGameClearPanel; }

	//◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 인트로  ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 
	void SetIntroPanel(GameObject* introPanel) { _introPanel = introPanel; }
	vector<GameObject*> GetIntroButtons() { return _introButtons; }
	void SetIntroButtons(GameObject* introButton) { _introButtons.push_back(introButton); }

	void IntroMenuControl();

	//◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 리셋  ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎ 
	void ResetUIVector()
	{
		_introButtons.clear();
		_menuButtons.clear();
		_gameOverButtons.clear();
		_quitPanelButtons.clear();
		_inGameSettingVolumeBalls.clear();
		_chracterImages.clear();
		_dashImages.clear();
		_heartImagesSpriteRenderer.clear();
		_chracterImages.clear();
		_inGameSettingVolumeBalls.clear();
	}

	void Update();
};

