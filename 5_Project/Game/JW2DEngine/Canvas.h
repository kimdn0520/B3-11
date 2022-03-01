#pragma once
#include "Component.h"

class GameObject;
class Transform;

/// <summary>
/// Canvas�� ��� UI ��ü�� �������� �����ϱ� ���� ��Ʈ ������Ʈ �̴�.
/// ��� UI ���� ��ҵ��� ��� ĵ���� �ؿ� ��ġ�Ѵ�(ĵ������ �ڽ�)
/// 3������ ������尡 ������ Screen Space - Camera ������� �Ѵ�.
/// �� ���� ĵ������ �׻� ī�޶� ����ٴϸ� ī�޶� �տ� ��ġ�ϰ� �ȴ�.
/// ���� ��ǥ �󿡼��� ��ġ ���� ������ �ȴ�.
/// </summary>
class Canvas : public Component
{
public:
	Canvas(GameObject* gameObject);
	virtual ~Canvas();

private:
	GameObject* _renderCamera;		// UI�� �������� ī�޶� ����ؾ��Ѵ�.

	Transform* _transform;

public:
	void SetRenderCamera(GameObject* renderCamera);

	void Update();

	void LateUpdate();
};

