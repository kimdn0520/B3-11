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
	// 캐릭터의 트리거를 컨트롤 하기 위해 캐릭터의 Obj를 불러오는 함수
	void SetPlayerTrigger(GameObject* gameObject) { _playerObj = gameObject; }

private:
	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerExit(ColliderBase* collider) override;
};

