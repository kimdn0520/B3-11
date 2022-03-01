#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "JW2DEngine.h"

Transform::Transform(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::TRANSFORM),
	_matLocal(Matrix::Identity()), _matWorld(Matrix::Identity())
{}

Transform::~Transform()
{

}

void Transform::Awake()
{
	CalculateWorldMatrix();
}

void Transform::Update()
{
	CalculateWorldMatrix();
}

/// <summary>
/// 카메라를 쫒아다니는 캔버스,, 등 때문에 해줘야합니다.
/// </summary>
void Transform::LateUpdate()
{
	CalculateWorldMatrix();
}

void Transform::FinalUpdate()
{
	CalculateWorldMatrix();

	if (SCENE_MANAGER->isDebug)
	{
		Matrix matScale = Matrix::Identity();
		matScale._11 = 1;
		matScale._22 = 1;

		Matrix matTranslate = Matrix::Identity();
		matTranslate.dx = _worldPosition.x;
		matTranslate.dy = _worldPosition.y;
		
		Matrix textMatrix = matScale * matTranslate;

		// textMatrix.dy -= 120.f;

		GEngine->SetTransform(textMatrix);

		string text = "(" + to_string((int)GetWorldPosition().x) + ", " + to_string((int)GetWorldPosition().y) + ")";

		// 여기서 string -> const char* 로 변환해서 넣어주는걸로 하였다..!
		const char* transText = text.c_str();

		GEngine->DrawTextScreen(0, 0,
			400.f, 100.f, 0, transText);
	}
}

void Transform::SetParent(Transform* parent)
{
	_parent = parent;												// 부모 트랜스폼을 얻어오고
	parent->GetGameObject()->SetChildObject(this->GetGameObject());	// 부모에 자식 게임오브젝트로도 등록한다.
}

void Transform::CalculateWorldMatrix()
{
	// 월드 행렬을 만들어줌
	// 먼저 원점으로 옮기고 스케일하고 회전돌리고 다시 내 원래 로컬 포지션으로
	Matrix matScale = Matrix::Identity();
	matScale._11 = _localScale.x;
	matScale._22 = _localScale.y;

	Matrix matRotation = Matrix::Identity();
	matRotation._11 = _localRotation.x;
	matRotation._12 = -_localRotation.y;
	matRotation._21 = _localRotation.y;
	matRotation._22 = _localRotation.x;

	Matrix matTranslate = Matrix::Identity();
	matTranslate.dx = _localPosition.x;
	matTranslate.dy = _localPosition.y;

	_matLocal = matScale * matRotation * matTranslate;	// 로컬에 넣어준다.
	_matWorld = _matLocal;								// 부모가 없으면_matLocal이 월드행렬을 의미함.

	// 부모가 있다면..!
	// _matWorld에 부모의 월드매트릭스를 곱해준다.
	if (_parent != nullptr)
	{
		_matWorld = _matLocal * _parent->_matWorld;
	}

	SetWorldPosition();
	SetWorldRotation();
	SetWorldScale();
}

/// <summary>
/// 자기 자신 중심을 기준으로 회전시킨다.
/// </summary>
void Transform::Rotate(float rotate)
{
	float radian = rotate * (3.1415f / 180.f);

	// 회전 행렬 적용 
	float nx = _localRotation.x * cos(radian) - _localRotation.y * sin(radian);
	float ny = _localRotation.x * sin(radian) + _localRotation.y * cos(radian);

	_localRotation = Vector2(nx, ny).Normalized();
}

/// <summary>
/// 특정 오브젝트 주위로 회전시킨다. (공전)
/// </summary>
void Transform::RotateArounds(GameObject* gameObj, float angle, float dist)
{
	(radian >= 2 * 3.1415f || radian <= -2 * 3.1415f)
		? radian = 0 : radian += angle * (3.1415f / 180.f);

	_localPosition.x = gameObj->GetComponent<Transform>()->GetWorldMatrix().dx + dist * cos(radian);
	_localPosition.y = gameObj->GetComponent<Transform>()->GetWorldMatrix().dy + dist * sin(radian);
}

void Transform::SetWorldPosition()
{
	_worldPosition = Vector2(_matWorld.dx, _matWorld.dy);
}

void Transform::SetWorldRotation()
{
	_worldRotation = Vector2(_matWorld._22, _matWorld._21).Normalized();
}

void Transform::SetWorldScale()
{
	Vector2 tmpScale(0.f, 0.f);
	tmpScale.x = sqrtf(powf(_matWorld.m11, 2.f) + powf(_matWorld.m12, 2.f));
	tmpScale.y = sqrtf(powf(_matWorld.m21, 2.f) + powf(_matWorld.m22, 2.f));

	_worldScale = Vector2(tmpScale.x, tmpScale.y);
}