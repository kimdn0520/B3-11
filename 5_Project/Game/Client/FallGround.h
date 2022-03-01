#pragma once
#include "GameObject.h"

class FallGround : public GameObject
{
public:
	FallGround(string name, float posX, float posY, float width, float height);
	virtual ~FallGround();
};
