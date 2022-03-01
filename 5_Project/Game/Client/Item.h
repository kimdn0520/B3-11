#pragma once
#include "MonoBehaviour.h"


class Item : public MonoBehaviour
{
public:
	Item(GameObject* gameObject);
	~Item();

private:
	virtual void OnTriggerEnter(ColliderBase* collider) override;

};

