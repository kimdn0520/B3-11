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
	
	// ����� ������ ���ְ� ���ִ� �κ��̴�.
	if (INPUT->GetButtonDown(KEY_TYPE::F1))
		isDebug = !isDebug;
	

	_activeScene->PreProcess();
	_activeScene->FixedUpdate();
	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

/// <summary>
/// _nextScene�� �ҷ��� ���� �־��ش�.
/// ����Ⱦ��� �ҷ��� �� �ֵ��� �Ѵ�.
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
/// ����� �� (���� �����ӿ� ������ �ش�.)
/// </summary>
void SceneManager::ReservedScene()
{
	// TODO : ���� Scene ����
	// TODO : Scene ���� �ε�

	// ������� �ִٸ� �������ش�.
	if (_activeScene != nullptr)
	{
		// �����Ҵ� ����
		for (auto iter : _activeScene->GetGameObjects())
		{
			delete iter;
		}

		// clear �� capacity ����
		_activeScene->AllClearGameObject();
	}

	_activeScene = _nextScene;	// ���� ���� �־��ش�.
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

	// �ڽ� ������Ʈ�� �ִٸ�
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
	_setActiveFalseGameObjectList.push_front(gameObject); // �� �ڿ������� �Ϸ��� front�� �ߴµ�.. ��

	// �ڽ� ������Ʈ�� �ִٸ�
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
/// True ���·� �ٲ�� �� �͵�..
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
/// False ���·� �ٲ�� �� �͵�
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
