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
	// _other 가 circle, box 둘 다 될 수 있기에..
	CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(other);
	BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(other);

	if (otherCircleCollider != nullptr)
	{
		float distance = sqrt(pow(_colMatrix.dx - other->GetColMatrix().dx, 2) +
			pow(_colMatrix.dy - other->GetColMatrix().dy, 2));

		// 내가 트리거일 경우
		if (_isTrigger)
		{
			// 충돌 체크
			if (distance <= (_radius + otherCircleCollider->GetRadius()))
			{
				return true;
			}
		}
		// 내가 트리거가 아닐 경우
		else
		{
			// 상대가 트리거일 경우
			if (otherCircleCollider->GetTrigger() == true)
			{
				// 충돌 체크
				if (distance <= (_radius + otherCircleCollider->GetRadius()))
				{
					return true;
				}
			}
			// 상대가 트리거가 아닐 경우
			else
			{
				if (distance <= (_radius + otherCircleCollider->GetRadius()))
				{
					Vector2 reflectVector = Vector2(_colMatrix.dx - other->GetColMatrix().dx, _colMatrix.dy - other->GetColMatrix().dy);
					Vector2 normalReflectVec = reflectVector.Normalized();
					Vector2 reflection = normalReflectVec * (_radius + otherCircleCollider->GetRadius() - distance);

					Rigidbody* otherRigidbody = other->GetRigidBody();

					// 두 원이 닿았다면 & 두 원이 가까워 지고 있는 상태였다면
					// 충격량을 구하여 속도 변화량을 구하고
					// 각각 두 원의 속도를 속도변화량 만큼 더 해 업데이트 한다.
					if (rigidbody != nullptr && otherRigidbody != nullptr)			// 둘다 강체인 경우
					{
						rigidbody->ResolveCollision(otherRigidbody, normalReflectVec);
					}
					else if (rigidbody != nullptr && otherRigidbody == nullptr)		// 내가 강체고 상대방은 아닌경우
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
		// TODO : 트리거일경우만 할거에용
		// 트리거일 경우    
		if (_isTrigger)
		{
			// 1. 보로노이 영역인지 아닌지 확인한다.
			// 2-1. 아니라면 반지름만큼 사각형을 확장하고 그 다음 원의 중심이 사각형안에 들어가있는지 확인한다.
			// 2-2. 맞다면 else 
			if ((_colMatrix.dx >= otherBoxCollider->GetVertices()[0].x && _colMatrix.dx <= otherBoxCollider->GetVertices()[2].x)
				|| (_colMatrix.dy >= otherBoxCollider->GetVertices()[0].y && _colMatrix.dy <= otherBoxCollider->GetVertices()[2].y))
			{
				if ((_colMatrix.dx > otherBoxCollider->GetVertices()[0].x - _radius && _colMatrix.dx < otherBoxCollider->GetVertices()[2].x + _radius)
					&& (_colMatrix.dy > otherBoxCollider->GetVertices()[0].y - _radius && _colMatrix.dy < otherBoxCollider->GetVertices()[2].y + _radius))
				{
					return true;
				}
			}
			// 2-2. 대각선쪽으로 왔을때 꼭지점들이 원 안에 있는지 확인
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
		// 트리거가 아닐 경우
		else
		{
			// 상대가 트리거일 경우
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
						Vector2 reflection = normalReflectVec;								// 해야합니다~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

						Rigidbody* otherRigidbody = other->GetRigidBody();

						if (rigidbody != nullptr && otherRigidbody != nullptr)			// 둘다 강체인 경우
						{
							rigidbody->ResolveCollision(otherRigidbody, normalReflectVec * 1.3f);
						}
						else if (rigidbody != nullptr && otherRigidbody == nullptr)		// 내가 강체고 상대방은 아닌경우
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

		// 콜라이더면 초록색 트리거면 빨간색 
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
