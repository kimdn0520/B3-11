#pragma once
#include "RendererBase.h"

class GameObject;

class BoxRenderer : public RendererBase
{
public:
	BoxRenderer(GameObject* gameObject);
	virtual ~BoxRenderer();

private:
	float _width;
	float _height;

public:
	void SetWH(float width, float height) { _width = width; _height = height; }

	virtual void FinalUpdate() override;

};

