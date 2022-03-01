#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Timer.h"
#include "Input.h"
#include "GameObject.h"

void SceneManager::Release()
{
	for (auto iter : _sceneList)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
		}
	}
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;
	
	// 디버그 정보를 켜주고 꺼주는 부분이다.
	if (INPUT->GetButtonDown(KEY_TYPE::F1))
		isDebug = !isDebug;
	

	_activeScene->PreProcess();
	_activeScene->FixedUpdate();
	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

/// <summary>
/// _nextScene에 불러올 씬을 넣어준다.
/// 예약된씬을 불러올 수 있도록 한다.
/// </summary>
void SceneManager::LoadScene(string sceneName)
{	
	_isReservedLoadScene = true;

	_nextScene = _sceneList[sceneName];
}

void SceneManager::SetIsReservedTimeControl(bool value)
{
	_isReservedTimeControl = true;
	_activeScene->SetTimeControl(value); 
}


/// <summary>
/// 예약된 씬 (다음 프레임에 실행해 준다.)
/// </summary>
void SceneManager::ReservedScene()
{
	// TODO : 기존 Scene 정리
	// TODO : Scene 정보 로드

	// 현재씬이 있다면 정리해준다.
	if (_activeScene != nullptr)
	{
		// 동적할당 해제
		for (auto iter : _activeScene->GetGameObjects())
		{
			delete iter;
		}

		// clear 후 capacity 정리
		_activeScene->AllClearGameObject();
	}

	_activeScene = _nextScene;	// 다음 씬을 넣어준다.
	_activeScene->Init();

	_activeScene->Awake();

	_isReservedLoadScene = false;
}

void SceneManager::ReservedInstantiateGameObject()
{
	if (!_instantiateGameObjectQueue.empty())
	{
		_activeScene->AddGameObject(_instantiateGameObjectQueue.front());
		_instantiateGameObjectQueue.pop();
	}
}

void SceneManager::SetRemoveGameObject(GameObject* gameObject, float destroyTime)
{
	for (auto it = _destroyList.begin(); it != _destroyList.end(); ++it)
	{
		if (it->first == gameObject)
		{
			if (it->second.first > destroyTime)
			{
				it->second.first = destroyTime;
			}

			return;
		}
	}
	
	_destroyList.insert({ gameObject, {destroyTime, 0} });
}

void SceneManager::SetActiveTrueGameObject(GameObject* gameObject)
{
	_setActiveTrueGameObjectList.push_back(gameObject);

	// 자식 오브젝트가 있다면
	if (!gameObject->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObject->GetChildObjects().size(); i++)
		{
			SetActiveTrueGameObject(gameObject->GetChildObjects()[i]);
		}
	}
}

void SceneManager::SetActiveFalseGameObject(GameObject* gameObject)
{
	_setActiveFalseGameObjectList.push_front(gameObject); // 좀 자연스럽게 하려고 front로 했는뎅.. 흠

	// 자식 오브젝트가 있다면
	if (!gameObject->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObject->GetChildObjects().size(); i++)
		{
			SetActiveFalseGameObject(gameObject->GetChildObjects()[i]);
		}
	}
}

void SceneManager::ReservedRemoveGameObject()
{
	if (!_destroyList.empty())
	{
		for (auto it = _destroyList.begin(); it != _destroyList.end();)
		{
			it->second.second += DELTA_TIME;

			if (it->second.first <= it->second.second)
			{
				_activeScene->RemoveGameObject(it->first);
				_destroyList.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}
}

/// <summary>
/// True 상태로 바꿔야 할 것들..
/// </summary>
void SceneManager::ReservedActiveTrueGameObject()
{
	if(!_setActiveTrueGameObjectList.empty())
	{
		for (int i = 0; i < _setActiveTrueGameObjectList.size(); i++)
		{
			_setActiveTrueGameObjectList.front()->SetActive(true);
			_setActiveTrueGameObjectList.pop_front();
		}
	}
}

/// <summary>
/// False 상태로 바꿔야 할 것들
/// </summary>
void SceneManager::ReservedActiveFalseGameObject()
{
	if (!_setActiveFalseGameObjectList.empty())
	{
		for (int i = 0; i < _setActiveFalseGameObjectList.size(); i++)
		{
			_setActiveFalseGameObjectList.front()->SetActive(false);
			_setActiveFalseGameObjectList.pop_front();
		}
	}
}

void SceneManager::ReservedTimeControl()
{
	_activeScene->SetTimeControl(_activeScene->GetTimeControl());
	
	_isReservedTimeControl = false;
}
