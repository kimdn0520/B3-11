#pragma once
#include "GameObject.h"

class BossPrefab : public GameObject
{
public:
	BossPrefab(Vector2 pos, float radius);
	virtual ~BossPrefab();
};
