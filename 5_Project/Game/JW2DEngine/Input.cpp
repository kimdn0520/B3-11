#include "pch.h"
#include "Input.h"
#include "JW2DEngine.h"

void Input::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE); // ��� Ű ��(0~255) �� NONE ���·� �ʱ�ȭ�Ѵ�.
}

void Input::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (_hwnd != hwnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
			_states[key] = KEY_STATE::NONE;

		return;
	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (GetKeyboardState(asciiKeys) == false)
		return;

	for (int key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// Ű�� ���� ������ true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&_mousePos);
	::ScreenToClient(GEngine->GetWindow().hWnd, &_mousePos);
}

float Input::GetAxisRawHorizontal()
{
	if (GetButton(KEY_TYPE::LEFT))
		return -1.f;
	else if(GetButton(KEY_TYPE::RIGHT))
		return 1.f;
	
	if (GetButtonUp(KEY_TYPE::LEFT))
		return 0.f;
	else if(GetButtonUp(KEY_TYPE::RIGHT))
		return 0.f;

	return 0.f;
}

float Input::GetAxisRawVertical()
{
	if (GetButton(KEY_TYPE::UP))
		return -1.f;
	else if (GetButton(KEY_TYPE::DOWN))
		return 1.f;

	if (GetButtonUp(KEY_TYPE::UP))
		return 0.f;
	else if (GetButtonUp(KEY_TYPE::DOWN))
		return 0.f;

	return 0.f;
}
