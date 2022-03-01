#include "pch.h"
#include "Camera.h"
#include "JW2DEngine.h"
#include "GameObject.h"

Camera::Camera(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::CAMERA),
	  _width(static_cast<float>(GEngine->GetWindow().width)), 
	  _height(static_cast<float>(GEngine->GetWindow().height)),
	  _size(1.0f)
{}

Camera::~Camera()
{}

void Camera::LateUpdate()
{
	// ReSize 될 수도 있으니 업데이트 해주자..
	_width = static_cast<float>(GEngine->GetWindow().width);
	_height = static_cast<float>(GEngine->GetWindow().height);
}
