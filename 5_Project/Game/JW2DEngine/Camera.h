#pragma once
#include "Component.h"

class GameObject;
class Transform;

/// <summary>
/// �ش� ���ӿ�����Ʈ�� Transform�� ���󰣴�.
/// ȭ���� �����̴°� �ƴ϶�, ��ü���� ��ǥ�� �����Ǿ�
/// ��ġ ȭ���� �����̴� ��ó�� ���̵��� ���̴� ��
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

