#pragma once
#include "MonoBehaviour.h"

class Text;

class TestTxt : public MonoBehaviour
{
public:
	TestTxt(GameObject* gameObject);
	~TestTxt();

private:
	Text* txt;

	virtual void Update();
};

