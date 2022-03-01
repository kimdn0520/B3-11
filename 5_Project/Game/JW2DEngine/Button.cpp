#include "pch.h"
#include "Button.h"
#include "JW2DEngine.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "Sprite.h"

Button::Button(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::BUTTON),
	  _transform(gameObject->GetComponent<Transform>())
{}

Button::~Button()
{}

/// <summary>
/// 버튼은 왼쪽마우스 버튼으로 상호작용한다.
/// </summary>
void Button::Update()
{
	_windowWidth = GEngine->GetWindow().width;
	_windowHeight = GEngine->GetWindow().height;

	float absolutePosX = _canvasTransform->GetWorldPosition().x - _transform->GetWorldPosition().x;
	float absolutePosY = _canvasTransform->GetWorldPosition().y - _transform->GetWorldPosition().y;

	// 이 버튼이 화면에서의 절대적 위치는 ㅇㄷ?
	if ((INPUT->GetMousePos().x >= (_windowWidth / 2 - _width / 2) - absolutePosX) &&
		(INPUT->GetMousePos().x <= (_windowWidth / 2 + _width / 2) - absolutePosX) &&
		(INPUT->GetMousePos().y >= (_windowHeight / 2 - _height / 2) - absolutePosY) &&
		(INPUT->GetMousePos().y <= (_windowHeight / 2 + _height / 2) - absolutePosY))
	{
		if (INPUT->GetButton(KEY_TYPE::LEFT_MOUSE))
		{
			_status = ButtonStatus::PRESSED;
		}
		else if (INPUT->GetButtonUp(KEY_TYPE::LEFT_MOUSE))
		{
			// 전에 눌려있었던 상태고 또 이안에서 UP을 시도했다면
			if (_status == ButtonStatus::PRESSED)
				_isSelected = true;				// 눌렸다!

			_status = ButtonStatus::NORMAL;		// 버튼의 상태는 노말로 다시바꿈
		}
		else
		{
			_status = ButtonStatus::HIGHLIGHT;
		}
	}
	else
	{
		_status = ButtonStatus::NORMAL;
	}
}

void Button::FinalUpdate()
{
	GEngine->SetTransform(_transform->GetWorldMatrix());

	if(_status == ButtonStatus::NORMAL)
		_sprite = _normalSprite;
	else if(_status == ButtonStatus::HIGHLIGHT)
		_sprite = _highlightSprite;
	else if(_status == ButtonStatus::PRESSED)
		_sprite = _pressedSprite;

	if(_keyBoardStatus == ButtonStatus::HIGHLIGHT)
		_sprite = _highlightSprite;
	else if (_keyBoardStatus == ButtonStatus::PRESSED)
		_sprite = _pressedSprite;

	_sprite->width = _width;
	_sprite->height = _height;

	if (_sprite != nullptr)
	{
		GEngine->DrawSprite
		(
			_sprite,
			_transform
		);
	}
}