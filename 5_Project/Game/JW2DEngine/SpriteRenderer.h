#pragma once
#include "RendererBase.h"

class GameObject;
class Transform;
class Sprite;
	
class SpriteRenderer : public RendererBase
{
public:
	SpriteRenderer(GameObject* gameObject);
	virtual ~SpriteRenderer();

public:
	void SetSprite(Sprite* sprite) {_sprite = sprite; }

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }
	void SetWH(float width, float height) { _width = width; _height = height; }

	// 투명도 조절
	void SetOpacity(float opacity);


	virtual void FinalUpdate() override;

	void SetRenderInactive() {_isRender = false;}

private:

bool _isRender;

	Transform* _transform;

	Sprite* _sprite;

	float _width = 0.f;
	float _height = 0.f;
};

