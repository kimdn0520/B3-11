#pragma once
#include "MonoBehaviour.h"

class Panel;

class FadeOut : public MonoBehaviour
{
public:
	FadeOut(GameObject* gameObject);
	~FadeOut();

private:
	Panel* _panel;

private:

	virtual void FinalUpdate() override;
};

