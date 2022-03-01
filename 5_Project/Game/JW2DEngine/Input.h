#pragma once

/// <summary>
/// ������ü�� �̷��� ��ȭ������ ����°�(����) ����.
/// </summary>
enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	NUM_1 = 0x31,
	NUM_2 = 0x32,
	NUM_3 = 0x33,

	F1 = VK_F1,
	F2 = VK_F2,
	F3= VK_F3,

	ESC = VK_ESCAPE,
	SPACE = VK_SPACE,
	SHIFT = VK_SHIFT,
	CTRL = VK_CONTROL,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Z = 'Z',

	LEFT_MOUSE = VK_LBUTTON,
	RIGHT_MOUSE = VK_RBUTTON,
	ALT = VK_MENU,
	// M = 'M',
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END,
};

enum
{
	KEY_TYPE_COUNT = 256,
	KEY_STATE_COUNT = KEY_STATE::END,
};

class Input
{
	DECLARE_SINGLE(Input);

public:
	void Init(HWND hwnd);
	void Update();

	// ������ ���� ��
	bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESS; }
	// �� ó�� ������ ��
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	// �� ó�� ������ ���� ��
	bool GetButtonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }

	float GetAxisRawHorizontal();
	float GetAxisRawVertical();

	const POINT& GetMousePos() 
	{ 
		int a = 3;
		return _mousePos; 
	}

public:
	void SetState(KEY_TYPE key, KEY_STATE keyState) { _states[(int)key] = keyState; }

private:
	inline KEY_STATE GetState(KEY_TYPE key) { return _states[(int)key]; }

private:
	HWND _hwnd;

	// �� Ű�� �ش��ϴ� ���¸� ���ͷ� Ȯ���Ѵ�.
	vector<KEY_STATE> _states;

	POINT _mousePos = { 0, 0 };
};

