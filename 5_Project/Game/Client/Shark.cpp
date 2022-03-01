#include "pch.h"
#include "Shark.h"
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
#include "Bullet.h"
#include "SHARK_WALK.h"
#include "SHARK_RUN.h"
#include "SHARK_ATTACK.h"
#include "SHARK_HIT.h"
#include "SHARK_GAME_OVER.h"

Shark::Shark(GameObject* gameObject)
	:MonoBehaviour(gameObject),
#pragma region SHARK_INIT
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
	_speed(70.f),
	_knockBackPower(40.f),
	_attackCoolTime(0.f),
	_dist(0.f),
	_hittedDmg(0.f),
	_h(1), _v(1),
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

	//������Ʈ ����
	//todo : ù ���� STATE WALK��
	_states[WALK] = new SHARK_WALK(this);
	_states[RUN] = new SHARK_RUN(this);
	_states[ATTACK] = new SHARK_ATTACK(this);
	_states[HIT] = new SHARK_HIT(this);
	_states[GAME_OVER] = new SHARK_GAME_OVER(this);

	_currentState = _states[_oldState];
	_currentState->Start();
}

Shark::~Shark()
{
	//������Ʈ �Ҹ�
	for (auto statePair : _states)
	{
		delete statePair.second;
	}
}

void Shark::VisualizeState()
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

void Shark::PreProcess()
{}

void Shark::OnCollisionEnter(ColliderBase* collider)
{
}

void Shark::OnCollisionStay(ColliderBase* collider)
{
}

void Shark::OnCollisionExit(ColliderBase* collider)
{
}

void Shark::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Bullet) && !_isHit)
	{
		_hittedDmg = collider->GetGameObject()->GetScriptComponent<Bullet>()->GetDamageBullet();
		_isHit = true;
	}
}

void Shark::OnTriggerStay(ColliderBase* collider)
{
}

void Shark::OnTriggerExit(ColliderBase* collider)
{
}

void Shark::FixedUpdate()
{
	//condition check
	{
		// _face = _input == 0 ? _face : _input;
	}

	//_currentState Change
	/*
		1. ������Ʈ�� ������Ʈ �Ѵ�.
		2. ������Ʈ�� �ٲ���ٸ�,
		�ٲ�� �� ������Ʈ ������Ʈ�� ���� �ʰ�
		���� ������Ʈ�� �����Ѵ�.
		3. �� �ٲ�ٸ� �ٲ�� ������ ���ش�.
	*/


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
	
	_newState = _currentState->FixedUpdate();

	while (_newState != _oldState)
	{
		_currentState->End();//���� ������Ʈ ������ �� ����
		_currentState = _states[_newState];//�ٲ㳢���ְ�
		_currentState->Start();//���ο� ������Ʈ ���� ����
		_oldState = _newState;
		_newState = _currentState->FixedUpdate();
	}

	VisualizeState();
}

void Shark::Update()
{
	_currentState->Update();
	//_text->FinalUpdate();
}

void Shark::FinalUpdate()
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

		// ���⼭ string -> const char* �� ��ȯ�ؼ� �־��ִ°ɷ� �Ͽ���..!
		const char* transText = _text->text.c_str();

		GEngine->DrawTextScreen(0, 0,
			300.f, 100.f, 0, transText);
	}
}

