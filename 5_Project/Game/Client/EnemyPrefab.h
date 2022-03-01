#pragma once
#include "GameObject.h"

class EnemyPrefab : public GameObject
{
public:
	EnemyPrefab(string name,Vector2 pos, float width,float height);
	virtual ~EnemyPrefab();
};

