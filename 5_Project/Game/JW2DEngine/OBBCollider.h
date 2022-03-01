#pragma once
#include "ColliderBase.h"

class OBBCollider : public ColliderBase
{
public:
	OBBCollider(class GameObject* gameObject);
	~OBBCollider();

public:
	vector<Vector2> GetVertices() { return _vertices; }

	void SetWH(float width, float height)
	{
		_width = width;
		_initWidth = width;
		_height = height;
		_initHeight = height;
	}

	void SetRotation(float rotation) { _rotation = rotation; }

	virtual bool CheckCollision(ColliderBase* other) override;

	virtual void Update() override;

	virtual void FinalUpdate() override;

private:
	float _initWidth;
	float _initHeight;

	float _width;
	float _height;

	Vector2 _scale;

	float _rotation;

	Vector2 _lt;
	Vector2 _rt;
	Vector2 _rb;
	Vector2 _lb;

	vector<Vector2> _vertices;
};

