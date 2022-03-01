#pragma once
#include "Component.h"

class Text : public Component
{
public:
	Text(GameObject* gameObject);
	~Text();

public:
	string text;
	// const char* text;

public:
	void SetStride(Vector2 stride) { this->stride = stride; }

	void SetWidth(int width) { _width = width; }
	
	void SetHeight(int height) { _height = height; }

	void SetRotate(float rotation) { _rotation = rotation; }

	virtual void FinalUpdate() override;
private:
	Transform* _textTransform;

	Transform* _transform;

	int _width;

	int _height;

	float _rotation;

	Vector2 stride;
};

