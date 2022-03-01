#pragma once
#include "GameObject.h"

class ItemPrefab : public GameObject
{
public:
	ItemPrefab(string name, Vector2 pos, float radius, bool trigger);
	virtual ~ItemPrefab();
};


