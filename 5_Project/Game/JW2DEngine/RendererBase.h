#pragma once
#include "Component.h"

class RendererBase : public Component
{
public:
	RendererBase(GameObject* gameObject);
	virtual ~RendererBase();

public:
	virtual void FixedUpdate() {};

	virtual void Update() {};
};

