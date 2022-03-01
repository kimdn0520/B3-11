#include "pch.h"
#include "prefab.h"
#include "CameraPrefab.h"
#include "EnginePch.h"
#include "JW2DEngine.h"

CameraPrefab::CameraPrefab(float width, float height, bool setTrigger, bool setCamerraView)
	:GameObject(TAG::NONE)
{
	SetName("Camera");
	AddComponent<Transform>();
	AddComponent<Camera>();
	AddComponent<BoxCollider>();
	AddComponent<Text>();
	GetComponent<BoxCollider>()->SetTrigger(setTrigger);	
	GetComponent<BoxCollider>()->SetWH(width, height);		// ī�޶� Ʈ���� ũ�⸦ Ű�������� �̰ɷ� Ű����
	AddComponent<CameraController>();
	SetCameraView(setCamerraView);
}

CameraPrefab::~CameraPrefab()
{
}
