#pragma once

class GameObject;

class Prefabs
{
	DECLARE_SINGLE(Prefabs);

private:
	map<int, GameObject*> _prefabsMap;

public:
	void Init();

	map<int, GameObject*> GetPrefabsData() { return _prefabsMap; }

	GameObject* BulletPrefab();
	GameObject* GroundSpritePrefab_1();
};

