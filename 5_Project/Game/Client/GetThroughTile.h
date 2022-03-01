#pragma once
#include "MonoBehaviour.h"

class GameObject;

class GetThroughTile : public MonoBehaviour
{
public:
	GetThroughTile(GameObject* gameObject);
	~GetThroughTile();

private:
	GameObject* _gameObject;
	BoxCollider* _boxCollider;

	virtual void OnCollisionExit(ColliderBase* col) override;
	virtual void OnTriggerEnter(ColliderBase* col) override;
};



