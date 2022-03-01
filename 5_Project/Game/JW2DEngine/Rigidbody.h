#pragma once
#include "Component.h"

// [Dyanamic]
// �ֺ��� ��� ��ü�� ��ȣ�ۿ��� �����ϴ�.
// ĳ���Ͱ� �߷°� ���� ���� �־ �ٸ� ��ü�� �ε����� �ڷ� �з�����.

// [Kinematic]
// �߷°� ���� ���� ��ũ��Ʈ�� ���� �̵����� �� ����Ѵ�.

// [Static]
// �������� �ʴ� ��ü
// ���̳��� Ÿ���� ������ �ִ� ĳ���Ϳ� �ε��� ����ƽ Ÿ���� ���� �������� �ʴ´�.
// ĳ���͸� ���θ��� �Ѿ����� ��

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

	// ��ġ�� �̵�
	void MovePosition(Vector2 dir);

	// Ư�� �������� ���� ����(���� �ۿ��� ����)
	void AddForce(Vector2 dir);

	void ResolveCollision(Rigidbody* otherRigidbody, Vector2 _normal);

	virtual void FixedUpdate() override;

	virtual void Update() override;

private:
	Transform* _transform;
	
	BODY_TYPE _bodyType;		// �ٵ� Ÿ��

	float _mass;				// ���� (������ ū ��ü�� ���� ��ü�� �浹�ϸ� ū ��ü�� ���� ������)

	float _linearDragX;			// ������ (������ ũ�� linearDrag�� ũ�� �� ������ �����δ� 0�̸� ��� ���ư�)

	float _linearDragY;

	float _gravityScale;		// �߷� ũ��(���� 1���ϸ� �⺻ �߷°��ӵ��� 9.8 m/s �� ����)

	Vector2 _gravity;			// �߷�(�⺻ 9.8m/s)

	Vector2 _position;			// ��ġ

	Vector2 _velocity;			// �ӵ�����

	Vector2 _acceleration;		// ���ӵ�����

	bool _isGravity;			// �߷� �ۿ��� �Ұ��� ������
};

