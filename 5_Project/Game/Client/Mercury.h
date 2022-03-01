#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;

class Mercury : public MonoBehaviour
{
public:
	Mercury(GameObject* gameObject);
	~Mercury();

private:
	Transform* _transform;

private:
	virtual void Update();
};

