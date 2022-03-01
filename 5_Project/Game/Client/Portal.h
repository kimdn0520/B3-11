#pragma once
#include "MonoBehaviour.h"

class Portal : public MonoBehaviour
{
public:
	Portal(GameObject* gameObject);
	~Portal();
public:
	Vector2 nextPlayerPos;
};

