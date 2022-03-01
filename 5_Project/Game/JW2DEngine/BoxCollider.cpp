#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "OBBCollider.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "JW2DEngine.h"
#include "Rigidbody.h"
#include "GameObject.h"

BoxCollider::BoxCollider(GameObject* gameObject)
	: ColliderBase(gameObject),
	  _width(1.f), _height(1.f), _initWidth(1.f), _initHeight(1.f)
{
	_type = COMPONENT_TYPE::BOX_COLLIDER;

	transform->CalculateWorldMatrix();
	
	_scale = transform->GetWorldScale();			// ���� Ʈ�������� �������� �����´�.
	
	// _colMatrix = transform->GetWorldMatrix();
	
	_width = _width * _scale.x;
	_height = _height * _scale.y;

	_lt = Vector2(transform->GetWorldMatrix().dx - (_width / 2), transform->GetWorldMatrix().dy - (_height / 2));
	_rt = Vector2(transform->GetWorldMatrix().dx + (_width / 2), transform->GetWorldMatrix().dy - (_height / 2));
	_rb = Vector2(transform->GetWorldMatrix().dx + (_width / 2), transform->GetWorldMatrix().dy + (_height / 2));
	_lb = Vector2(transform->GetWorldMatrix().dx - (_width / 2), transform->GetWorldMatrix().dy + (_height / 2));


	_vertices.clear();

	_vertices.push_back(_lt);
	_vertices.push_back(_rt);
	_vertices.push_back(_rb);
	_vertices.push_back(_lb);

	if(rigidbody != nullptr)
		velocityVec = { rigidbody->GetVelocity().x, rigidbody->GetVelocity().y };

	transform->CalculateWorldMatrix();
}

BoxCollider::~BoxCollider()
{}

bool BoxCollider::CheckCollision(ColliderBase * other)
{
	// _other �� circle, box, Obb �� �� �� �� �ֱ⿡..
	ColliderBase* otherCollider = other;
	
	if (other->GetType() == COMPONENT_TYPE::BOX_COLLIDER)
	{
		BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(other);

		// ���� Ʈ������ ���
		if (_isTrigger)
		{
			if ((abs(position.x - otherBoxCollider->position.x) < _width / 2 + otherBoxCollider->_width / 2) &&
				(abs(position.y - otherBoxCollider->position.y) < _height / 2 + otherBoxCollider->_height / 2))
			{
				return true;
			}
		}
		// ���� Ʈ���Ű� �ƴ� ���
		else
		{
			// ��밡 Ʈ������ ���
			if (otherBoxCollider->GetTrigger() == true)
			{
				if ((abs(position.x - otherBoxCollider->position.x) < _width / 2 + otherBoxCollider->_width / 2) &&
					(abs(position.y - otherBoxCollider->position.y) < _height / 2 + otherBoxCollider->_height / 2))
				{
					return true;
				}
			}
			// ��뵵 Ʈ���Ű� �ƴ� ���
			else
			{
				// �浹������..
				if ((abs(position.x - otherBoxCollider->position.x) <= _width / 2 + otherBoxCollider->_width / 2) &&
					(abs(position.y - otherBoxCollider->position.y) <= _height / 2 + otherBoxCollider->_height / 2))
				{
					// �Ѵ� ��ü�� ��� notAffectTag�� �Ⱥε����� �Ҷ��ߴµ� �����ӵ�� �������� �׳� �����浹�� ���ϴ������� �����غ��Ҵ�
					if (rigidbody != nullptr && other->GetRigidBody() != nullptr)
					{
						// rigidbody->ResolveCollision(other->GetRigidBody(), (position - other->GetPosition()).Normalized() * 1.3f);
					}
					// ���� ��ü�� ������ �ƴѰ�� ���⸦ ��� �� ¥������������~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					else if (rigidbody != nullptr && other->GetRigidBody() == nullptr)
					{
						// üũ�� �Ǹ�.. ���� �Ϸ���..
						_isCheck = true;

						if (_vertices[0].x <= otherBoxCollider->GetVertices()[0].x && _vertices[2].y <= otherBoxCollider->GetVertices()[2].y)
						{
							// x : myRight - otLeft       y : myBottom - otTop
							float xDepth = _vertices[1].x - otherBoxCollider->GetVertices()[0].x;
							float yDepth = _vertices[2].y - otherBoxCollider->GetVertices()[0].y;

							if (xDepth >= yDepth)
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::DOWN) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { 0, -yDepth };
									info->compNum = xDepth;
									info->velocityVec = { rigidbody->GetVelocity().x, 0 };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::DOWN;

									_reflMap[(int)COL_DIR::DOWN] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::DOWN]->compNum < xDepth)
									{
										_reflMap[(int)COL_DIR::DOWN]->compNum = xDepth;
										_reflMap[(int)COL_DIR::DOWN]->reflectVec = { 0, -yDepth };
										_reflMap[(int)COL_DIR::DOWN]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::DOWN]->velocityVec = { rigidbody->GetVelocity().x, 0 };
										_reflMap[(int)COL_DIR::DOWN]->colDir = (int)COL_DIR::DOWN;
									}
								}
							}
							else
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::RIGHT) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { -xDepth, 0 };
									info->compNum = yDepth;
									info->velocityVec = { 0, rigidbody->GetVelocity().y };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::RIGHT;

									_reflMap[(int)COL_DIR::RIGHT] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::RIGHT]->compNum < yDepth)
									{
										_reflMap[(int)COL_DIR::RIGHT]->compNum = yDepth;
										_reflMap[(int)COL_DIR::RIGHT]->reflectVec = { -xDepth, 0 };
										_reflMap[(int)COL_DIR::RIGHT]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::RIGHT]->velocityVec = { 0, rigidbody->GetVelocity().y };
										_reflMap[(int)COL_DIR::RIGHT]->colDir = (int)COL_DIR::RIGHT;
									}
								}
							}
						}
						else if (_vertices[0].x > otherBoxCollider->GetVertices()[0].x && _vertices[2].y <= otherBoxCollider->GetVertices()[2].y)
						{
							// x : otRight - myLeft       y : myBottom - otTop
							float xDepth = otherBoxCollider->GetVertices()[1].x - _vertices[0].x;
							float yDepth = _vertices[2].y - otherBoxCollider->GetVertices()[0].y;

							if (xDepth >= yDepth)
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::DOWN) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { 0, -yDepth };
									info->compNum = xDepth;
									info->velocityVec = { rigidbody->GetVelocity().x, 0 };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::DOWN;

									_reflMap[(int)COL_DIR::DOWN] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::DOWN]->compNum < xDepth)
									{
										_reflMap[(int)COL_DIR::DOWN]->compNum = xDepth;
										_reflMap[(int)COL_DIR::DOWN]->reflectVec = { 0, -yDepth };
										_reflMap[(int)COL_DIR::DOWN]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::DOWN]->velocityVec = { rigidbody->GetVelocity().x, 0 };
										_reflMap[(int)COL_DIR::DOWN]->colDir = (int)COL_DIR::DOWN;
									}
								}
							}
							else
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::LEFT) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { xDepth, 0 };
									info->compNum = yDepth;
									info->velocityVec = { 0, rigidbody->GetVelocity().y };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::LEFT;

									_reflMap[(int)COL_DIR::LEFT] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::LEFT]->compNum < yDepth)
									{
										_reflMap[(int)COL_DIR::LEFT]->compNum = yDepth;
										_reflMap[(int)COL_DIR::LEFT]->reflectVec = { xDepth, 0 };
										_reflMap[(int)COL_DIR::LEFT]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::LEFT]->velocityVec = { 0, rigidbody->GetVelocity().y };
										_reflMap[(int)COL_DIR::LEFT]->colDir = (int)COL_DIR::LEFT;
									}
								}
							}
						}
						else if (_vertices[0].x <= otherBoxCollider->GetVertices()[0].x && _vertices[2].y > otherBoxCollider->GetVertices()[2].y)
						{
							// x : myRight - otLeft       y : otBottom - myTop
							float xDepth = _vertices[1].x - otherBoxCollider->GetVertices()[0].x;
							float yDepth = otherBoxCollider->GetVertices()[2].y - _vertices[0].y;

							if (xDepth >= yDepth)
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::UP) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { 0, yDepth };
									info->compNum = xDepth;
									info->velocityVec = { rigidbody->GetVelocity().x, 0 };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::UP;

									_reflMap[(int)COL_DIR::UP] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::UP]->compNum < xDepth)
									{
										_reflMap[(int)COL_DIR::UP]->compNum = xDepth;
										_reflMap[(int)COL_DIR::UP]->reflectVec = { 0, yDepth };
										_reflMap[(int)COL_DIR::UP]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::UP]->velocityVec = { rigidbody->GetVelocity().x, 0 };
										_reflMap[(int)COL_DIR::UP]->colDir = (int)COL_DIR::UP;
									}
								}
							}
							else
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::RIGHT) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { -xDepth, 0 };
									info->compNum = yDepth;
									info->velocityVec = { 0, rigidbody->GetVelocity().y };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::RIGHT;

									_reflMap[(int)COL_DIR::RIGHT] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::RIGHT]->compNum < yDepth)
									{
										_reflMap[(int)COL_DIR::RIGHT]->compNum = yDepth;
										_reflMap[(int)COL_DIR::RIGHT]->reflectVec = { -xDepth, 0 };
										_reflMap[(int)COL_DIR::RIGHT]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::RIGHT]->velocityVec = { 0, rigidbody->GetVelocity().y };
										_reflMap[(int)COL_DIR::RIGHT]->colDir = (int)COL_DIR::RIGHT;
									}
								}
							}
						}
						else if (_vertices[0].x > otherBoxCollider->GetVertices()[0].x && _vertices[2].y > otherBoxCollider->GetVertices()[2].y)
						{
							// x : otRight - myLeft       y : otBottom - myTop
							float xDepth = otherBoxCollider->GetVertices()[1].x - _vertices[0].x;
							float yDepth = otherBoxCollider->GetVertices()[2].y - _vertices[0].y;

							if (xDepth >= yDepth)
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::UP) == _reflMap.end()) 
								{
									Info* info = new Info();
									info->reflectVec = { 0, yDepth };
									info->compNum = xDepth;
									info->velocityVec = { rigidbody->GetVelocity().x, 0 };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::UP;

									_reflMap[(int)COL_DIR::UP] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::UP]->compNum < xDepth)
									{
										_reflMap[(int)COL_DIR::UP]->compNum = xDepth;
										_reflMap[(int)COL_DIR::UP]->reflectVec = { 0, yDepth };
										_reflMap[(int)COL_DIR::UP]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::UP]->velocityVec = { rigidbody->GetVelocity().x, 0 };
										_reflMap[(int)COL_DIR::UP]->colDir = (int)COL_DIR::UP;
									}
								}
							}
							else
							{
								// ������ �ְ�
								if (_reflMap.find((int)COL_DIR::LEFT) == _reflMap.end())
								{
									Info* info = new Info();
									info->reflectVec = { xDepth, 0 };
									info->compNum = yDepth;
									info->velocityVec = { 0, rigidbody->GetVelocity().y };
									info->otherCol = otherBoxCollider;
									info->colDir = (int)COL_DIR::LEFT;

									_reflMap[(int)COL_DIR::LEFT] = info;
								}
								// ������ ���ؼ� �ִ´�.
								else
								{
									// ���ݰ��� ��ũ�� �������ش�.
									if (_reflMap[(int)COL_DIR::LEFT]->compNum < yDepth)
									{
										_reflMap[(int)COL_DIR::LEFT]->compNum = yDepth;
										_reflMap[(int)COL_DIR::LEFT]->reflectVec = { xDepth, 0 };
										_reflMap[(int)COL_DIR::LEFT]->otherCol = otherBoxCollider;
										_reflMap[(int)COL_DIR::LEFT]->velocityVec = { 0, rigidbody->GetVelocity().y };
										_reflMap[(int)COL_DIR::LEFT]->colDir = (int)COL_DIR::LEFT;
									}
								}
							}
						}
						Update();
					}

					return true;
				}
			}
		}
	}

	if (other->GetType() == COMPONENT_TYPE::CIRCLE_COLLIDER)
	{
		CircleCollider* otherCircleCollider = dynamic_cast<CircleCollider*>(other);

		otherCircleCollider->GetColMatrix();
		
		// TODO : Ʈ������ ��츸 �Ұſ���
		// ���� Ʈ������ ���
		if (_isTrigger)
		{
			// 1. ���γ��� �������� �ƴ��� Ȯ���Ѵ�.
			// 2-1. �ƴ϶�� ��������ŭ �簢���� Ȯ���ϰ� �� ���� ���� �߽��� �簢���ȿ� ���ִ��� Ȯ���Ѵ�.
			// 2-2. �´ٸ� else 

			if ((otherCircleCollider->GetColMatrix().dx >= _vertices[0].x && otherCircleCollider->GetColMatrix().dx <= _vertices[2].x)
				|| (otherCircleCollider->GetColMatrix().dy >= _vertices[0].y && otherCircleCollider->GetColMatrix().dy <= _vertices[2].y))
			{
				if ((otherCircleCollider->GetColMatrix().dx > _vertices[0].x - otherCircleCollider->GetRadius() && otherCircleCollider->GetColMatrix().dx < _vertices[2].x + otherCircleCollider->GetRadius())
					&& (otherCircleCollider->GetColMatrix().dy > _vertices[0].y - otherCircleCollider->GetRadius() && otherCircleCollider->GetColMatrix().dy < _vertices[2].y + otherCircleCollider->GetRadius()))
				{
					return true;
				}
			}
			else
			{
				// 2-2. �밢�������� ������ ���������� �� �ȿ� �ִ��� Ȯ��
				float distance1 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[0].x, 2) +
					pow(otherCircleCollider->GetColMatrix().dy - _vertices[0].y, 2));

				float distance2 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[1].x, 2) +
					pow(otherCircleCollider->GetColMatrix().dy - _vertices[1].y, 2));

				float distance3 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[2].x, 2) +
					pow(otherCircleCollider->GetColMatrix().dy - _vertices[2].y, 2));

				float distance4 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[3].x, 2) +
					pow(otherCircleCollider->GetColMatrix().dy - _vertices[3].y, 2));

				if (distance1 <= otherCircleCollider->GetRadius())
					return true;
				if (distance2 <= otherCircleCollider->GetRadius())
					return true;
				if (distance3 <= otherCircleCollider->GetRadius())
					return true;
				if (distance4 <= otherCircleCollider->GetRadius())
					return true;
			}
		}
		// Ʈ���Ű� �ƴ� ���
		else
		{
			// ��밡 Ʈ������ ���
			if (otherCircleCollider->GetTrigger() == true)
			{
				// 1. ���γ��� �������� �ƴ��� Ȯ���Ѵ�.
				// 2-1. �ƴ϶�� ��������ŭ �簢���� Ȯ���ϰ� �� ���� ���� �߽��� �簢���ȿ� ���ִ��� Ȯ���Ѵ�.
				// 2-2. �´ٸ� else 
				if ((otherCircleCollider->GetColMatrix().dx >= _vertices[0].x && otherCircleCollider->GetColMatrix().dx <= _vertices[2].x)
					|| (otherCircleCollider->GetColMatrix().dy >= _vertices[0].y && otherCircleCollider->GetColMatrix().dy <= _vertices[2].y))
				{
					if ((otherCircleCollider->GetColMatrix().dx > _vertices[0].x - otherCircleCollider->GetRadius() && otherCircleCollider->GetColMatrix().dx < _vertices[2].x + otherCircleCollider->GetRadius())
						&& (otherCircleCollider->GetColMatrix().dy > _vertices[0].y - otherCircleCollider->GetRadius() && otherCircleCollider->GetColMatrix().dy < _vertices[2].y + otherCircleCollider->GetRadius()))
					{
						return true;
					}
				}
				else
				{
					// 2-2. �밢�������� ������ ���������� �� �ȿ� �ִ��� Ȯ��
					float distance1 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[0].x, 2) +
						pow(otherCircleCollider->GetColMatrix().dy - _vertices[0].y, 2));

					float distance2 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[1].x, 2) +
						pow(otherCircleCollider->GetColMatrix().dy - _vertices[1].y, 2));

					float distance3 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[2].x, 2) +
						pow(otherCircleCollider->GetColMatrix().dy - _vertices[2].y, 2));

					float distance4 = sqrt(pow(otherCircleCollider->GetColMatrix().dx - _vertices[3].x, 2) +
						pow(otherCircleCollider->GetColMatrix().dy - _vertices[3].y, 2));

					if (distance1 <= otherCircleCollider->GetRadius())
						return true;
					if (distance2 <= otherCircleCollider->GetRadius())
						return true;
					if (distance3 <= otherCircleCollider->GetRadius())
						return true;
					if (distance4 <= otherCircleCollider->GetRadius())
						return true;
				}
			}
			// ��뵵 Ʈ���Ű� �ƴҰ�� �ڵ�� ¥���� �ʾҴ�..
			else
			{
				return false;
			}
		}
	}

	if (other->GetType() == COMPONENT_TYPE::OBB_COLLIDER)
	{
		OBBCollider* otherOBBCollider = dynamic_cast<OBBCollider*>(other);

		// ���� Ʈ������ ���
		if (_isTrigger)
		{
			vector<Vector2> edge;
			edge.push_back(Vector2(_vertices[1].x - _vertices[0].x, _vertices[1].y - _vertices[0].y));
			edge.push_back(Vector2(_vertices[2].x - _vertices[1].x, _vertices[2].y - _vertices[1].y));
			edge.push_back(Vector2(otherOBBCollider->GetVertices()[1].x - otherOBBCollider->GetVertices()[0].x, otherOBBCollider->GetVertices()[1].y - otherOBBCollider->GetVertices()[0].y));
			edge.push_back(Vector2(otherOBBCollider->GetVertices()[2].x - otherOBBCollider->GetVertices()[1].x, otherOBBCollider->GetVertices()[2].y - otherOBBCollider->GetVertices()[1].y));

			float this_min = 100000000;
			float this_max = -100000000;
			float other_min = 100000000;
			float other_max = -100000000;

			for (int i = 0; i < 4; i++)
			{
				this_min = 100000000;
				this_max = -100000000;
				other_min = 100000000;
				other_max = -100000000;

				for (int j = 0; j < _vertices.size(); j++)
				{
					this_min = min(this_min, _vertices[j].Dot(_vertices[j], edge[i]));
					this_max = max(this_max, _vertices[j].Dot(_vertices[j], edge[i]));

					other_min = min(other_min, otherOBBCollider->GetVertices()[j].Dot(otherOBBCollider->GetVertices()[j], edge[i]));
					other_max = max(other_max, otherOBBCollider->GetVertices()[j].Dot(otherOBBCollider->GetVertices()[j], edge[i]));
				}

				if ((this_min < other_max && other_min < this_max) == false)
				{
					return false;
				}
			}

			return true;
		}
		// ���� Ʈ���Ű� �ƴ� ���
		else
		{
			// ��밡 Ʈ������ ���
			if (otherOBBCollider->GetTrigger() == true)
			{
				vector<Vector2> edge;
				edge.push_back(Vector2(_vertices[1].x - _vertices[0].x, _vertices[1].y - _vertices[0].y));
				edge.push_back(Vector2(_vertices[2].x - _vertices[1].x, _vertices[2].y - _vertices[1].y));
				edge.push_back(Vector2(otherOBBCollider->GetVertices()[1].x - otherOBBCollider->GetVertices()[0].x, otherOBBCollider->GetVertices()[1].y - otherOBBCollider->GetVertices()[0].y));
				edge.push_back(Vector2(otherOBBCollider->GetVertices()[2].x - otherOBBCollider->GetVertices()[1].x, otherOBBCollider->GetVertices()[2].y - otherOBBCollider->GetVertices()[1].y));

				float this_min = 100000000;
				float this_max = -100000000;
				float other_min = 100000000;
				float other_max = -100000000;

				for (int i = 0; i < 4; i++)
				{
					this_min = 100000000;
					this_max = -100000000;
					other_min = 100000000;
					other_max = -100000000;

					for (int j = 0; j < _vertices.size(); j++)
					{
						this_min = min(this_min, _vertices[j].Dot(_vertices[j], edge[i]));
						this_max = max(this_max, _vertices[j].Dot(_vertices[j], edge[i]));

						other_min = min(other_min, otherOBBCollider->GetVertices()[j].Dot(otherOBBCollider->GetVertices()[j], edge[i]));
						other_max = max(other_max, otherOBBCollider->GetVertices()[j].Dot(otherOBBCollider->GetVertices()[j], edge[i]));
					}

					if ((this_min < other_max) && (other_min < this_max))
					{
						continue;
					}
					else
					{
						return false;
					}
				}

				return true;
			}
			// ��뵵 Ʈ���Ű� �ƴ� ���
			else
			{
				// nob,,
			}
		}
	}

	return false;
}

void BoxCollider::Update()
{	
	// ������Ʈ Ʈ������ ���¿� �����ϰ� ���ش�.
	position.x = transform->GetWorldMatrix().dx;
	position.y = transform->GetWorldMatrix().dy;
	_scale = transform->GetWorldScale();

	//// �ݶ��̴� ��Ʈ������ �Ѱ��ش�.
	//_colMatrix = transform->GetWorldMatrix();
	//_colMatrix.dx += _colLocation.x;
	//_colMatrix.dy += _colLocation.y;

	_width = _initWidth * _scale.x;
	_height = _initHeight * _scale.y;

	_lt = Vector2(position.x - (_width / 2), position.y - (_height / 2));
	_rt = Vector2(position.x + (_width / 2), position.y - (_height / 2));
	_rb = Vector2(position.x + (_width / 2), position.y + (_height / 2));
	_lb = Vector2(position.x - (_width / 2), position.y + (_height / 2));

	_vertices.clear();

	_vertices.push_back(_lt);
	_vertices.push_back(_rt);
	_vertices.push_back(_rb);
	_vertices.push_back(_lb);

	transform->CalculateWorldMatrix();
}

void BoxCollider::FinalUpdate()
{
	if(SCENE_MANAGER->isDebug)
	{ 
		GEngine->SetTransform(transform->GetWorldMatrix());

		if (!_isTrigger)
			GEngine->SetBrushColor(0, 1, 0, 1);
		else
			GEngine->SetBrushColor(1, 0, 0, 1);

		GEngine->DrawRectScreen(
			-(_initWidth / 2),
			-(_initHeight / 2),
			(_initWidth / 2),
			(_initHeight / 2));
	}
}
