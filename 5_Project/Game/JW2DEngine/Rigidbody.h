#pragma once
#include "Component.h"

// [Dyanamic]
// 주변의 모든 물체와 상호작용이 가능하다.
// 캐릭터가 중력과 힘을 갖고 있어서 다른 물체와 부딪히면 뒤로 밀려난다.

// [Kinematic]
// 중력과 힘이 없고 스크립트에 의해 이동만할 때 사용한다.

// [Static]
// 움직이지 않는 물체
// 다이나믹 타입을 가지고 있는 캐릭터와 부딪힌 스태틱 타입의 돌은 움직이지 않는다.
// 캐릭터만 돌부리에 넘어지는 것

class Rigidbody : public Component
{
public:
	Rigidbody(GameObject* gameObject);
	virtual ~Rigidbody();

public:
	BODY_TYPE GetBodyType() { return _bodyType; }
	void SetBodyType(BODY_TYPE bodyType) { _bodyType = bodyType; }

	float GetMass()	{ return _mass; }
	void SetMass(float mass) { _mass = mass; }

	float GetLinearDragX() { return _linearDragX; }
	void SetLinearDragX(float linearDragX) { _linearDragX = linearDragX; }

	float GetLinearDragY() { return _linearDragY; }
	void SetLinearDragY(float linearDragY) { _linearDragY = linearDragY; }

	float GetGravityScale() { return _gravityScale; }
	void SetGravityScale(float gravityScale) { _gravityScale = gravityScale; }

	Vector2 GetVelocity() { return _velocity; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
	void SetVelocityX(float velocity) { _velocity.x = velocity; }
	void SetVelocityY(float velocity) { _velocity.y = velocity; }

	void SetAcceleration(Vector2 accel) {_acceleration = accel;}

	void OnGravity(bool value) { _isGravity = value; }

	// 위치로 이동
	void MovePosition(Vector2 dir);

	// 특정 방향으로 힘을 가함(관성 작용이 있음)
	void AddForce(Vector2 dir);

	void ResolveCollision(Rigidbody* otherRigidbody, Vector2 _normal);

	virtual void FixedUpdate() override;

	virtual void Update() override;

private:
	Transform* _transform;
	
	BODY_TYPE _bodyType;		// 바디 타입

	float _mass;				// 질량 (질량이 큰 물체와 작은 물체가 충돌하면 큰 물체가 적게 움직임)

	float _linearDragX;			// 마찰력 (질량이 크고 linearDrag가 크면 더 느리게 움직인다 0이면 계속 날아감)

	float _linearDragY;

	float _gravityScale;		// 중력 크기(값을 1로하면 기본 중력가속도인 9.8 m/s 가 적용)

	Vector2 _gravity;			// 중력(기본 9.8m/s)

	Vector2 _position;			// 위치

	Vector2 _velocity;			// 속도벡터

	Vector2 _acceleration;		// 가속도벡터

	bool _isGravity;			// 중력 작용을 할건지 말건지
};

