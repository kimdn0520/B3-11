#pragma once
#include "GameObject.h"
#include "MapDataTable.h"

class MovableTilePrefab : public GameObject
{
public:
	MovableTilePrefab(string name, float posX, float posY, float width, float height);
	virtual ~MovableTilePrefab();
};

