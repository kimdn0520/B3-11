#pragma once
#include "RendererBase.h"

class GameObject;

class CircleRenderer : public RendererBase
{
public:
	CircleRenderer(GameObject* gameObject);
	virtual ~CircleRenderer();

private:
	float _radius;

public:
	void SetRaidus(float radius) { _radius = radius; }

	virtual void FinalUpdate() override;
};

