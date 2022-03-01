#pragma once
#include "Component.h"

class GameObject;
/// <summary>
/// 컴포넌트중 하나인 Transform 이다.
/// Transform 내부 Update에서 로컬값들을 계산해서 월드값을 구한다.
/// 이동, 변환, 부모 설정, 좌표얻어오기가 가능하다.
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

	// 로컬 좌표를 얻어 온다.
	Vector2 GetLocalPosition() { return _localPosition; }
	Vector2 GetLocalRotation() { return _localRotation; }
	Vector2 GetLocalScale() { return _localScale; }

	// 월드 좌표를 얻어 온다.
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
	// Parent 기준으로 local 좌표를 가지고 있다.
	Vector2 _localPosition = { 0.f, 0.f };
	Vector2 _localRotation = { 1.f, 0.f };
	Vector2	_localScale = { 1.f, 1.f };

	Vector2 _worldPosition = { 0.f, 0.f };
	Vector2 _worldRotation = { 1.f, 0.f };
	Vector2 _worldScale = { 1.f, 1.f };

	Matrix _matLocal = {};					// 계산하면서 중간에 저장하기위한 로컬 행렬
	Matrix _matWorld = {};					// 월드 행렬 계산해야함.

	Transform* _parent = nullptr;			// 부모의 정보 

	float radian = 0.f;

private:
	void SetWorldPosition();
	void SetWorldRotation();
	void SetWorldScale();
};
