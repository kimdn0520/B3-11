#include "pch.h"
#include "Panel.h"
#include "JW2DEngine.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"

Panel::Panel(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::PANEL),
	_transform(gameObject->GetComponent<Transform>())
{}

Panel::~Panel()
{}

void Panel::FinalUpdate()
{
	GEngine->SetTransform(_transform->GetWorldMatrix());


	if (_sprite != nullptr)
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
