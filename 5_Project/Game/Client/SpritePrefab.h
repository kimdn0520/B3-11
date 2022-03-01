#pragma once
#include "GameObject.h"

class SpritePrefab : public GameObject
{
public:
	SpritePrefab(string spriteName, wstring filePath, float posX, float posY, float width = 128.f, float height = 128.f);
	virtual ~SpritePrefab();
};