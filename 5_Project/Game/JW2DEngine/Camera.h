#pragma once
#include "Component.h"

class GameObject;
class Transform;

/// <summary>
/// 해당 게임오브젝트의 Transform을 따라간다.
/// 화면이 움직이는게 아니라, 객체들의 좌표가 수정되어
/// 마치 화면이 움직이는 것처럼 보이도록 속이는 것
/// </summary>
class Camera : public Component
{
public:
	Camera(GameObject* gameObject);
	virtual ~Camera();

private:
	float _width;;
	float _height;

	float _size;

public:
	float GetWidth() { return _width; }
	float GetHeight() { return _height;}

	virtual void LateUpdate() override;
};

