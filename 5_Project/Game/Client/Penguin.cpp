#include "pch.h"
#include "Penguin.h"
#include "JW2DEngine.h"
#include "Text.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "State.h"
#include "UIManager.h"
#include "B3_11.h"
#include "PENGUIN_WALK.h"
#include "PENGUIN_RUN.h"
#include "PENGUIN_ATTACK.h"
#include "PENGUIN_HIT.h"
#include "PENGUIN_GAME_OVER.h"

Penguin::Penguin(GameObject* gameObject)
	:MonoBehaviour(gameObject),
#pragma region Penguin_INIT
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_rigidbody(gameObject->GetComponent<Rigidbody>()),
	_defaultLinearDragX(0.08f),
	_defaultLinearDragY(0.08f),
	_defaultGravityScale(10.f),
	_animator(gameObject->GetComponent<Animator>()),
	_boxCollider(gameObject->GetComponent<BoxCollider>()),

	_maxHp(3),
	_hp(3),
	_speed(90.f),
	_runSpeed(180.f),
	_attackSpeed(200.f),
	_knockBackPower(40.f),
	_dist(0.f),
	_hittedDmg(0.f),
	_attackCoolTime(0.f),
	_h(1),
	_moveTimer(0.f),
	_face(1),
	_deadDelay(0.f),

	_currentState(nullptr),
	_oldState(WALK),
	_newState(_oldState),
	_states{},

	_text(nullptr),
	_moveSoundDelay(0.f)
#pragma endregion
{
	_text = new Text(_gameObject);
	_text->SetStride({ 0,-100 });

	_rigidbody->SetLinearDragX(_defaultLinearDragX);
	_rigidbody->SetLinearDragY(_defaultLinearDragY);
	_rigidbody->SetGravityScale(_defaultGravityScale);

	//스테이트 생성
	//todo : 첫 시작 STATE WALK로
	_states[WALK] = new PENGUIN_WALK(this);
	_states[RUN] = new PENGUIN_RUN(this);
	_states[ATTACK] = new PENGUIN_ATTACK(this);
	_states[HIT] = new PENGUIN_HIT(this);
	_states[GAME_OVER] = new PENGUIN_GAME_OVER(this);

	_currentState = _states[_oldState];
	_currentState->Start();
}

Penguin::~Penguin()
{
	//스테이트 소멸
	for (auto statePair : _states)
	{
		delete statePair.second;
	}
}

void Penguin::VisualizeState()
{
	switch (_newState)
	{
	case WALK:
		_text->text = "WALK";
		break;
	case RUN:
		_text->text = "RUN";
		break;
	case ATTACK:
		_text->text = "ATTACK";
		break;
	case HIT:
		_text->text = "HIT";
		break;
	case GAME_OVER:
		_text->text = "GAME_OVER";
		break;
	default:
		break;
	}
}

void Penguin::PreProcess()
{}

void Penguin::OnCollisionEnter(ColliderBase* collider)
{
}

void Penguin::OnCollisionStay(ColliderBase* collider)
{
}

void Penguin::OnCollisionExit(ColliderBase* collider)
{
}

void Penguin::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet) && !_isHit)
	{
		_hittedDmg = collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet();
		_isHit = true;
	}
}

void Penguin::OnTriggerStay(ColliderBase* collider)
{
}

void Penguin::OnTriggerExit(ColliderBase* collider)
{
}

void Penguin::FixedUpdate()
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

	if (_hp <= 0)
	{
		_isDead = true;
	}

	if (!_isDead)
	{
		_attackCoolTime += DELTA_TIME;

		_dist = _transform->GetLocalPosition().Distance(_transform->GetLocalPosition(), _playerTransform->GetLocalPosition());

		if (_dist > 300.f && _dist <= 800.f)
		{
			_isInAtkDetect = false;
			_isInDetect = true;
		}
		else if (_dist <= 300.f)
		{
			_isInDetect = false;
			_isInAtkDetect = true;
		}
		else if (_dist > 800.f)
		{
			_isInDetect = false;
			_isInAtkDetect = false;
		}

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

void Penguin::Update()
{
	_currentState->Update();
	//_text->FinalUpdate();
}

void Penguin::FinalUpdate()
{
	if (SCENE_MANAGER->isDebug)
	{
		Matrix textMatrix = _transform->GetWorldMatrix();

		if (_face == -1)
		{
			Matrix matScale = Matrix::Identity();
			matScale._11 = -1;
			matScale._22 = 1;
			textMatrix = matScale * textMatrix;
		}

		textMatrix.dy -= 120.f;

		GEngine->SetTransform(textMatrix);

		// 여기서 string -> const char* 로 변환해서 넣어주는걸로 하였다..!
		const char* transText = _text->text.c_str();

		GEngine->DrawTextScreen(0, 0,
			300.f, 100.f, 0, transText);
	}
}
