#pragma once
#include "MonoBehaviour.h"

class GameObject;

class PlayerHeadTrigger : public MonoBehaviour
{
public:
	PlayerHeadTrigger(GameObject* gameObject);
	~PlayerHeadTrigger();

private:
	GameObject* _playerObj;

public:
	// ĳ������ Ʈ���Ÿ� ��Ʈ�� �ϱ� ���� ĳ������ Obj�� �ҷ����� �Լ�
	void SetPlayerTrigger(GameObject* gameObject) { _playerObj = gameObject; }

private:
	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerExit(ColliderBase* collider) override;
};

