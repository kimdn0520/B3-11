#include "pch.h"
#include "JW2DEngine.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "JW2DEngine.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject)
	: RendererBase(gameObject), _isRender(true), _sprite(nullptr)
{
	_type = COMPONENT_TYPE::SPRITE_RENDERER;
	_transform = gameObject->GetComponent<Transform>();
}

SpriteRenderer::~SpriteRenderer()
{}

void SpriteRenderer::SetOpacity(float opacity)
{
	_sprite->opacity = opacity;
}

void SpriteRenderer::FinalUpdate()
{
	GEngine->SetTransform(_transform->GetWorldMatrix());

	if (_sprite != nullptr && _isRender)
	{
		if (GEngine->GetMainCamera() != nullptr)
		{
			if ((abs(GEngine->GetMainCameraTransform()->GetWorldPosition().x - _transform->GetLocalPosition().x) < SCREEN_WIDTH / 2 + _width / 2) &&
				(abs(GEngine->GetMainCameraTransform()->GetWorldPosition().y - _transform->GetLocalPosition().y) < SCREEN_HEIGHT / 2 + _height / 2))
			{
				_sprite->width = _width;
				_sprite->height = _height;
				GEngine->DrawSprite
				(
					_sprite,
					_transform
				);
			}
			else if(this->GetGameObject()->GetTag() == (int)TAG::UI)
			{
				_sprite->width = _width;
				_sprite->height = _height;
				GEngine->DrawSprite
				(
					_sprite,
					_transform
				);
			}
		}
		else
		{
			_sprite->width = _width;
			_sprite->height = _height;
			GEngine->DrawSprite
			(
				_sprite,
				_transform
			);
		}
	}
}
