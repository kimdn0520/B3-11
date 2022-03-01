#pragma once
#include "GameObject.h"

class CameraPrefab : public GameObject
{
public:
	CameraPrefab(float width, float height, bool setTrigger, bool setCamerraView);
	virtual ~CameraPrefab();
};

