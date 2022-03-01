#include "pch.h"
#include "BulletPrefab.h"
#include "Transform.h"
#include "CircleRenderer.h"		// Sprite로 교체 예정
#include "CircleCollider.h"
#include "Bullet.h"
#include "prefab.h"

BulletPrefab::BulletPrefab()
	:GameObject(TAG::Bullet)
{
	this->SetName("BulletPrefab");
	this->SetActive(true);
	this->AddComponent<Transform>();
	this->AddComponent<CircleCollider>();
	this->GetComponent<CircleCollider>()->SetRadius(10.f);
	this->GetComponent<CircleCollider>()->SetTrigger(true);
	this->AddComponent<Bullet>();
	AddComponent<Animator>();
	GetComponent<Animator>()->Play(AnimClipLoader::LoadClip(AnimClipPath("NormalAttack")));
	SetCameraView(true);
}

BulletPrefab::~BulletPrefab()
{}

