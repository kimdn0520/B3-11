#pragma once

class GameObject;

class Scene
{
public:
	virtual void Init() {};

	void Awake();

	void PreProcess();
	void FixedUpdate();
	void Update();			// virtual 해서 따로 관리할까?
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

	// true 가 되면 FixedUpdate, Update는 멈추되..
	// 근데 UI는 Update가 돌아가야한다 주의..
	bool _isTimeControl = false;
};

