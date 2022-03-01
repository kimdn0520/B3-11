#pragma once
#include "GameObject.h"

class BrokenWallPrefab : public GameObject
{
public:
	BrokenWallPrefab(string name, wstring filePath, float posX, float posY, float width, float height);
	virtual ~BrokenWallPrefab();

};

