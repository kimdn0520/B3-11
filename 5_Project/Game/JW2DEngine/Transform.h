#pragma once
#include "Component.h"

class GameObject;
/// <summary>
/// ������Ʈ�� �ϳ��� Transform �̴�.
/// Transform ���� Update���� ���ð����� ����ؼ� ���尪�� ���Ѵ�.
/// �̵�, ��ȯ, �θ� ����, ��ǥ�����Ⱑ �����ϴ�.
/// </summary>
class Transform : public Component
{
public:
	Transform(GameObject* gameObject);
	virtual ~Transform();

public:
	virtual void Awake() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	Transform* GetParent() { return _parent; }
	void SetParent(Transform* parent);

	// ���� ��ǥ�� ��� �´�.
	Vector2 GetLocalPosition() { return _localPosition; }
	Vector2 GetLocalRotation() { return _localRotation; }
	Vector2 GetLocalScale() { return _localScale; }

	// ���� ��ǥ�� ��� �´�.
	Vector2 GetWorldPosition() { return _worldPosition; }
	Vector2 GetWorldRotation() { return _worldRotation; }
	Vector2 GetWorldScale() { return _worldScale; }

	Matrix GetWorldMatrix() { return _matWorld; }

	void SetLocalPosition(Vector2 position) { _localPosition = position; CalculateWorldMatrix();}
	void SetLocalRotation(float delta)
	{
		float rotateX = _localRotation.x * cos(delta) - _localRotation.y * sin(delta);
		float rotateY = _localRotation.x * sin(delta) + _localRotation.y * cos(delta);

		_localRotation = Vector2(rotateX, rotateY).Normalized();

		CalculateWorldMatrix();
	}
	void SetLocalScale(Vector2 scale) {
	_localScale = scale; CalculateWorldMatrix(); }

	void Translate(float x, float y) { _localPosition.x += x; _localPosition.y += y; }
	void Translate(Vector2 vec) { _localPosition.x += vec.x; _localPosition.y += vec.y; }

	void CalculateWorldMatrix();

	void Rotate(float rotate);
	void RotateArounds(GameObject* gameObj, float angle, float dist);

private:
	// Parent �������� local ��ǥ�� ������ �ִ�.
	Vector2 _localPosition = { 0.f, 0.f };
	Vector2 _localRotation = { 1.f, 0.f };
	Vector2	_localScale = { 1.f, 1.f };

	Vector2 _worldPosition = { 0.f, 0.f };
	Vector2 _worldRotation = { 1.f, 0.f };
	Vector2 _worldScale = { 1.f, 1.f };

	Matrix _matLocal = {};					// ����ϸ鼭 �߰��� �����ϱ����� ���� ���
	Matrix _matWorld = {};					// ���� ��� ����ؾ���.

	Transform* _parent = nullptr;			// �θ��� ���� 

	float radian = 0.f;

private:
	void SetWorldPosition();
	void SetWorldRotation();
	void SetWorldScale();
};
