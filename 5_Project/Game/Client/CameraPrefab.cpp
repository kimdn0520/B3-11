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
	GetComponent<BoxCollider>()->SetWH(width, height);		// 카메라 트리거 크기를 키우고싶으면 이걸로 키우자
	AddComponent<CameraController>();
	SetCameraView(setCamerraView);
}

CameraPrefab::~CameraPrefab()
{
}
