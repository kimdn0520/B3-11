#pragma once
#include "Component.h"

class Transform;
class Sprite;
class Text;

class Button : public Component
{
public:
	Button(GameObject* gameObject);
	virtual ~Button();

private:
	ButtonStatus _status = ButtonStatus::NORMAL;
	ButtonStatus _keyBoardStatus = ButtonStatus::NORMAL;	// 키보드로 선택중일때..
	
	Transform* _transform = nullptr;

	Sprite* _sprite = nullptr;				// 여기다가 상태에따라 담아준다.

	Transform* _canvasTransform = nullptr;

	// 상태에따른 스프라이트를 세팅해줘야한다.
	Sprite* _normalSprite = nullptr;		// 일반적인 상태
	Sprite* _highlightSprite = nullptr;		// 마우스 포인터가 사각 영역 안에 있을때
	Sprite* _pressedSprite = nullptr;		// 마우스로 누르고 있을때
	// Sprite* _selectedSprite;				// 선택된 상태 (사각 영역 안에서 벗어난 영역을선택하면 normal 상태가 된다)

	float _width = 0.f;

	float _height = 0.f;

	float _windowWidth = 0.f;

	float _windowHeight = 0.f;

	bool _isSelected = false;

public:
	bool GetSelected() { return _isSelected; }
	void SetSelected(bool value) { _isSelected = value; }

	ButtonStatus GetButtonStatus() { return _status; }
	void SetStatus(ButtonStatus status) { _status = status; }
	void SetKeyBoardStatus(ButtonStatus keyBoardStatus) { _keyBoardStatus = keyBoardStatus; }

	void SetNormalSprite(Sprite* sprite) { _normalSprite = sprite; }
	void SetHighlightSprite(Sprite* sprite) { _highlightSprite = sprite; }
	void SetPressedSprite(Sprite* sprite) { _pressedSprite = sprite; }

	// 스프라이트의 크기를 이걸로 다시 조정..?
	void SetWH(float width, float height) { _width = width; _height = height; }

	Transform* GetCanvasTransform() { return _canvasTransform; }
	void SetCanvas(Transform* canvasTransform) { _canvasTransform = canvasTransform; }

	virtual void Update() override;

	virtual void FinalUpdate() override;
};


