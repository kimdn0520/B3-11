#pragma once
#include "MonoBehaviour.h"

class GameObject;

class SavePoint : public MonoBehaviour
{
public:
	SavePoint(GameObject* gameObject);
	~SavePoint();

	void SetSprite(GameObject* spriteObj) {_sprite = spriteObj;}
	void SetPlayer(GameObject* playerObj) { _playerObj = playerObj;}

public:
	string savePoint;

	GameObject* _fadeInObj;

	GameObject* _sprite;

	GameObject* _playerObj;

private:
 virtual void OnTriggerStay(ColliderBase* collider) override;

public:
	void SetFadeInObj(GameObject* fadeInObj) { _fadeInObj = fadeInObj; }

};

