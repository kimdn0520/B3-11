#pragma once
#include "ColliderBase.h"

class CircleCollider : public ColliderBase
{
public:
	CircleCollider(class GameObject* gameObject);
	virtual ~CircleCollider();

private:
	bool _isTrigger;

	float _radius;

	float _initRadius;

public:

	float GetRadius() { return _radius; }

	void SetRadius(float radius) { _radius = radius; _initRadius = radius; }

	virtual bool CheckCollision(ColliderBase* other) override;

	virtual void Update() override;

	virtual void FinalUpdate() override;
};

 