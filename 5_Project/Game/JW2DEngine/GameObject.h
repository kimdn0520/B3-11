#pragma once
#include "Component.h"
#include "EventManager.h"
#include "ObjectPool.h"


class Transform;
class MonoBehaviour;
class BoxCollider;

/// <summary>
/// ���ʰ� �Ǵ� Ŭ�����̴�.
/// �� �������� ���ӿ�����Ʈ�� ������Ʈ���� �ٿ��� �ϳ��� ������Ʈ�� �����.
/// </summary>
class GameObject
{
private:
	GameObject();
public:
	GameObject(TAG tag);
	virtual ~GameObject();

	static map<int, vector<int>> _notAffectTag;

	int _tag;//todo : �ű��
private:
	Vector2 _pos;

	string _name;


	bool _isEnable = true;				// �⺻���� true, true��쿡�� ���ӿ�����Ʈ�� ������Ʈ���ٰ��̴�.

	bool _isBasicEnable = true;			// ���� �� ���ӿ�����Ʈ�� ����(ó������ �������� ��쵵 �ְ�.. ������Ʈ Ǯ ���� �����Ҷ� �Ǵ��Ϸ��� ����)

	bool _isDrawCol = false;

	bool _isCameraView = false;			// false�� ���־���ϴµ�

	vector<string> _notColTagList;

	vector<GameObject*> _childObjects;

	array<Component*, COMPONENT_COUNT> _components;
	MonoBehaviour* _script;				// ���ӿ�����Ʈ�� ��ũ��Ʈ�� �ϳ��� ����.

public:
	string GetName() { return _name; }
	void SetName(const string& name) { _name = name; }

	int GetTag() { return _tag; }
	void SetTag(int tag) { _tag = tag; }

	MonoBehaviour* GetScript() { return _script; }

	template <class TComponent>
	void AddComponent();
	
	template <typename TComponent>
	TComponent* GetComponent();

	template <typename TComponent>
	TComponent* GetScriptComponent();

	bool GetEnable() { return _isEnable; }
	void SetActive(bool value);

	bool GetBasicEnable() { return _isBasicEnable; }
	void SetBasicEnable(bool value) { _isBasicEnable = value; }

	vector<GameObject*> GetChildObjects() { return _childObjects; }
	void SetChildObject(GameObject* gameObject) { _childObjects.push_back(gameObject); }

	void SetDrawCol(bool value) { _isDrawCol = value; }

	// �ش� ���ӿ�����Ʈ�� ��ȣ �ۿ��� ���� ���� �±׸� �����Ѵ�.
	void SetNotColTag(string name);

	bool GetCameraView() { return _isCameraView; }
	void SetCameraView(bool value) { _isCameraView = value; }

	void Awake();

	void PreProcess();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void FinalUpdate();
};

template<typename TComponent>
inline TComponent* GameObject::GetComponent()
{
	this;
	for (int i = 0; i < COMPONENT_COUNT; i++)
	{
		TComponent* castedComponent = dynamic_cast<TComponent*>(_components[i]);

		if (castedComponent != nullptr)
			return castedComponent;
	}

	return nullptr;
}

template<typename TComponent>
inline TComponent* GameObject::GetScriptComponent()
{
	TComponent* castedComponent = dynamic_cast<TComponent*>(_script);

	if (castedComponent != nullptr)
		return castedComponent;

	return nullptr;
}

template<class TComponent>
inline void GameObject::AddComponent()
{
	TComponent* _newComponent = new TComponent(this);

	int typeIndex = (int)_newComponent->GetType();

	if (typeIndex < COMPONENT_COUNT)
	{
		_components[(int)_newComponent->GetType()] = _newComponent;
	}
	else
	{
		_script = dynamic_cast<MonoBehaviour*>(_newComponent);
	}
}
