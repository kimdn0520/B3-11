#include "pch.h"
#include "Canvas.h"
#include "GameObject.h"
#include "Transform.h"

Canvas::Canvas(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::CANVAS),
	  _renderCamera(nullptr), _transform(gameObject->GetComponent<Transform>())
{}

Canvas::~Canvas()
{}

void Canvas::SetRenderCamera(GameObject* renderCamera)
{
	_renderCamera = renderCamera;
}

void Canvas::Update()
{
	
}

void Canvas::LateUpdate()
{
	// Canvas�� �������� Camera�� ���󰣴�.
	_transform->SetLocalPosition
	(
		_renderCamera->GetComponent<Transform>()->GetWorldPosition()
	);
}


