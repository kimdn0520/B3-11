#include "pch.h"
#include "State.h"
#include "Boss.h"
#include "JW2DEngine.h"
#include "Text.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "UIManager.h"
#include "BOSS_IDLE.h"
#include "BOSS_HORIZONTAL_ATTACK.h"
#include "BOSS_VERTICAL_ATTACK.h"
#include "BOSS_ENEMY_SUMMON.h"
#include "BOSS_HIT.h"
#include "BOSS_GAME_OVER.h"
#include "UIManager.h"


Boss::Boss(GameObject* gameObject)
	:MonoBehaviour(gameObject),
#pragma region BOSS_INIT
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_rigidbody(gameObject->GetComponent<Rigidbody>()),
	_animator(gameObject->GetComponent<Animator>()),
	_circleCollider(gameObject->GetComponent<CircleCollider>()),

	_maxHp(30),
	_hp(30),
	_power(1.f),
	_attackCoolTime(0.f),

	_currentState(nullptr),
	_oldState(IDLE),
	_newState(_oldState),
	_states{},

	_text(nullptr),
	_soundDelay(0.f)
#pragma endregion
{
	_text = new Text(_gameObject);
	_text->SetStride({ 0, -900 });

	//스테이트 생성
	//todo : 첫 시작 STATE IDLE로
	_states[IDLE] = new BOSS_IDLE(this);
	_states[HORIZONTAL_ATTACK] = new BOSS_HORIZONTAL_ATTACK(this);
	_states[VERTICALL_ATTACK] = new BOSS_VERTICAL_ATTACK(this);
	_states[ENEMY_SUMMON] = new BOSS_ENEMY_SUMMON(this);
	_states[HIT] = new BOSS_HIT(this);
	_states[GAME_OVER] = new BOSS_GAME_OVER(this);

	_currentState = _states[_oldState];
	_currentState->Start();
}

Boss::~Boss()
{
	//스테이트 소멸
	for (auto statePair : _states)
	{
		delete statePair.second;
	}
}

void Boss::VisualizeState()
{
	switch (_newState)
	{
		case IDLE:
			_text->text = "IDLE";
			break;
		case HORIZONTAL_ATTACK:
			_text->text = "HORIZONTAL_ATTACK";
			break;
		case VERTICALL_ATTACK:
			_text->text = "VERTICALL_ATTACK";
			break;
		case ENEMY_SUMMON:
			_text->text = "ENEMY_SUMMON";
			break;
		case HIT:
			_text->text = "HIT";
		case GAME_OVER:
			_text->text = "GAME_OVER";
			break;
		default:
			break;
	}
}

void Boss::PreProcess()
{}

void Boss::OnCollisionEnter(ColliderBase* collider)
{
}

void Boss::OnCollisionStay(ColliderBase* collider)
{
}

void Boss::OnCollisionExit(ColliderBase* collider)
{
}

void Boss::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet) && !_isHit)
	{
		_hittedDmg = collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet();
		_isHit = true;
	}
}

void Boss::OnTriggerStay(ColliderBase* collider)
{
}

void Boss::OnTriggerExit(ColliderBase* collider)
{
}

void Boss::FixedUpdate()
{	
	//condition check
	{
		// _face = _input == 0 ? _face : _input;
	}

	//_currentState Change
	/*
		1. 스테이트를 업데이트 한다.
		2. 스테이트가 바뀌었다면,
		바뀌기 전 스테이트 업데이트를 하지 않고
		다음 스테이트를 설정한다.
		3. 또 바뀐다면 바뀌기 전까지 해준다.
	*/

	if (GET_SINGLE(UIManager)->GetIsGameOver())
	{
		SCENE_MANAGER->SetIsReservedTimeControl(true);
	}

	_newState = _currentState->FixedUpdate();

	while (_newState != _oldState)
	{
		_currentState->End();//이전 스테이트 꺼지기 전 동작
		_currentState = _states[_newState];//바꿔끼워주고
		_currentState->Start();//새로운 스테이트 시작 동작
		_oldState = _newState;
		_newState = _currentState->FixedUpdate();
	}

	VisualizeState();
}

void Boss::Update()
{
	_currentState->Update();

	//if (GET_SINGLE(UIManager)->_isDebug)
	//_text->FinalUpdate();
}

void Boss::FinalUpdate()
{
	if (SCENE_MANAGER->isDebug)
	{
		Matrix textMatrix = _transform->GetWorldMatrix();

		textMatrix.dy -= 400.f;

		GEngine->SetTransform(textMatrix);

		// 여기서 string -> const char* 로 변환해서 넣어주는걸로 하였다..!
		const char* transText = _text->text.c_str();

		GEngine->DrawTextScreen(0, 0,
			500.f, 100.f, 0, transText);
	}
}
