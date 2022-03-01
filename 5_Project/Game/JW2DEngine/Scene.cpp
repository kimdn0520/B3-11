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
/// 프레임을 기반으로 호출되는 Update 와 달리 Fixed Timestep에 설정된 값에 따라 일정한 간격으로 호출됩니다. 
/// 물리 효과가 적용된(Rigidbody) 오브젝트를 조정할 때 사용됩니다
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
/// 스크립트가 enabled 상태일때, 매 프레임마다 호출됩니다.
/// 일반적으로 가장 빈번하게 사용되는 함수이며, 물리 효과가 적용되지 않은 오브젝트의 움직임이나 
/// 단순한 타이머, 키 입력을 받을 때 사용됩니다.
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
/// 모든 Update 함수가 호출된 후, 마지막으로 호출됩니다. 
/// 주로 오브젝트를 따라가게 설정한 카메라는 LateUpdate 를 사용합니다.
/// (카메라가 따라가는 오브젝트가 Update함수 안에서 움직일 경우가 있기 때문).
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
/// (FixedUpdate, Update, LateUpdate)에서 계산된 모든 것들을 Render 해주는 FinalUpdate 입니다.
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
