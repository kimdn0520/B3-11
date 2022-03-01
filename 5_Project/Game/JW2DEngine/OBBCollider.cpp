#include "pch.h"
#include "OBBCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "JW2DEngine.h"

OBBCollider::OBBCollider(GameObject* gameObject)
	: ColliderBase(gameObject),
	_width(1.f), _height(1.f), _initWidth(1.f), _initHeight(1.f), _rotation(0.f)
{
	_type = COMPONENT_TYPE::OBB_COLLIDER;

	transform->CalculateWorldMatrix();

	_scale = transform->GetWorldScale();			// ���� Ʈ�������� �������� �����´�.

	_colMatrix = transform->GetWorldMatrix();

	_width = _width * _scale.x;
	_height = _height * _scale.y;

	// 180 degree = �� radian
	// 1 degree = �� / 180 radian
	// x degree = x * �� / 180 radian
	// ��ǻ������ ����� �ѱ涧�� radian���� �ٲ㼭 �ѱ��.
	float radian = _rotation * (3.141592f / 180.f);

	// �� ���� �� �ϳ� ���Ҷ��� pos + w/2 + h/2 �̷����ؼ� ���ϴµ�
	// ������ ���� ���� w/2 * cos��  �̷������� ���ָ� �ȴ�

	_lt = Vector2(_colMatrix.dx - (cos(radian) * _width / 2) + (sin(radian) * _height / 2),
				  _colMatrix.dy - (cos(radian) * _height / 2) - (sin(radian) * _width / 2));
	_rt = Vector2(_colMatrix.dx + (cos(radian) * _width / 2) - (sin(radian) * _height / 2),
				  _colMatrix.dy - (cos(radian) * _height / 2) + (sin(radian) * _width / 2));
	_rb = Vector2(_colMatrix.dx + (cos(radian) * _width / 2) + (sin(radian) * _height / 2),
				  _colMatrix.dy + (cos(radian) * _height / 2) - (sin(radian) * _width / 2));
	_lb = Vector2(_colMatrix.dx - (cos(radian) * _width / 2) - (sin(radian) * _height / 2),
				  _colMatrix.dy + (cos(radian) * _height / 2) + (sin(radian) * _width / 2));

	_vertices.clear();

	_vertices.push_back(_lt);
	_vertices.push_back(_rt);
	_vertices.push_back(_rb);
	_vertices.push_back(_lb);
}

OBBCollider::~OBBCollider()
{}

/// <summary>
///	OBB�� BOX �� �Ұ���, �浹üũ�� �Ұ���(Ʈ���ſ�)
/// </summary>
bool OBBCollider::CheckCollision(ColliderBase* other)
{
	BoxCollider* otherBoxCollider = dynamic_cast<BoxCollider*>(other);

	if (otherBoxCollider != nullptr)
	{
		// ���� Ʈ������ ���
		if (_isTrigger)
		{
			vector<Vector2> edge;
			edge.push_back(Vector2(_vertices[1].x - _vertices[0].x, _vertices[1].y - _vertices[0].y ));
			edge.push_back(Vector2(_vertices[2].x - _vertices[1].x, _vertices[2].y - _vertices[1].y));
			edge.push_back(Vector2(otherBoxCollider->GetVertices()[1].x - otherBoxCollider->GetVertices()[0].x, otherBoxCollider->GetVertices()[1].y - otherBoxCollider->GetVertices()[0].y));
			edge.push_back(Vector2(otherBoxCollider->GetVertices()[2].x - otherBoxCollider->GetVertices()[1].x, otherBoxCollider->GetVertices()[2].y - otherBoxCollider->GetVertices()[1].y));

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

					other_min = min(other_min, otherBoxCollider->GetVertices()[j].Dot(otherBoxCollider->GetVertices()[j], edge[i]));
					other_max = max(other_max, otherBoxCollider->GetVertices()[j].Dot(otherBoxCollider->GetVertices()[j], edge[i]));
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
			if (otherBoxCollider->GetTrigger() == true)
			{
				vector<Vector2> edge;
				edge.push_back(Vector2(_vertices[1].x - _vertices[0].x, _vertices[1].y - _vertices[0].y));
				edge.push_back(Vector2(_vertices[2].x - _vertices[1].x, _vertices[2].y - _vertices[1].y));
				edge.push_back(Vector2(otherBoxCollider->GetVertices()[1].x - otherBoxCollider->GetVertices()[0].x, otherBoxCollider->GetVertices()[1].y - otherBoxCollider->GetVertices()[0].y));
				edge.push_back(Vector2(otherBoxCollider->GetVertices()[2].x - otherBoxCollider->GetVertices()[1].x, otherBoxCollider->GetVertices()[2].y - otherBoxCollider->GetVertices()[1].y));

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

						other_min = min(other_min, otherBoxCollider->GetVertices()[j].Dot(otherBoxCollider->GetVertices()[j], edge[i]));
						other_max = max(other_max, otherBoxCollider->GetVertices()[j].Dot(otherBoxCollider->GetVertices()[j], edge[i]));
					}

					if ((this_min < other_max && other_min < this_max) == false)
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

void OBBCollider::Update()
{
	// ������Ʈ Ʈ������ ���¿� �����ϰ� ���ش�.
	position.x = transform->GetWorldMatrix().dx;
	position.y = transform->GetWorldMatrix().dy;
	_scale = transform->GetWorldScale();

	// �ݶ��̴� ��Ʈ������ �Ѱ��ش�.
	_colMatrix = transform->GetWorldMatrix();
	_colMatrix.dx += _colLocation.x;
	_colMatrix.dy += _colLocation.y;

	_width = _initWidth * _scale.x;
	_height = _initHeight * _scale.y;

	// 180 degree = �� radian
	// 1 degree = �� / 180 radian
	// x degree = x * �� / 180 radian
	// ��ǻ������ ����� �ѱ涧�� radian���� �ٲ㼭 �ѱ��.
	float radian = _rotation * (3.141592f / 180.f);

	// �� ���� �� �ϳ� ���Ҷ��� pos + w/2 + h/2 �̷����ؼ� ���ϴµ�
	// ������ ���� ���� w/2 * cos��  �̷������� ���ָ� �ȴ�

	_lt = Vector2(_colMatrix.dx - (cos(radian) * _width / 2) + (sin(radian) * _height / 2),
		_colMatrix.dy - (cos(radian) * _height / 2) - (sin(radian) * _width / 2));
	_rt = Vector2(_colMatrix.dx + (cos(radian) * _width / 2) - (sin(radian) * _height / 2),
		_colMatrix.dy - (cos(radian) * _height / 2) + (sin(radian) * _width / 2));
	_rb = Vector2(_colMatrix.dx + (cos(radian) * _width / 2) + (sin(radian) * _height / 2),
		_colMatrix.dy + (cos(radian) * _height / 2) - (sin(radian) * _width / 2));
	_lb = Vector2(_colMatrix.dx - (cos(radian) * _width / 2) - (sin(radian) * _height / 2),
		_colMatrix.dy + (cos(radian) * _height / 2) + (sin(radian) * _width / 2));

	_vertices.clear();

	_vertices.push_back(_lt);
	_vertices.push_back(_rt);
	_vertices.push_back(_rb);
	_vertices.push_back(_lb);
}

void OBBCollider::FinalUpdate()
{
	if (_isDrawCol)
	{
		GEngine->SetTransform(_colMatrix);

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
