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
/// ī�޶� �i�ƴٴϴ� ĵ����,, �� ������ ������մϴ�.
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

		// ���⼭ string -> const char* �� ��ȯ�ؼ� �־��ִ°ɷ� �Ͽ���..!
		const char* transText = text.c_str();

		GEngine->DrawTextScreen(0, 0,
			400.f, 100.f, 0, transText);
	}
}

void Transform::SetParent(Transform* parent)
{
	_parent = parent;												// �θ� Ʈ�������� ������
	parent->GetGameObject()->SetChildObject(this->GetGameObject());	// �θ� �ڽ� ���ӿ�����Ʈ�ε� ����Ѵ�.
}

void Transform::CalculateWorldMatrix()
{
	// ���� ����� �������
	// ���� �������� �ű�� �������ϰ� ȸ�������� �ٽ� �� ���� ���� ����������
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

	_matLocal = matScale * matRotation * matTranslate;	// ���ÿ� �־��ش�.
	_matWorld = _matLocal;								// �θ� ������_matLocal�� ��������� �ǹ���.

	// �θ� �ִٸ�..!
	// _matWorld�� �θ��� �����Ʈ������ �����ش�.
	if (_parent != nullptr)
	{
		_matWorld = _matLocal * _parent->_matWorld;
	}

	SetWorldPosition();
	SetWorldRotation();
	SetWorldScale();
}

/// <summary>
/// �ڱ� �ڽ� �߽��� �������� ȸ����Ų��.
/// </summary>
void Transform::Rotate(float rotate)
{
	float radian = rotate * (3.1415f / 180.f);

	// ȸ�� ��� ���� 
	float nx = _localRotation.x * cos(radian) - _localRotation.y * sin(radian);
	float ny = _localRotation.x * sin(radian) + _localRotation.y * cos(radian);

	_localRotation = Vector2(nx, ny).Normalized();
}

/// <summary>
/// Ư�� ������Ʈ ������ ȸ����Ų��. (����)
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