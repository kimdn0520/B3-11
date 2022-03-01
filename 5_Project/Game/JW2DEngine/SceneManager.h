#pragma once

class Scene;
class GameObject;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Release();

	void Update();
	void LoadScene(string sceneName);

public:
	bool isTutorialScene()
	{
		return(_activeScene == _sceneList["TutorialScene"]);
	}

	Scene* GetActiveScene() { return _activeScene; }

	map<string, Scene*> GetSceneList() { return _sceneList; }

	bool GetIsReservedLoadScene() { return _isReservedLoadScene; }

	bool GetIsReservedTimeControl() { return _isReservedTimeControl; }
	void SetIsReservedTimeControl(bool value);

	queue<GameObject*> GetInstantiateGameObjectQueue() { return _instantiateGameObjectQueue; }
	void SetInstantiateGameObject(GameObject* gameObject) { _instantiateGameObjectQueue.push(gameObject); }
	
	map<GameObject*, pair<float, float>> GetDestroyList() { return _destroyList; }
	void SetIsRemoveGameObject(bool value) { _isReservedRemoveGameObject = value; }//ajw 해야할 곳
	void SetRemoveGameObject(GameObject* gameObject, float destroyTime);

	void SetActiveTrueGameObject(GameObject* gameObject);
	void SetActiveFalseGameObject(GameObject* gameObject);

	template <typename TScene>
	void InputScene(string sceneName);
	void ReservedScene();

	void ReservedInstantiateGameObject();
	void ReservedRemoveGameObject();

	void ReservedActiveTrueGameObject();
	void ReservedActiveFalseGameObject();

	void ReservedTimeControl();

	void SetPlayerPos(Vector2 playerPos) { _playerPos = playerPos; }
	Vector2 GetPlayerPos() { return _playerPos; }
	void SetSavePointPos() { _playerPos = _savePointPlayerPos; }

	void SetSavePoint(string savePointName) { _savePointName = savePointName; }
	string GetSavePoint() { return _savePointName; }

public:
	// 디버그용
	bool isDebug = false;

private:
	Scene* _activeScene;
	Scene* _nextScene;
	map<string, Scene*> _sceneList;

	queue<GameObject*> _instantiateGameObjectQueue;

	list<GameObject*> _setActiveTrueGameObjectList;

	list<GameObject*> _setActiveFalseGameObjectList;

	map<GameObject*, pair<float, float>> _destroyList;

	bool _isReservedLoadScene = false;

	bool _isReservedRemoveGameObject = false;

	bool _isReservedTimeControl = false;

	Vector2 _playerPos = { 2 * 128.f, 5 * 128.f };
	Vector2 _savePointPlayerPos = { 7 * 128.f, 6 * 128.f };
	string _savePointName = "TutorialScene";
};

template<typename TScene>
inline void SceneManager::InputScene(string sceneName)
{
	_sceneList[sceneName] = (Scene*)new TScene;
}
