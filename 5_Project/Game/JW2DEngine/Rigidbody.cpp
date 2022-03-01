#include "pch.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"

Rigidbody::Rigidbody(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::RIGIDBODY),
	_bodyType(BODY_TYPE::Dynamic), _mass(1), _linearDragX(0), _linearDragY(0), _gravityScale(1),
	_gravity({ 0.0f, 9.8f }), _isGravity(false)
{
	_transform = gameObject->GetComponent<Transform>();
	_position = _transform->GetWorldPosition();
}

Rigidbody::~Rigidbody()
{}

void Rigidbody::MovePosition(Vector2 dir)
{

}

void Rigidbody::AddForce(Vector2 dir)
{
	if (_bodyType == BODY_TYPE::Static)
		return;

	_acceleration = (dir / _mass);
	_velocity = _velocity + _acceleration;
}

void Rigidbody::ResolveCollision(Rigidbody* otherRigidbody, Vector2 _normal)
{
	// ��� �ӵ�
	Vector2 relativeVelocity = _velocity - otherRigidbody->GetVelocity();

	// ��� �ӵ��� norvalReflVec �� ������ ���� 
	// �����(����!) �־����°Ű� ������(�а�!) ����� ���� ���̴�.
	if (relativeVelocity.Dot(relativeVelocity, _normal) < 0.0f)
	{
		float epsilon = 1.f;	// �ݹ� ���(1�̸� ����ź���浹 0�̸� ������ź���浹  0 <= e <= 1)

		// ��ݷ��� ����ؾ��Ѵ�. 
		// ���ӵ��μ� ���� �ӵ��� ���͸� �����־�� �ϴϱ� ��� ���ͷ� �������.
		Vector2 impulse = _normal * -(1.0f + epsilon) * relativeVelocity.Dot(relativeVelocity, _normal) /
			((1.0f / otherRigidbody->GetMass()) + (1.0f / _mass));

		//_velocity = _velocity + impulse;
		//otherRigidbody->SetVelocity( otherRigidbody->GetVelocity() + (impulse * -1));

		AddForce(impulse);
		otherRigidbody->AddForce(impulse * -1);
	}
}

void Rigidbody::FixedUpdate()
{
}

// ������Ʈ�� �Ƚ����.. ��� ���� ȣ��?
void Rigidbody::Update()
{
	if (_bodyType == BODY_TYPE::Static)
		return;

	_position.x = _transform->GetWorldMatrix().dx;
	_position.y = _transform->GetWorldMatrix().dy;

	_velocity.x = _velocity.x - (_velocity.x * _linearDragX);					  // x���� �ӵ� ������ �ֱ�..
	_velocity.y = _velocity.y - (_velocity.y * _linearDragY);					  // y���� �ӵ� ������ �ֱ�..

   /*if(_velocity.x <= 0)
	   _velocity.x = 0;*/

	if (_isGravity)
	{
		_velocity.y = _velocity.y + _gravity.y * _gravityScale * DELTA_TIME;	  // �߷�

		//if (_velocity.y >= 50)
		//{
		//	_velocity.y = 50;	// �ִ� ���ӵ� 20
		//}
	}

	_transform->SetLocalPosition(_transform->GetLocalPosition() + _velocity);	  // velocity ��ŭ �����ش�.
}