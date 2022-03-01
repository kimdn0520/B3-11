#include "pch.h"
#include "TestEnemyPrefab.h"
#include "BulletPrefab.h"
#include "Transform.h"
#include "CircleRenderer.h"		// Sprite로 교체 예정
#include "BoxCollider.h"
#include "EnemyController.h"

TestEnemyPrefab::TestEnemyPrefab()
	:GameObject(TAG::Enemy)
{
	this->SetName("TestEnemyPrefab");
	this->SetActive(true);
	this->AddComponent<Transform>();
	this->AddComponent<BoxCollider>();
	this->GetComponent<BoxCollider>()->SetWH(128, 128);
	this->AddComponent<EnemyController>();

	/*GameObject * atkPos = new GameObject();
	atkPos->SetName("EnemyAttackPos");
	atkPos->SetTag((int)TAG::EnemyAtk);
	atkPos->SetActive(true);
	atkPos->AddComponent<Transform>();
	atkPos->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
	atkPos->GetComponent<Transform>()->SetLocalPosition(Vector2(100, 0));
	atkPos->AddComponent<BoxCollider>();
	atkPos->GetComponent<BoxCollider>()->SetWH(40, 40);
	atkPos->GetComponent<BoxCollider>()->SetTrigger(true);
	atkPos->SetActive(false);
	atkPos->SetBasicEnable(false);*/

	/*GameObject* enemy = new GameObject();
	enemy->SetName("enemy");
	enemy->SetTag("Enemy");
	enemy->AddComponent<Transform>();
	enemy->GetComponent<Transform>()->SetLocalPosition(Vector2(600.f, 700.f));
	enemy->AddComponent<BoxCollider>();
	enemy->GetComponent<BoxCollider>()->SetWH(128, 128);
	enemy->GetComponent<BoxCollider>()->SetTrigger(true);
	enemy->AddComponent<Text>();
	enemy->AddComponent<EnemyController>();
	AddGameObject(enemy);*/
}

TestEnemyPrefab::~TestEnemyPrefab()
{}