#pragma once
#include "Component.h"

class ColliderBase;

class MonoBehaviour : public Component
{
public:
	MonoBehaviour(GameObject* gameObject);
	virtual ~MonoBehaviour();

public:
	void Instantiate(GameObject* prefab, Vector2 pos);
	void Destroy(GameObject* gameObject, float destroyTime = 0.f);

	virtual void PreProcess() {};

	virtual void OnCollisionEnter(ColliderBase* col) {};
	virtual void OnCollisionStay(ColliderBase* col) {};
	virtual void OnCollisionExit(ColliderBase* col) {};

	virtual void OnTriggerEnter(ColliderBase* col) {};
	virtual void OnTriggerStay(ColliderBase* col) {};
	virtual void OnTriggerExit(ColliderBase* col) {};
};

