#pragma once
#include "GameObject.h"

class SavePointPrefab :public GameObject
{
public:
	SavePointPrefab(string mapName, float posX, float posY, float width, float height, string savePointName);
	virtual ~SavePointPrefab();

public:
	string savePoint;
};

