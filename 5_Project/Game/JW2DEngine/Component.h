#pragma once

/// <summary>
/// �̰� ������ ������ �߿��ϴ�... ���� -> Ʈ������ ��ġ �ٲ� -> �ݶ��̴� -> ����.. -> ī�޶�? �� ������.. 
/// </summary>
enum class COMPONENT_TYPE
{
	RIGIDBODY,
	TRANSFORM,
	BOX_COLLIDER,
	CIRCLE_COLLIDER,
	OBB_COLLIDER,
	SPRITE_RENDERER,
	ANIMATOR,
	CIRCLE_RENDERER,
	BOX_RENDERER,
	CANVAS,
	BUTTON,
	PANEL,
	CAMERA,
	TEXT,
	MONO_BEHAVIOUR,
	END,
};

enum
{
	COMPONENT_COUNT = (int)(COMPONENT_TYPE::END) - 1
};

class GameObject;
class Transform;
class Rigidbody;

class Component
{
public:
	Component(GameObject* gameObject, COMPONENT_TYPE);
	virtual ~Component();

private:
	bool _isEnable;

	GameObject* _gameObject;

private:
	void SetActive(bool _value);

protected:
	COMPONENT_TYPE _type;

	bool _isDrawCol = false;

public:
	COMPONENT_TYPE GetType() { return _type;}

	GameObject* GetGameObject() { return _gameObject; }

	void SetDrawCol(bool value) { _isDrawCol = value; }

	virtual void Awake() {};

	virtual void FixedUpdate() {};	
	
	virtual void Update() {};		
	
	virtual void LateUpdate() {};	

	virtual void FinalUpdate() {}; // �������� ������ ���ֱ����� ������Ʈ �̴�.
};

