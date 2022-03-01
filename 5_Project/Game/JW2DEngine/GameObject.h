#pragma once
#include "Component.h"
#include "EventManager.h"
#include "ObjectPool.h"


class Transform;
class MonoBehaviour;
class BoxCollider;

/// <summary>
/// 기초가 되는 클래스이다.
/// 빈 껍데기인 게임오브젝트에 컴포넌트들을 붙여서 하나의 오브젝트를 만든다.
/// </summary>
class GameObject
{
private:
	GameObject();
public:
	GameObject(TAG tag);
	virtual ~GameObject();

	static map<int, vector<int>> _notAffectTag;

	int _tag;//todo : 옮기기
private:
	Vector2 _pos;

	string _name;


	bool _isEnable = true;				// 기본값은 true, true경우에만 게임오브젝트를 업데이트해줄것이다.

	bool _isBasicEnable = true;			// 원래 이 게임오브젝트의 상태(처음부터 꺼져있을 경우도 있고.. 오브젝트 풀 생성 삭제할때 판단하려고 썼음)

	bool _isDrawCol = false;

	bool _isCameraView = false;			// false로 되있어야하는뎅

	vector<string> _notColTagList;

	vector<GameObject*> _childObjects;

	array<Component*, COMPONENT_COUNT> _components;
	MonoBehaviour* _script;				// 게임오브젝트당 스크립트는 하나만 들어간다.

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

	// 해당 게임오브젝트와 상호 작용을 하지 않을 태그를 설정한다.
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
