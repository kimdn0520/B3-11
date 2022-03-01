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
/// UIManager �� GameManager�� ������ �ð��ִ� �Ŵ��� �Դϴ�..
/// �÷��̾��� ü�»���, ��ý�ų�̳� ������ų�� ���� ���� ���� �����ϰ� �ְ�
/// �� �� UI���¸� üũ�մϴ�.
/// </summary>
class UIManager
{
	DECLARE_SINGLE(UIManager);

private:
	// Fade In �� ������Ʈ �г�
	GameObject* _fadeInObj;

	//�ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� �ΰ��� �ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� 
	SpriteRenderer* _chracterImageSpriteRenderer;		// �ΰ��� ���� ĳ���� �̹��� ��������Ʈ������
	vector<Sprite*> _chracterImages;					// �ΰ��� ���� ĳ���� �̹��� 3�� ����

	SpriteRenderer* _dashImageSpriteRenderer;			// �ΰ��� ���� ��� �̹��� ��������Ʈ������
	vector<Sprite*> _dashImages;						// �ΰ��� ���� ��� �̹��� 2�� ����

	SpriteRenderer* _chargeImageSpriteRenderer;			// �ΰ��� ���� ���� �̹��� ��������Ʈ������
	vector<Sprite*> _chargeImages;						// �ΰ��� ���� ���� �̹��� 2�� ����

	vector<SpriteRenderer*> _heartImagesSpriteRenderer;	// ü�� �̹��� ������Ʈ�� 
	vector<Sprite*> _heartImages;						// ü�� �̹��� 2�� ����

	GameObject* _inGameMenuPanel;						// �ΰ��� �޴� �г�
	vector<GameObject*> _menuButtons;					// �ΰ��� ���� �޴� ��ư ������Ʈ 3�� ����

	GameObject* _inGameSettingPanel;					// �ΰ��� ���� �г� ������Ʈ
	GameObject* _inGameSettingQuitButton;				// �ΰ��� ���� Quit ��ư
	vector<GameObject*> _inGameSettingVolumeBalls;		// �ΰ��� ���� ���� ���� ��
	float _masterVol = 0.5f;							// �����ͺ��� �ϴ� 0.5f �� ����
	float _sfxVol = 0.5f;								// SFX���� �ϴ� 0.5f �� ����
	float _musicVol = 0.5f;								// ���Ǻ��� �ϴ� 0.5f �� ����
	float _masterSetX = 100.f;
	float _sfxSetX = 100.f;
	float _musicSetX = 100.f; 

	GameObject* _inGameQuitPanel;						// �ΰ��� Quit�г�
	vector<GameObject*> _quitPanelButtons;				// �ΰ��� Quit�г��� ��ư��(yes, no)

	B3_11Prefab* _player;								// �÷��̾� ������ ���� ����

	bool _isInGameMenuPanel = false;					// ��� �ʿ���
	int _menuInfo = 0;

	bool _isInGameQuitPanel = false;					// �ʿ���µ�?
	int _quitInfo = 1;

	GameObject* _inGameOverPanel;						// ���� ���� �г�
	vector<GameObject*> _gameOverButtons;

	bool _isDash;				// ����ȯ�� �÷��̾����� ����!
	bool _isCharge;				// ����ȯ�� �÷��̾����� ����!
	int _playerHp = 3;			// ����ȯ�� �÷��̾����� ����!
	bool _isGameOver = false;
	int _gameOverInfo = 0;

	GameObject* _inGameClearPanel;						// ���� Ŭ���� �г�

	bool _isGameClear = false;

	//�ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� ��Ʈ��  �ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� 
	GameObject* _introPanel;
	vector<GameObject*> _introButtons;
	int _introInfo = 0;

public:
	// Fade In �� ������Ʈ �г��� �־��ִ� �Լ�
	void SetFadeInObj(GameObject* fadeInObj) { _fadeInObj = fadeInObj; }

	//�ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� �ΰ��� �ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� 
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

	//�ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� ��Ʈ��  �ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� 
	void SetIntroPanel(GameObject* introPanel) { _introPanel = introPanel; }
	vector<GameObject*> GetIntroButtons() { return _introButtons; }
	void SetIntroButtons(GameObject* introButton) { _introButtons.push_back(introButton); }

	void IntroMenuControl();

	//�ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� ����  �ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ� 
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

