#include "pch.h"
#include "CircleRenderer.h"
#include "JW2DEngine.h"
#include "Transform.h"
#include "GameObject.h"
#include "CircleCollider.h"

CircleRenderer::CircleRenderer(GameObject* gameObject)
	: RendererBase(gameObject),
	  _radius(100.f)
{
	_type = COMPONENT_TYPE::CIRCLE_RENDERER;
}

CircleRenderer::~CircleRenderer()
{}

void CircleRenderer::FinalUpdate()
{
	GEngine->SetTransform(GetGameObject()->GetComponent<Transform>()->GetWorldMatrix());

	GEngine->SetBrushColor(1, 1, 1, 1);

	GEngine->DrawFillCircleScreen(
		0,
		0,
		_radius);
}

