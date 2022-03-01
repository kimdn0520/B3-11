#include "pch.h"
#include "ObjectPool.h"

GameObject* ObjectPool::SpawnFromPool(string name, Vector2 pos)
{
	OutputDebugString(L"������");
	GameObject* tmpGameObj = objectMapList[name].front();
	objectMapList[name].pop();

	tmpGameObj->GetComponent<Transform>()->SetLocalPosition(pos);

	//SCENE_MANAGER->SetActiveTrueGameObject(tmpGameObj);
	tmpGameObj->SetActive(true);

	// �� ������ ������Ʈ�� �ڽĿ�����Ʈ�� �ִٸ� �³��鵵 true ���ش�.
	if (!tmpGameObj->GetChildObjects().empty())
	{
		for (int i = 0; i < tmpGameObj->GetChildObjects().size(); i++)
		{
			// �ڽĿ�����Ʈ�� ���� ���� �ִ� ���� true�� ���ָ� �ȵȴ�! ��!
			// �ٵ� ���ٶ��� ������ �״ϱ�.. ���� Basic�� �˸�ȴ�.
			if (tmpGameObj->GetChildObjects()[i]->GetBasicEnable())
				SpawnChildObject(tmpGameObj->GetChildObjects()[i]);
		}
	}

	return tmpGameObj;
}

/// <summary>
/// ��������� �� �ڽĿ� �ڽ��� �ִٸ� true...
/// </summary>
void ObjectPool::SpawnChildObject(GameObject* gameObject)
{
	SCENE_MANAGER->SetActiveTrueGameObject(gameObject);

	// �� ������ ������Ʈ�� �ڽĿ�����Ʈ�� �ִٸ� �³��鵵 true ���ش�.
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
	OutputDebugString(L"��ȯ��, %d \n");
	// �ݶ��̴��� �ִٸ� 
	if (gameObj->GetComponent<BoxCollider>() != nullptr)
	{
		gameObj->GetComponent<BoxCollider>()->ResetCollsionInfo();
	}
	else if (gameObj->GetComponent<CircleCollider>() != nullptr)
	{
		gameObj->GetComponent<CircleCollider>()->ResetCollsionInfo();
	}

	SCENE_MANAGER->SetActiveFalseGameObject(gameObj);

	// Parent�� ������ �̴����� �ֻ��� ������Ʈ�� push ���ش�.
	if (!gameObj->GetComponent<Transform>()->GetParent())
		objectMapList[gameObj->GetName()].push(gameObj);

	// ���� �ڽ� ������Ʈ�� �ִٸ� �ڽĿ�����Ʈ���� SetActvie(false) ���ش�.
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
	// ������ƮǮ�� �߰����� �������� ���¸� ���ְ� ��ġ�� ���� �ʿ����
	prefab->SetActive(false);

	// ���� ����
	//SCENE_MANAGER->SetInstantiateGameObject(prefab);

	//// ���� �� �����տ� �ڽĿ�����Ʈ�� ����ִٸ� ���� ������ ���� �ɾ��ش�.
	//// �̷����ϸ� �ڽ��� �ڽĿ�����Ʈ�� ������ �װ͵� �ȴ�.
	//if (!prefab->GetChildObjects().empty())
	//{
	//	for (int i = 0; i < prefab->GetChildObjects().size(); i++)
	//	{
	//		CreateNewObj(prefab->GetChildObjects()[i]);
	//	}
	//}

	// ���� ������Ʈ ��Ƴ������� �߰����ְ�
	// Instantiate �Լ��ȿ� �ڽĿ�����Ʈ�� �ִٸ� �������ִ� �ڵ尡 �ִ�.
	//prefab->GetScriptComponent<TObject>()->Instantiate(prefab, Vector2(0, 0));

	// ������ƮǮ ����Ʈ�� �߰����ش�.
	// �θ������Ʈ�� ���°� -> �ֻ��� ������Ʈ �� �߰����ش�.
	/*if (!prefab->GetComponent<Transform>()->GetParent())
		objectMapList[prefab->GetName()].push(prefab);*/
	objectMapList[prefab->GetName()].push(prefab);
}