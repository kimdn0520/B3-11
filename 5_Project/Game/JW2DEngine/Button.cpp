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
/// ��ư�� ���ʸ��콺 ��ư���� ��ȣ�ۿ��Ѵ�.
/// </summary>
void Button::Update()
{
	_windowWidth = GEngine->GetWindow().width;
	_windowHeight = GEngine->GetWindow().height;

	float absolutePosX = _canvasTransform->GetWorldPosition().x - _transform->GetWorldPosition().x;
	float absolutePosY = _canvasTransform->GetWorldPosition().y - _transform->GetWorldPosition().y;

	// �� ��ư�� ȭ�鿡���� ������ ��ġ�� ����?
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
			// ���� �����־��� ���°� �� �̾ȿ��� UP�� �õ��ߴٸ�
			if (_status == ButtonStatus::PRESSED)
				_isSelected = true;				// ���ȴ�!

			_status = ButtonStatus::NORMAL;		// ��ư�� ���´� �븻�� �ٽùٲ�
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