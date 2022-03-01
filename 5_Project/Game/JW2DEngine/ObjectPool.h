#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "SceneManager.h"
#include "Transform.h"

class ObjectPool
{	
	DECLARE_SINGLE(ObjectPool);

public:
    GameObject* SpawnFromPool(string name, Vector2 pos);

	void SpawnChildObject(GameObject* gameObject);

	void ReturnObject(GameObject* gameObj);

	void CreateNewObj(GameObject* prefab);

	void ResetObjectMapList() { objectMapList.clear(); };

public:
	map<string, queue<GameObject*>> objectMapList;
};
