#pragma once
#include "MonoBehaviour.h"

class Camera;
class Text;

class CameraController : public MonoBehaviour 
{
public:
	CameraController(GameObject* gameObject);
	virtual ~CameraController();

public:
	void SetCamera(GameObject* camera) { _camera = camera; }
	void SetPlayer(GameObject* player) { _player = player;}

	virtual void OnTriggerEnter(ColliderBase* col) override;
	virtual void OnTriggerStay(ColliderBase* col) override;
	virtual void OnTriggerExit(ColliderBase* col) override;

	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	void SetMapSize(Vector2 mapSize) { _mapSize = mapSize; };

private:
	GameObject* _camera;

	GameObject* _player;

	Vector2 _mapSize;

	Text* _text;
};

