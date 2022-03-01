#pragma once
#include "GameObject.h"

class PortalPrefab :public GameObject
{
public:
	PortalPrefab(string connectMapName, Vector2 pos, float width, float height, Vector2 playerPos);
	virtual ~PortalPrefab();

public:
	Vector2 nextPlayerPos;
};

