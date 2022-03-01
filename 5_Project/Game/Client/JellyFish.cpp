#include "pch.h"
#include "JellyFish.h"
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
#include "JELLYFISH_WALK.h"
#include "JELLYFISH_HIT.h"
#include "JELLYFISH_GAME_OVER.h"

JellyFish::JellyFish(GameObject* gameObject)
	:MonoBehaviour(gameObject),
#pragma region JellyFish_INIT
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_rigidbody(gameObject->GetComponent<Rigidbody>()),
	_defaultLinearDragX(0.08f),
	_defaultLinearDragY(0.08f),
	_defaultGravityScale(0.f),
	_animator(gameObject->GetComponent<Animator>()),
	_boxCollider(gameObject->GetComponent<BoxCollider>()),

	_maxHp(3),
	_hp(3),
	_speed(60.f),
	_knockBackPower(40.f),
	_dist(0.f),
	_hittedDmg(0.f),
	_h(3),
	_moveTimer(0.f),
	_face(1),

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
	_states[WALK] = new JELLYFISH_WALK(this);
	_states[HIT] = new JELLYFISH_HIT(this);
	_states[GAME_OVER] = new JELLYFISH_GAME_OVER(this);

	_currentState = _states[_oldState];
	_currentState->Start();
}

JellyFish::~JellyFish()
{
	//스테이트 소멸
	for (auto statePair : _states)
	{
		delete statePair.second;
	}
}

void JellyFish::VisualizeState()
{
	switch (_newState)
	{
	case WALK:
		_text->text = "WALK";
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

void JellyFish::PreProcess()
{}

void JellyFish::OnCollisionEnter(ColliderBase* collider)
{
}

void JellyFish::OnCollisionStay(ColliderBase* collider)
{
}

void JellyFish::OnCollisionExit(ColliderBase* collider)
{
}

void JellyFish::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet) && !_isHit)
	{
		_hittedDmg = collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet();
		_isHit = true;
	}
}

void JellyFish::OnTriggerStay(ColliderBase* collider)
{
}

void JellyFish::OnTriggerExit(ColliderBase* collider)
{
}

void JellyFish::FixedUpdate()
{
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

void JellyFish::Update()
{
	_currentState->Update();
	//_text->FinalUpdate();
}

void JellyFish::FinalUpdate()
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
