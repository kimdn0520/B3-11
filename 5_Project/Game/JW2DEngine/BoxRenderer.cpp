#include "pch.h"
#include "BoxRenderer.h"
#include "JW2DEngine.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoxCollider.h"

BoxRenderer::BoxRenderer(GameObject* gameObject)
	: RendererBase(gameObject),
	  _width(100.f), _height(100.f)
{
	_type = COMPONENT_TYPE::BOX_RENDERER;
}

BoxRenderer::~BoxRenderer()
{}

void BoxRenderer::FinalUpdate()
{
	GEngine->SetTransform(GetGameObject()->GetComponent<Transform>()->GetWorldMatrix());

	GEngine->SetBrushColor(1, 1, 1, 1);

	GEngine->DrawFillRectScreen(
		-(_width / 2),
		-(_height / 2),
		(_width / 2),
		(_height / 2));
}

