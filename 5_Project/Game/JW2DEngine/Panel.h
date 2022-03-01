#pragma once
#include "Component.h"

class Transform;
class Sprite;

class Panel : public Component
{
public:
	Panel(GameObject* gameObject);
	virtual ~Panel();

private:
	Transform* _transform = nullptr;

	Sprite* _sprite = nullptr;

	float _width = 0.f;

	float _height = 0.f;

public:
	// ��������Ʈ�� ũ�⸦ �̰ɷ� �ٽ� ����..?
	void SetWH(float width, float height) { _width = width; _height = height; }

	void SetSprite(Sprite* sprite) { _sprite = sprite; }

	Sprite* GetSprite() { return _sprite; }

	virtual void FinalUpdate() override;
};
