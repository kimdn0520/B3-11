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
	ButtonStatus _keyBoardStatus = ButtonStatus::NORMAL;	// Ű����� �������϶�..
	
	Transform* _transform = nullptr;

	Sprite* _sprite = nullptr;				// ����ٰ� ���¿����� ����ش�.

	Transform* _canvasTransform = nullptr;

	// ���¿����� ��������Ʈ�� ����������Ѵ�.
	Sprite* _normalSprite = nullptr;		// �Ϲ����� ����
	Sprite* _highlightSprite = nullptr;		// ���콺 �����Ͱ� �簢 ���� �ȿ� ������
	Sprite* _pressedSprite = nullptr;		// ���콺�� ������ ������
	// Sprite* _selectedSprite;				// ���õ� ���� (�簢 ���� �ȿ��� ��� �����������ϸ� normal ���°� �ȴ�)

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

	// ��������Ʈ�� ũ�⸦ �̰ɷ� �ٽ� ����..?
	void SetWH(float width, float height) { _width = width; _height = height; }

	Transform* GetCanvasTransform() { return _canvasTransform; }
	void SetCanvas(Transform* canvasTransform) { _canvasTransform = canvasTransform; }

	virtual void Update() override;

	virtual void FinalUpdate() override;
};


