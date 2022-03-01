#include "pch.h"
#include "prefab.h"
#include "EnemyPrefab.h"
#include "Turtle.h"
#include "Shark.h"
#include "Penguin.h"
#include "AngryMotion.h"

EnemyPrefab::EnemyPrefab(string name, Vector2 pos, float width, float height)
	:GameObject(TAG::Enemy)
{
	SetName(name);
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(pos);
	GetComponent<Transform>()->SetLocalScale(Vector2(1.f,1.f));
	AddComponent<Rigidbody>();
	GetComponent<Rigidbody>()->OnGravity(true);
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(width, height);
	AddComponent<Animator>();
	/*GetComponent<Animator>()->AddAnimClip("Walk", AnimClipLoader::LoadClip(AnimClipPath(name + "Move")));
	GetComponent<Animator>()->AddAnimClip("Dead", AnimClipLoader::LoadClip(AnimClipPath(name + "Dead")));*/


	GameObject* angryAnmation = new GameObject(TAG::ANGRYMOTION);
	angryAnmation->SetName("AngryAnimation");
	angryAnmation->AddComponent<Transform>();
	angryAnmation->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
	angryAnmation->AddComponent<BoxCollider>();
	angryAnmation->GetComponent<BoxCollider>()->SetWH(30, 30);
	angryAnmation->GetComponent<Transform>()->SetLocalPosition(Vector2(-20, -55));
	angryAnmation->GetComponent<BoxCollider>()->SetTrigger(true);
	angryAnmation->AddComponent<Animator>();
	angryAnmation->AddComponent<AngryMotion>();
	angryAnmation->GetScriptComponent<AngryMotion>()->Set(this);
	angryAnmation->GetScriptComponent<AngryMotion>()->SetAnimation(angryAnmation);

	SetCameraView(true);
	SetActive(true);

	//angryAnmation->SetActive(false);
}

EnemyPrefab::~EnemyPrefab()
{
}
