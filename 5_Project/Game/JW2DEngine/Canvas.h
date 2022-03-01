#pragma once
#include "Component.h"

class GameObject;
class Transform;

/// <summary>
/// Canvas는 모든 UI 객체의 렌더링을 관리하기 위한 루트 컴포넌트 이다.
/// 모든 UI 구성 요소들은 모두 캔버스 밑에 위치한다(캔버스의 자식)
/// 3가지의 렌더모드가 있지만 Screen Space - Camera 방식으로 한다.
/// 이 모드는 캔버스는 항상 카메라를 따라다니며 카메라 앞에 위치하게 된다.
/// 따라서 좌표 상에서의 위치 값을 가지게 된다.
/// </summary>
class Canvas : public Component
{
public:
	Canvas(GameObject* gameObject);
	virtual ~Canvas();

private:
	GameObject* _renderCamera;		// UI를 렌더해줄 카메라를 등록해야한다.

	Transform* _transform;

public:
	void SetRenderCamera(GameObject* renderCamera);

	void Update();

	void LateUpdate();
};

