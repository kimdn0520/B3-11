#pragma once
#include "GameObject.h"

class TilePrefab : public GameObject
{
public:
	TilePrefab(string name, float posX, float posY, float width, float height);
	virtual ~TilePrefab();
};

