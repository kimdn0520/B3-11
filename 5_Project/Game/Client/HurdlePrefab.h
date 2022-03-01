#pragma once
#include "GameObject.h"

class HurdlePrefab : public GameObject
{
public:
	HurdlePrefab(string name, string type, float posX, float posY, float width, float height, bool triger = true);
	virtual ~HurdlePrefab();
};

