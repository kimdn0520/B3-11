#include "pch.h"
#include "RendererBase.h"

RendererBase::RendererBase(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::SPRITE_RENDERER)
{
}

RendererBase::~RendererBase()
{
}
