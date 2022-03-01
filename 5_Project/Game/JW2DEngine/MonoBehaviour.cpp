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
/// ���α׷� �����߿�(��Ÿ��) ���ӿ�����Ʈ(������)�� ������ �� �ֵ��� ���ش�.
/// </summary>
void MonoBehaviour::Instantiate(GameObject* prefab, Vector2 pos)
{
	// ��ġ ����
	prefab->GetComponent<Transform>()->SetLocalPosition(pos);

	// ���� ����
	//SCENE_MANAGER->SetInstantiateGameObject(prefab);

	// ���� �� �����տ� �ڽĿ�����Ʈ�� ����ִٸ� ���� ������ ���� �ɾ��ش�.
	// �̷����ϸ� �ڽ��� �ڽĿ�����Ʈ�� ������ �װ͵� �ȴ�.
	if (!prefab->GetChildObjects().empty())
	{
		for (int i = 0; i < prefab->GetChildObjects().size(); i++)
		{
			Instantiate(prefab->GetChildObjects()[i], prefab->GetChildObjects()[i]->GetComponent<Transform>()->GetLocalPosition());
		}
	}
}

/// <summary>
/// ���α׷� �����߿�(��Ÿ��) ���ӿ�����Ʈ�� ������ �� �ֵ��� ���ش�.
/// </summary>
void MonoBehaviour::Destroy(GameObject* gameObject, float destroyTime)
{
	SCENE_MANAGER->SetRemoveGameObject(gameObject, destroyTime);

	// ���� �ڽĿ�����Ʈ�� �ִٸ� �ڽĿ�����Ʈ�� ���� ������ �� ������ �ɾ��ش�.
	// �̷����ϸ� �ڽ��� �ڽĿ�����Ʈ�� ������ �װ͵� �ȴ�.
	if (!gameObject->GetChildObjects().empty())
	{
		for (int i = 0; i < gameObject->GetChildObjects().size(); i++)
		{
			Destroy(gameObject->GetChildObjects()[i], destroyTime);
		}
	}
}