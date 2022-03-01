#include "pch.h"
#include "prefab.h"
#include "B3_11Prefab.h"
#include "B3_11.h"
#include "SavePoint.h"

B3_11Prefab::B3_11Prefab(Vector2 pos)
	:GameObject(TAG::Player)
{
	// Player
	SetName("Player");
	AddComponent<Transform>();
	GetComponent<Transform>()->SetLocalPosition(pos);
	GetComponent<Transform>()->SetLocalScale(Vector2(1.f, 1.f));
	AddComponent<Rigidbody>();
	GetComponent<Rigidbody>()->OnGravity(true);
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetWH(100, 176);
	AddComponent<Animator>();
	/*GetComponent<Animator>()->AddAnimClip("Idle", AnimClipLoader::LoadClip(AnimClipPath("B3_11_IDLE")));
	GetComponent<Animator>()->CreateAnimClip("Walk");
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(11, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(181, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(351, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(521, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(691, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Walk", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(861, 211), 163, 176, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->CreateAnimClip("Attack");
	GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\TestSheet\\Skul.png", Vector2(6, 305), 33, 45, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
	GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\TestSheet\\Skul.png", Vector2(45, 305), 33, 44, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
	GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\TestSheet\\Skul.png", Vector2(85, 305), 62, 55, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
	GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\TestSheet\\Skul.png", Vector2(153, 305), 60, 39, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
	GetComponent<Animator>()->InputClipData("Attack", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\TestSheet\\Skul.png", Vector2(219, 305), 40, 34, Vector2(0.5f, 0.5f), 0.2f, 1.0f));
	GetComponent<Animator>()->CreateAnimClip("Dash");
	GetComponent<Animator>()->InputClipData("Dash", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(10, 5315), 144, 136, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dash", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(160, 5315), 144, 136, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->CreateAnimClip("Hit");
	GetComponent<Animator>()->InputClipData("Hit", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(11, 4921), 162, 177, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->CreateAnimClip("Dead");
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(11, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(226, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(441, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(656, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(871, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(1086, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(1301, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));
	GetComponent<Animator>()->InputClipData("Dead", GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\CharacterSheet\\Bell_Sprite.png", Vector2(1516, 5121), 215, 172, Vector2(0.5f, 0.5f), 0.15f, 1.0f));*/
	//AddComponent<SavePoint>();
	//GetScriptComponent<SavePoint>()->SetPlayer(this);
	SetCameraView(true);
	AddComponent<Text>();
	AddComponent<B3_11>();
	GetScriptComponent<B3_11>()->SetDashExist(GET_SINGLE(UIManager)->GetIsDash());
	GetScriptComponent<B3_11>()->SetChargeExist(GET_SINGLE(UIManager)->GetIsCharge());
	GetScriptComponent<B3_11>()->SetCurHp(GET_SINGLE(UIManager)->GetPlayerHp());

	// PlayerHeadTrigger
	//todo : ø©±‚ ∏∑æ∆µ“
	/*GameObject* playerHeadTriggerObj = new GameObject(TAG::HeadTrigger);
	playerHeadTriggerObj->SetName("PlayerHeadTrigger");
	playerHeadTriggerObj->AddComponent<Transform>();
	playerHeadTriggerObj->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
	playerHeadTriggerObj->AddComponent<BoxCollider>();
	playerHeadTriggerObj->GetComponent<BoxCollider>()->SetWH(100, 180);
	playerHeadTriggerObj->GetComponent<Transform>()->SetLocalPosition(Vector2(0, -50));
	playerHeadTriggerObj->GetComponent<BoxCollider>()->SetTrigger(true);
	playerHeadTriggerObj->AddComponent<PlayerHeadTrigger>();
	playerHeadTriggerObj->GetScriptComponent<PlayerHeadTrigger>()->SetPlayerTrigger(this);*/

	//GET_SINGLE(UIManager)->SetPlayer(this->GetScriptComponent<Player>());//ø©±‚ ¿·±Ò ∏∑æ∆µ“
}

B3_11Prefab::~B3_11Prefab()
{
}
