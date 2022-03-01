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
	// 상대 속도
	Vector2 relativeVelocity = _velocity - otherRigidbody->GetVelocity();

	// 상대 속도를 norvalReflVec 에 내적한 값이 
	// 양수면(예각!) 멀어지는거고 음수면(둔각!) 가까워 지는 것이다.
	if (relativeVelocity.Dot(relativeVelocity, _normal) < 0.0f)
	{
		float epsilon = 1.f;	// 반발 계수(1이면 완전탄성충돌 0이면 완전비탄성충돌  0 <= e <= 1)

		// 충격량을 계산해야한다. 
		// 가속도로서 공의 속도에 벡터를 더해주어야 하니까 충격 벡터로 만들었다.
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

// 업데이트냐 픽스드냐.. 어디서 먼저 호출?
void Rigidbody::Update()
{
	if (_bodyType == BODY_TYPE::Static)
		return;

	_position.x = _transform->GetWorldMatrix().dx;
	_position.y = _transform->GetWorldMatrix().dy;

	_velocity.x = _velocity.x - (_velocity.x * _linearDragX);					  // x방향 속도 마찰력 주기..
	_velocity.y = _velocity.y - (_velocity.y * _linearDragY);					  // y방향 속도 마찰력 주기..

   /*if(_velocity.x <= 0)
	   _velocity.x = 0;*/

	if (_isGravity)
	{
		_velocity.y = _velocity.y + _gravity.y * _gravityScale * DELTA_TIME;	  // 중력

		//if (_velocity.y >= 50)
		//{
		//	_velocity.y = 50;	// 최대 가속도 20
		//}
	}

	_transform->SetLocalPosition(_transform->GetLocalPosition() + _velocity);	  // velocity 만큼 더해준다.
}