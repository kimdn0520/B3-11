#include "pch.h"
#include "prefab.h"
#include "GameOverTextPrefab.h"

GameOverTextPrefab::GameOverTextPrefab(Vector2 pos, Transform* parentTransform)
	:GameObject(TAG::UI)
{
	SetName("GameOverTextPrefab");
	SetActive(true);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetParent(parentTransform);
	GetComponent<Transform>()->SetLocalPosition(Vector2(0.f, -400.f));
	AddComponent<Animator>();
	GetComponent<Animator>()->AddAnimClip("GameOverAnim", AnimClipLoader::LoadClip(AnimClipPath("GameOverAnim")));
	GetComponent<Animator>()->Play(AnimClipLoader::LoadClip(AnimClipPath("GameOverAnim")));
	SetActive(false);
	SetCameraView(true);
}

GameOverTextPrefab::~GameOverTextPrefab()
{
}
