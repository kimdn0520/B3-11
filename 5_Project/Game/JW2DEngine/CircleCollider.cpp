#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "JW2DEngine.h"

CircleCollider::CircleCollider(GameObject* gameObject)
	: ColliderBase(gameObject),
	  _radius(1), _initRadius(1)
{
	_type = COMPONENT_TYPE::CIRCLE_COLLIDER;
	_radius = transform->GetWorldScale().x;

	transform->CalculateWorldMatrix();
	_colMatrix = transform->GetWorldMatrix();			
}

CircleCollider::~CircleCollider()
{}

bool CircleCollider::CheckCollision(ColliderBase* other)
{
	// _other �� circle, box �� �� �� �� �ֱ⿡..
	CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(other);
	BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(other);

	if (otherCircleCollider != nullptr)
	{
		float distance = sqrt(pow(_colMatrix.dx - other->GetColMatrix().dx, 2) +
			pow(_colMatrix.dy - other->GetColMatrix().dy, 2));

		// ���� Ʈ������ ���
		if (_isTrigger)
		{
			// �浹 üũ
			if (distance <= (_radius + otherCircleCollider->GetRadius()))
			{
				return true;
			}
		}
		// ���� Ʈ���Ű� �ƴ� ���
		else
		{
			// ��밡 Ʈ������ ���
			if (otherCircleCollider->GetTrigger() == true)
			{
				// �浹 üũ
				if (distance <= (_radius + otherCircleCollider->GetRadius()))
				{
					return true;
				}
			}
			// ��밡 Ʈ���Ű� �ƴ� ���
			else
			{
				if (distance <= (_radius + otherCircleCollider->GetRadius()))
				{
					Vector2 reflectVector = Vector2(_colMatrix.dx - other->GetColMatrix().dx, _colMatrix.dy - other->GetColMatrix().dy);
					Vector2 normalReflectVec = reflectVector.Normalized();
					Vector2 reflection = normalReflectVec * (_radius + otherCircleCollider->GetRadius() - distance);

					Rigidbody* otherRigidbody = other->GetRigidBody();

					// �� ���� ��Ҵٸ� & �� ���� ����� ���� �ִ� ���¿��ٸ�
					// ��ݷ��� ���Ͽ� �ӵ� ��ȭ���� ���ϰ�
					// ���� �� ���� �ӵ��� �ӵ���ȭ�� ��ŭ �� �� ������Ʈ �Ѵ�.
					if (rigidbody != nullptr && otherRigidbody != nullptr)			// �Ѵ� ��ü�� ���
					{
						rigidbody->ResolveCollision(otherRigidbody, normalReflectVec);
					}
					else if (rigidbody != nullptr && otherRigidbody == nullptr)		// ���� ��ü�� ������ �ƴѰ��
					{
						rigidbody->SetVelocity({ rigidbody->GetVelocity().x, 0 });

						transform->SetLocalPosition(transform->GetLocalPosition() + reflection);
					}

					return true;
				}
			}
		}
	}

	if (otherBoxCollider != nullptr)
	{
		// TODO : Ʈ�����ϰ�츸 �Ұſ���
		// Ʈ������ ���    
		if (_isTrigger)
		{
			// 1. ���γ��� �������� �ƴ��� Ȯ���Ѵ�.
			// 2-1. �ƴ϶�� ��������ŭ �簢���� Ȯ���ϰ� �� ���� ���� �߽��� �簢���ȿ� ���ִ��� Ȯ���Ѵ�.
			// 2-2. �´ٸ� else 
			if ((_colMatrix.dx >= otherBoxCollider->GetVertices()[0].x && _colMatrix.dx <= otherBoxCollider->GetVertices()[2].x)
				|| (_colMatrix.dy >= otherBoxCollider->GetVertices()[0].y && _colMatrix.dy <= otherBoxCollider->GetVertices()[2].y))
			{
				if ((_colMatrix.dx > otherBoxCollider->GetVertices()[0].x - _radius && _colMatrix.dx < otherBoxCollider->GetVertices()[2].x + _radius)
					&& (_colMatrix.dy > otherBoxCollider->GetVertices()[0].y - _radius && _colMatrix.dy < otherBoxCollider->GetVertices()[2].y + _radius))
				{
					return true;
				}
			}
			// 2-2. �밢�������� ������ ���������� �� �ȿ� �ִ��� Ȯ��
			else
			{
				float distance1 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[0].x), 2) +
					pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[0].y), 2));

				float distance2 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[1].x), 2) +
					pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[1].y), 2));

				float distance3 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[2].x), 2) +
					pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[2].y), 2));

				float distance4 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[3].x), 2) +
					pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[3].y), 2));

				if (distance1 <= _radius)
					return true;
				if (distance2 <= _radius)
					return true;
				if (distance3 <= _radius)
					return true;
				if (distance4 <= _radius)
					return true;
			}
		}
		// Ʈ���Ű� �ƴ� ���
		else
		{
			// ��밡 Ʈ������ ���
			if (otherBoxCollider->GetTrigger() == true)
			{
				if ((_colMatrix.dx >= otherBoxCollider->GetVertices()[0].x && _colMatrix.dx <= otherBoxCollider->GetVertices()[2].x)
					|| (_colMatrix.dy >= otherBoxCollider->GetVertices()[0].y && _colMatrix.dy <= otherBoxCollider->GetVertices()[2].y))
				{
					if ((_colMatrix.dx > otherBoxCollider->GetVertices()[0].x - _radius && _colMatrix.dx < otherBoxCollider->GetVertices()[2].x + _radius)
						&& (_colMatrix.dy > otherBoxCollider->GetVertices()[0].y - _radius && _colMatrix.dy < otherBoxCollider->GetVertices()[2].y + _radius))
					{
						return true;
					}
				}
				else
				{
					float distance1 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[0].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[0].y), 2));

					float distance2 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[1].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[1].y), 2));

					float distance3 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[2].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[2].y), 2));

					float distance4 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[3].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[3].y), 2));

					if (distance1 <= _radius)
						return true;
					if (distance2 <= _radius)
						return true;
					if (distance3 <= _radius)
						return true;
					if (distance4 <= _radius)
						return true;
				}
			}
			else
			{
				float distance = sqrt(pow(_colMatrix.dx - other->GetTransform()->GetWorldMatrix().dx, 2) +
					pow(_colMatrix.dy - other->GetTransform()->GetWorldMatrix().dy, 2));

				if ((_colMatrix.dx >= otherBoxCollider->GetVertices()[0].x && _colMatrix.dx <= otherBoxCollider->GetVertices()[2].x)
					|| (_colMatrix.dy >= otherBoxCollider->GetVertices()[0].y && _colMatrix.dy <= otherBoxCollider->GetVertices()[2].y))
				{
					if ((_colMatrix.dx > otherBoxCollider->GetVertices()[0].x - _radius && _colMatrix.dx < otherBoxCollider->GetVertices()[2].x + _radius)
						&& (_colMatrix.dy > otherBoxCollider->GetVertices()[0].y - _radius && _colMatrix.dy < otherBoxCollider->GetVertices()[2].y + _radius))
					{
						Vector2 reflectVector = position - other->GetPosition();
						Vector2 normalReflectVec = reflectVector.Normalized();
						// Vector2 reflection = normalReflectVec * (_radius + otherCircleCollider->GetRadius() - distance);
						Vector2 reflection = normalReflectVec;								// �ؾ��մϴ�~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

						Rigidbody* otherRigidbody = other->GetRigidBody();

						if (rigidbody != nullptr && otherRigidbody != nullptr)			// �Ѵ� ��ü�� ���
						{
							rigidbody->ResolveCollision(otherRigidbody, normalReflectVec * 1.3f);
						}
						else if (rigidbody != nullptr && otherRigidbody == nullptr)		// ���� ��ü�� ������ �ƴѰ��
						{
							rigidbody->SetVelocity({ rigidbody->GetVelocity().x, 0 });

							transform->SetLocalPosition(transform->GetLocalPosition() + reflection);
						}

						return true;
					}
				}
				else
				{
					float distance1 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[0].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[0].y), 2));

					float distance2 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[1].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[1].y), 2));

					float distance3 = sqrt(pow(_colMatrix.dx - (otherBoxCollider->GetVertices()[2].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[2].y), 2));

					float distance4 = sqrt(pow(position.x - (otherBoxCollider->GetVertices()[3].x), 2) +
						pow(_colMatrix.dy - (otherBoxCollider->GetVertices()[3].y), 2));

					if (distance1 <= _radius)
						return true;
					if (distance2 <= _radius)
						return true;
					if (distance3 <= _radius)
						return true;
					if (distance4 <= _radius)
						return true;
				}
			}
		}
	}

	return false;
}

void CircleCollider::Update()
{
	position.x = transform->GetWorldMatrix().dx;
	position.y = transform->GetWorldMatrix().dy;

	_colMatrix = transform->GetWorldMatrix();
	_colMatrix.dx += _colLocation.x;
	_colMatrix.dy += _colLocation.y;

	_radius = _initRadius * transform->GetWorldScale().x;
}

void CircleCollider::FinalUpdate()
{
	if(SCENE_MANAGER->isDebug)
	{ 
		GEngine->SetTransform(_colMatrix);

		// �ݶ��̴��� �ʷϻ� Ʈ���Ÿ� ������ 
		if (!_isTrigger)
			GEngine->SetBrushColor(0, 1, 0, 1);
		else
			GEngine->SetBrushColor(1, 0, 0, 1);

		GEngine->DrawCircleScreen(
			0,
			0,
			_initRadius);
	}
}
