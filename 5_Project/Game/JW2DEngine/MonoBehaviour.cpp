#include "pch.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"

using namespace std;

MonoBehaviour::MonoBehaviour(GameObject* gameObject)
	: Component(gameObject, COMPONENT_TYPE::MONO_BEHAVIOUR)
{}

MonoBehaviour::~MonoBehaviour()
{}

/// <summary>
/// 프로그램 실행중에(런타임) 게임오브젝트(프리팹)를 생성할 수 있도록 해준다.
/// </summary>
void MonoBehaviour::Instantiate(GameObject* prefab, Vector2 pos)
{
	// 위치 설정
	prefab->GetComponent<Transform>()->SetLocalPosition(pos);

	// 생성 예약
	//SCENE_MANAGER->SetInstantiateGameObject(prefab);

	// 만약 그 프리팹에 자식오브젝트가 들어있다면 생성 예약을 같이 걸어준다.
	// 이렇게하면 자식의 자식오브젝트가 있으면 그것도 된다.
	if (!prefab->GetChildObjects().empty())
	{
		for (int i = 0; i < prefab->GetChildObjects().size(); i++)
		{
			Instantiate(prefab->GetChildObjects()[i], prefab->GetChildObjects()[i]->GetComponent<Transform>()->GetLocalPosition());
		}
	}
}

/// <summary>
/// 프로그램 실행중에(런타임) 게임오브젝트를 삭제할 수 있도록 해준다.
/// </summary>
void MonoBehaviour::Destroy(GameObject* gameObject, float destroyTime)
{
	SCENE_MANAGER->SetRemoveGameObject(gameObject, destroyTime);

	// 만약 자식오브젝트가 있다면 자식오브젝트도 삭제 예약을 그 다음에 걸어준다.
	// 이렇게하면 자식의 자식오브젝트가 있으면 그것도 된다.
	if (!gameObject->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObject->GetChildObjects().size(); i++)
		{
			Destroy(gameObject->GetChildObjects()[i], destroyTime);
		}
	}
}