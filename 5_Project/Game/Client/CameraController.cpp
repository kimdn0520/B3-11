#include "pch.h"
#include "CameraController.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "ColliderBase.h"
#include "Timer.h"
#include "JW2DEngine.h"
#include "UIManager.h"
#include "Text.h"

CameraController::CameraController(GameObject* gameObject)
	: MonoBehaviour(gameObject),
	  _camera(nullptr), _player(nullptr)
{
	//_camera->GetComponent<Transform>()->SetLocalPosition(_player->GetComponent<Transform>()->GetLocalPosition());
	_text = gameObject->GetComponent<Text>();
}

CameraController::~CameraController()
{}

/// <summary>
/// 이 카메라의 트리거랑 부딪힌 애들만 보이게 + 충돌체크 할거임
/// </summary>
void CameraController::OnTriggerEnter(ColliderBase* col)
{
	
}

void CameraController::OnTriggerStay(ColliderBase* col)
{
	col->GetGameObject()->SetCameraView(true);


}

/// <summary>
/// 빠져나가면 그 게임오브젝트 false 시켜주고
/// </summary>
void CameraController::OnTriggerExit(ColliderBase* col)
{
	col->GetGameObject()->SetCameraView(false);
}

void CameraController::LateUpdate()
{
	// 카메라의 포지션은 플레이어를 따라간다.
	if (_player->GetComponent<Transform>()->GetLocalPosition().x <= 7.5f * 128.f && _player->GetComponent<Transform>()->GetLocalPosition().y <= 4.3 * 128.f)
	{
	_camera->GetComponent<Transform>()->SetLocalPosition(Vector2(7.5f * 128.f, 4.3 * 128.f));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().x > (_mapSize.x - 7.4f) * 128.f && _player->GetComponent<Transform>()->GetLocalPosition().y <= 4.3 * 128.f)
	{
	_camera->GetComponent<Transform>()->SetLocalPosition(Vector2((_mapSize.x - 7.4f) * 128.f, 4.3 * 128.f));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().x <= 7.5f * 128.f && _player->GetComponent<Transform>()->GetLocalPosition().y > (_mapSize.y - 3.95) * 128.f)
	{
	_camera->GetComponent<Transform>()->SetLocalPosition(Vector2(7.5f * 128.f, (_mapSize.y - 3.95) * 128.f));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().x > (_mapSize.x - 7.4f) * 128.f && _player->GetComponent<Transform>()->GetLocalPosition().y > (_mapSize.y - 3.95) * 128.f)
	{
	_camera->GetComponent<Transform>()->SetLocalPosition(Vector2((_mapSize.x - 7.4f) * 128.f, (_mapSize.y - 3.95) * 128.f));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().x <= 7.5f * 128.f)
	{
		_camera->GetComponent<Transform>()->SetLocalPosition(Vector2(7.5f * 128.f, _player->GetComponent<Transform>()->GetLocalPosition().y));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().x > (_mapSize.x - 7.4f) * 128.f)
	{
		_camera->GetComponent<Transform>()->SetLocalPosition(Vector2((_mapSize.x - 7.4f) * 128.f, _player->GetComponent<Transform>()->GetLocalPosition().y));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().y <= 4.3 * 128.f)
	{
		_camera->GetComponent<Transform>()->SetLocalPosition(Vector2(_player->GetComponent<Transform>()->GetLocalPosition().x, 4.3 * 128.f));
	}
	else if (_player->GetComponent<Transform>()->GetLocalPosition().y > (_mapSize.y - 3.95) * 128.f)
	{
		_camera->GetComponent<Transform>()->SetLocalPosition(Vector2(_player->GetComponent<Transform>()->GetLocalPosition().x, (_mapSize.y - 3.95) * 128.f));
	}
	else
	{
		_camera->GetComponent<Transform>()->SetLocalPosition
		(
			_player->GetComponent<Transform>()->GetLocalPosition()
		);
	}
	//else if ()
	if (_player->GetComponent<Transform>()->GetWorldPosition().x == 1600)
	{
		_camera->GetComponent<Transform>()->SetLocalPosition({ 1600, _player->GetComponent<Transform>()->GetLocalPosition().y});
	}

}

void CameraController::FinalUpdate()
{
}
