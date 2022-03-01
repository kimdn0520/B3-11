#include "pch.h"
#include "ObjectPool.h"

GameObject* ObjectPool::SpawnFromPool(string name, Vector2 pos)
{
	OutputDebugString(L"생성함");
	GameObject* tmpGameObj = objectMapList[name].front();
	objectMapList[name].pop();

	tmpGameObj->GetComponent<Transform>()->SetLocalPosition(pos);

	//SCENE_MANAGER->SetActiveTrueGameObject(tmpGameObj);
	tmpGameObj->SetActive(true);

	// 그 스폰할 오브젝트가 자식오브젝트가 있다면 걔내들도 true 해준다.
	if (!tmpGameObj->GetChildObjects().empty())
	{
		for (int i = 0; i < tmpGameObj->GetChildObjects().size(); i++)
		{
			// 자식오브젝트가 원래 꺼져 있는 경우는 true를 해주면 안된다! 아!
			// 근데 켜줄때도 문제임 그니까.. 원래 Basic을 알면된다.
			if (tmpGameObj->GetChildObjects()[i]->GetBasicEnable())
				SpawnChildObject(tmpGameObj->GetChildObjects()[i]);
		}
	}

	return tmpGameObj;
}

/// <summary>
/// 재귀적으로 그 자식에 자식이 있다면 true...
/// </summary>
void ObjectPool::SpawnChildObject(GameObject* gameObject)
{
	SCENE_MANAGER->SetActiveTrueGameObject(gameObject);

	// 그 스폰할 오브젝트가 자식오브젝트가 있다면 걔내들도 true 해준다.
	if (!gameObject->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObject->GetChildObjects().size(); i++)
		{
			SpawnChildObject(gameObject->GetChildObjects()[i]);
		}
	}
}

void ObjectPool::ReturnObject(GameObject* gameObj)
{
	OutputDebugString(L"반환함, %d \n");
	// 콜라이더가 있다면 
	if (gameObj->GetComponent<BoxCollider>() != nullptr)
	{
		gameObj->GetComponent<BoxCollider>()->ResetCollsionInfo();
	}
	else if (gameObj->GetComponent<CircleCollider>() != nullptr)
	{
		gameObj->GetComponent<CircleCollider>()->ResetCollsionInfo();
	}

	SCENE_MANAGER->SetActiveFalseGameObject(gameObj);

	// Parent가 없으면 이뇨속이 최상위 오브젝트라서 push 해준다.
	if (!gameObj->GetComponent<Transform>()->GetParent())
		objectMapList[gameObj->GetName()].push(gameObj);

	// 만약 자식 오브젝트가 있다면 자식오브젝트들은 SetActvie(false) 해준다.
	if (!gameObj->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObj->GetChildObjects().size(); i++)
		{
			ReturnObject(gameObj->GetChildObjects()[i]);
		}
	}
}

void ObjectPool::CreateNewObj(GameObject* prefab)
{
	// 오브젝트풀에 추가해줄 프리팹의 상태를 꺼주고 위치는 해줄 필요없구
	prefab->SetActive(false);

	// 생성 예약
	//SCENE_MANAGER->SetInstantiateGameObject(prefab);

	//// 만약 그 프리팹에 자식오브젝트가 들어있다면 생성 예약을 같이 걸어준다.
	//// 이렇게하면 자식의 자식오브젝트가 있으면 그것도 된다.
	//if (!prefab->GetChildObjects().empty())
	//{
	//	for (int i = 0; i < prefab->GetChildObjects().size(); i++)
	//	{
	//		CreateNewObj(prefab->GetChildObjects()[i]);
	//	}
	//}

	// 씬에 오브젝트 모아놓은곳에 추가해주고
	// Instantiate 함수안에 자식오브젝트가 있다면 생성해주는 코드가 있다.
	//prefab->GetScriptComponent<TObject>()->Instantiate(prefab, Vector2(0, 0));

	// 오브젝트풀 리스트에 추가해준다.
	// 부모오브젝트가 없는것 -> 최상위 오브젝트 만 추가해준다.
	/*if (!prefab->GetComponent<Transform>()->GetParent())
		objectMapList[prefab->GetName()].push(prefab);*/
	objectMapList[prefab->GetName()].push(prefab);
}