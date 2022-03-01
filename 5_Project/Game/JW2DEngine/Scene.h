#pragma once

class GameObject;

class Scene
{
public:
	virtual void Init() {};

	void Awake();

	void PreProcess();
	void FixedUpdate();
	void Update();			// virtual �ؼ� ���� �����ұ�?
	void LateUpdate();
	void FinalUpdate();

public:
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
	void AllClearGameObject();

	void Debug_FPS();

	vector<GameObject*> GetGameObjects() { return _gameObjects; }

	bool GetTimeControl() { return _isTimeControl; }
	void SetTimeControl(bool value) { _isTimeControl = value; }

protected:
	vector<GameObject*> _gameObjects;

private:
	bool _isDrawCol = false;
	bool _isDrawFPS = false;

	// true �� �Ǹ� FixedUpdate, Update�� ���ߵ�..
	// �ٵ� UI�� Update�� ���ư����Ѵ� ����..
	bool _isTimeControl = false;
};

