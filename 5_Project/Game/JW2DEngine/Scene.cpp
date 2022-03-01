#include "pch.h"
#include "Scene.h"
#include "JW2DEngine.h"
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"

void Scene::Awake()
{
	for (auto gameObject : _gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::PreProcess()
{
	for (auto gameObject : _gameObjects)
	{
		if (gameObject->GetEnable())
			gameObject->PreProcess();
	}
}

/// <summary>
/// �������� ������� ȣ��Ǵ� Update �� �޸� Fixed Timestep�� ������ ���� ���� ������ �������� ȣ��˴ϴ�. 
/// ���� ȿ���� �����(Rigidbody) ������Ʈ�� ������ �� ���˴ϴ�
/// </summary>
void Scene::FixedUpdate()
{
	if(_isTimeControl)
		return;

	if (INPUT->GetButtonDown(KEY_TYPE::F1))
	{
		_isDrawCol = !_isDrawCol;
		_isDrawFPS = !_isDrawFPS;
	}
		
	for (auto gameObject : _gameObjects)
	{
		gameObject->SetDrawCol(_isDrawCol);

		if (gameObject->GetEnable())
			gameObject->FixedUpdate();
	}
}

/// <summary>
/// ��ũ��Ʈ�� enabled �����϶�, �� �����Ӹ��� ȣ��˴ϴ�.
/// �Ϲ������� ���� ����ϰ� ���Ǵ� �Լ��̸�, ���� ȿ���� ������� ���� ������Ʈ�� �������̳� 
/// �ܼ��� Ÿ�̸�, Ű �Է��� ���� �� ���˴ϴ�.
/// </summary>
void Scene::Update()
{
	for (auto gameObject : _gameObjects)
	{
		if (_isTimeControl && gameObject->GetTag() != (int)TAG::UI)
		{
			continue;
		}


		if (gameObject->_tag == (int)TAG::Bullet)
		{
			int a = 10;
		}

		if(gameObject->GetEnable())
			gameObject->Update();
	}
}

/// <summary>
/// ��� Update �Լ��� ȣ��� ��, ���������� ȣ��˴ϴ�. 
/// �ַ� ������Ʈ�� ���󰡰� ������ ī�޶�� LateUpdate �� ����մϴ�.
/// (ī�޶� ���󰡴� ������Ʈ�� Update�Լ� �ȿ��� ������ ��찡 �ֱ� ����).
/// </summary>
void Scene::LateUpdate()
{
	for (auto gameObject : _gameObjects)
	{
		if (gameObject->GetEnable())
			gameObject->LateUpdate();
	}
}


/// <summary>
/// (FixedUpdate, Update, LateUpdate)���� ���� ��� �͵��� Render ���ִ� FinalUpdate �Դϴ�.
/// </summary>
void Scene::FinalUpdate()
{
	for (auto gameObject : _gameObjects)
	{
		if (gameObject->GetEnable())
			gameObject->FinalUpdate();
	}

	Debug_FPS();
}

void Scene::AddGameObject(GameObject* gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	auto findIt = find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	
	if (findIt != _gameObjects.end())
	{
  		delete *findIt;			
		*findIt = nullptr;
		_gameObjects.erase(findIt);
	}
}

void Scene::AllClearGameObject()
{
	_gameObjects.clear();

	vector<GameObject*>().swap(_gameObjects);
}

void Scene::Debug_FPS()
{
	if (SCENE_MANAGER->isDebug && GEngine->GetMainCamera() != nullptr)
	{
		string str = "[ FPS : " + to_string(TIMER->GetFps()) + " ]";

		const char* FPS_TEXT = str.c_str();

		GEngine->SetTransform(GEngine->GetMainCamera()->GetComponent<Transform>()->GetWorldMatrix());

		GEngine->DrawTextScreen(-600.f, -500.f,
			700, 400, 0, FPS_TEXT);
	}
}
