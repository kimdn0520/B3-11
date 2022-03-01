#include "pch.h"
#include "Input.h"
#include "JW2DEngine.h"
#include "Text.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "ColliderBase.h"
#include "BoxCollider.h"
#include "FadeIn.h"
#include "State.h"
#include "UIManager.h"
#include "B3_11.h"
#include "STATE_B3_11_IDLE.h"
#include "STATE_B3_11_IDLE_ATTACK.h"
#include "STATE_B3_11_WALK.h"
#include "STATE_B3_11_WALK_ATTACK.h"
#include "STATE_B3_11_JUMP.h"
#include "STATE_B3_11_JUMP_ATTACK.h"
#include "STATE_B3_11_FALL.h"
#include "STATE_B3_11_FALL_ATTACK.h"
#include "STATE_B3_11_WALL.h"
#include "STATE_B3_11_WALL_ATTACK.h"
#include "STATE_B3_11_DASH.h"
#include "STATE_B3_11_HIT.h"
#include "STATE_B3_11_GAME_OVER.h"
#include "Portal.h"
#include "PortalPrefab.h"
#include "SavePoint.h"
#include "SavePointPrefab.h"
#include "BulletPrefab.h"

B3_11::B3_11(GameObject* gameObject)
	:MonoBehaviour(gameObject),
#pragma region B3_11_INIT
	_gameObject(gameObject),
	_transform(gameObject->GetComponent<Transform>()),
	_rigidbody(gameObject->GetComponent<Rigidbody>()),
	_defaultLinearDragX(0.08f),
	_defaultLinearDragY(0.08f),
	_defaultGravityScale(10.0f),
	_animator(gameObject->GetComponent<Animator>()),
	_boxCollider(gameObject->GetComponent<BoxCollider>()),

	_bullet(nullptr),

	_maxHp(3),
	_hp(3),
	_maxChargeLevel(3),
	_chargeLevel(0),
	_speed(70.f),

	_jumpPower(35.0f),
	_wallJumpPower(35.f),
	_power{},
	_knockBackPower(40.f),
	_dashPower(50.f),
	_face(1),

	_hasDash(false),
	_hasCharge(false),
	_bOnWall(false),


	_input(0),
	_wallSide{},
	_groundWay{},
	_bJumpKeyPressed(false),
	_bAttackKeyPressed(false),
	_bDashKeyPressed(false),
	_bCheckGround(false),
	_bCheckWall(false),
	_bHit(false),
	_shootWay(1),

	_wallEscapeTimer(0.0f),
	_hitTimer(0.f),
	_dashCoolTimer(1.5f),
	_dashCoolTime(1.5f),
	_dashTimer(0.f),
	_jumpTimer(0.f),

	_jumpTime(0.25f),
	_wallEscapeTime(0.2f),
	_recoveryTime(0.5f),
	_dashTime(0.3f),

	_isAttacking(false),
	_chargable(true),
	_shootable(false),
	_followTimerAddable(false),
	_bJumpEntry(false),

	_attackFollowThoroughTimer(0.0f),
	_attackFollowThoroughTime(0.3f),

	_attackCoolTimer(0.0f),

	_attackCoolTime(0.3f),

	_chargeTimer(0.0f),
	_chargeTime(0.75f),

	_isDashable(true),
	_isDashing(false),

	_invincible(false),
	_invincibleTime(2.0f),
	_invincibleTimer(_invincibleTime),

	_chargeSound(false),

	_walkSoundTimer(0.f),
	_walkSoundCoolTime(0.5f),

	_jumpForceAddable(false),

	_currentState(nullptr),
	_oldState(FALL),
	_newState(_oldState),
	_states{},

	_text(nullptr),
	_moveSoundDelay(0.f),
	_fadeInObj(nullptr)
#pragma endregion
{	
	_power[0] = 1;
	_power[1] = 1;
	_power[2] = 3;

	_text = new Text(_gameObject);
	_text->SetStride({ 0,-100 });
	

	_rigidbody->SetLinearDragX(_defaultLinearDragX);
	_rigidbody->SetLinearDragY(_defaultLinearDragY);
	_rigidbody->SetGravityScale(_defaultGravityScale);

	//스테이트 생성
	//todo : 첫 시작 STATE FALL로
	_states[IDLE] = new STATE_B3_11_IDLE(this);
	_states[IDLE_ATTACK] = new STATE_B3_11_IDLE_ATTACK(this);
	_states[WALK] = new STATE_B3_11_WALK(this);
	_states[WALK_ATTACK] = new STATE_B3_11_WALK_ATTACK(this);
	_states[JUMP] = new STATE_B3_11_JUMP(this);
	_states[JUMP_ATTACK] = new STATE_B3_11_JUMP_ATTACK(this);
	_states[FALL] = new STATE_B3_11_FALL(this);
	_states[FALL_ATTACK] = new STATE_B3_11_FALL_ATTACK(this);
	_states[WALL] = new STATE_B3_11_WALL(this);
	_states[WALL_ATTACK] = new STATE_B3_11_WALL_ATTACK(this);
	_states[DASH] = new STATE_B3_11_DASH(this);
	_states[HIT] = new STATE_B3_11_HIT(this);
	_states[GAME_OVER] = new STATE_B3_11_GAME_OVER(this);

	_currentState = _states[_oldState];
	_currentState->Start();
}

B3_11::~B3_11()
{
	//스테이트 소멸
	for (auto statePair : _states)
	{
		delete statePair.second;
	}
}

void B3_11::VisualizeState()
{
	switch (_newState)
	{
	case IDLE:
		_text->text = "IDLE";
		OutputDebugString("IDLE \n");
		break;
	case IDLE_ATTACK:
		_text->text = "IDLE_ATTACK";
		break;
	case WALK:
		_text->text = "WALK";
		OutputDebugString("WALK \n");
		break;
	case WALK_ATTACK:
		_text->text = "WALK_ATTACK";
		break;
	case JUMP:
		_text->text = "JUMP";
		break;
	case JUMP_ATTACK:
		_text->text = "JUMP_ATTACK";
		break;
	case FALL:
		_text->text = "FALL";
		OutputDebugString("FALL \n");
		break;
	case FALL_ATTACK:
		_text->text = "FALL_ATTACK";
		break;
	case WALL:
		_text->text = "WALL";
		OutputDebugString("WALL \n");
		break;
	case WALL_ATTACK:
		_text->text = "WALL_ATTACK";
		break;
	case DASH:
		_text->text = "DASH";
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

void B3_11::PreProcess()
{
	_bCheckGround = false;
	_bCheckWall = false;
	_bHit = false;

	_wallSide[0] =false;
	_wallSide[1] = false;

	_groundWay[0] = false;
	_groundWay[1] = false;
	_groundWay[2] = false;
	_groundWay[3] = false;
}

void B3_11::OnCollisionEnter(ColliderBase* collider)
{
	//condition Check
	{
		if (collider->CompareTag(TAG::Ground) ||
			collider->CompareTag(TAG::MovableGround) ||
			collider->CompareTag(TAG::GetThroughGround))
		{
			for (int i = 0; i < 4; i++)
			{
				if (_boxCollider->GetColDirVec()[i])
				{
					_groundWay[i] = true;
				}
			}
		}

		if (!_bCheckGround)
			_bCheckGround = _groundWay[0];

		if (!_bCheckWall)
			_bCheckWall = (_groundWay[1] || _groundWay[2]);

	}
}

//todo : 조건들 더 디테일 하게
void B3_11::OnCollisionStay(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Ground) ||
		collider->CompareTag(TAG::MovableGround) ||

		collider->CompareTag(TAG::GetThroughGround) ||
		collider->CompareTag(TAG::BrokenWall))
	{
		for (int i = 0; i < 4; i++)
		{
			if (_boxCollider->GetColDirVec()[i])
			{
				_groundWay[i] = true;
			}
		}
	}

	if (!_bCheckGround)
		_bCheckGround = _groundWay[0];

	if (!_bCheckWall)
		_bCheckWall = (_groundWay[1] || _groundWay[2]);


	if (!_bHit)
	{
		_bHit = collider->CompareTag(TAG::Enemy);
		_knockBackDiagonal = (_boxCollider->GetTransform()->GetLocalPosition() - collider->GetTransform()->GetLocalPosition()).Normalized();
	}
}

void B3_11::OnCollisionExit(ColliderBase* collider)
{
	
}

void B3_11::OnTriggerEnter(ColliderBase* collider)
{
	if (collider->CompareTag(TAG::Portal) && _currentState != _states[GAME_OVER])
	{
		SCENE_MANAGER->SetPlayerPos(collider->GetGameObject()->GetScriptComponent<Portal>()->nextPlayerPos);
		SCENE_MANAGER->SetIsReservedTimeControl(true);
		_fadeInObj->GetScriptComponent<FadeIn>()->SetLoadSceneName(collider->GetGameObject()->GetName());
		_fadeInObj->SetActive(true);
		GET_SINGLE(UIManager)->ResetUIVector();
	}

	else if (collider->CompareTag(TAG::Item))
	{
		if (collider->GetGameObject()->GetName() == "Dash")
			_hasDash = true;
		else if (collider->GetGameObject()->GetName() == "Charge")
			_hasCharge = true;
	}
	else if ((collider->GetGameObject()->GetName() == "fallGround") && !_bHit)
	{
		_hp--;
		_transform->SetLocalPosition( {2.5 * 128.f, 45 * 128.f} );
		if (_hp == 0)
			_bHit = true;
	}

	else if(collider->GetGameObject()->GetName() == "Saw")
		_bHit = true;
}

void B3_11::OnTriggerStay(ColliderBase* collider)
{
	if (collider->GetGameObject()->GetName() == "SavePoint")
	{
		if (INPUT->GetButtonDown(KEY_TYPE::UP))
		{
		
			collider->GetGameObject()->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Save_Point_Saving (256_256).png", Vector2(0, 0), 256.f, 256.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
			
			_animator->StopRender();
			
			_rigidbody->SetLinearDragX(1.f);
			_rigidbody->SetLinearDragY(1.f);
			
			_hp = _maxHp;
			
			SCENE_MANAGER->SetSavePoint(collider->GetGameObject()->GetScriptComponent<SavePoint>()->savePoint);
			SCENE_MANAGER->SetPlayerPos(_boxCollider->GetTransform()->GetLocalPosition());
		}
		else if (INPUT->GetButtonDown(KEY_TYPE::DOWN))
		{
			collider->GetGameObject()->GetComponent<SpriteRenderer>()->SetSprite(GEngine->LoadSpriteFromSheet(L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Save_Point_Saved (256_256).png", Vector2(0, 0), 256.f, 256.f, Vector2(0.5f, 0.5f), 0.f, 1.0f));
			
			_rigidbody->SetLinearDragX(_defaultLinearDragX);
			_rigidbody->SetLinearDragY(_defaultLinearDragY);

			_animator->ResumeRender();
		}
	}

}

void B3_11::OnTriggerExit(ColliderBase* collider)
{
}

void B3_11::FixedUpdate()
{
	if (INPUT->GetButtonDown(KEY_TYPE::F2))
		_hasDash = !_hasDash;
	if (INPUT->GetButtonDown(KEY_TYPE::F3))
		_hasCharge = !_hasCharge;

	if (_groundWay[0] || _groundWay[3] || _bCheckGround)
		_rigidbody->SetVelocityY(0);

	if (_groundWay[1] || _groundWay[2])
		_rigidbody->SetVelocityX(0);

	//condition check
	{
		_input = INPUT->GetAxisRawHorizontal();
		_face = _input == 0 ? _face : _input;

		_bJumpKeyDown = INPUT->GetButtonDown(KEY_TYPE::SPACE);
		_bJumpKeyPressed = INPUT->GetButton(KEY_TYPE::SPACE);//점프 다운이랑, 점프 프레스 따로 관리 할 것
		_bAttackKeyPressed = INPUT->GetButton(KEY_TYPE::CTRL);
		_bDashKeyPressed =  (INPUT->GetButtonDown(KEY_TYPE::SHIFT) &&( _hasDash || SCENE_MANAGER->isTutorialScene()));
	}


	{
		if (_attackCoolTimer < _attackCoolTime)//쿨타임이 안찼으면
			_attackCoolTimer += DELTA_TIME;//채운다
		else//쿨타임이 채워졌으면
			_chargable = true;//공격이 가능하게 한다.


		if (_chargable && _bAttackKeyPressed)//충전이 가능할 때 누르고 있으면
		{

			_chargeTimer += DELTA_TIME;//차지를 하고
			_shootable = true;//쏠수 있는 상태로 만든다.
			_isAttacking = true;//공격 모션 나가는 기준
		}


		if (_chargeTimer > _chargeTime && (_hasCharge || SCENE_MANAGER->isTutorialScene()))//차지가 정해진 시간 만큼 되면
		{
			_chargeLevel = _chargeLevel < _maxChargeLevel ? _chargeLevel + 1 : _chargeLevel;//차지레벨을 올리고
			_chargeTimer = 0.0f;//차지타임을 초기화 시켜준다.
		}


		if (_shootable && !_bAttackKeyPressed)//쏠 수 있는 상태일 때 공격키를 뗐다면
		{

			SOUND_MANAGER->PlayerAttack();
			_attackCoolTimer = 0.0f;//쿨을 돌리기 시작하고
			_chargable = false; //충전을 시작하지 못하게 하고
			_chargeTimer = 0.0f;//차지 시간을 리셋시키고
			_shootable = false;//쏠수 없는 상태
			_followTimerAddable = true;//쏘고 상태 변경까지 걸리는 시간을 세기 시작한다.


			if (_chargeLevel < 3)//차지레벨을 체크 맥스 차지가 아니라면
			{

				//_bullet = GET_SINGLE(ObjectPool)->SpawnFromPool("BulletPrefab", _transform->GetLocalPosition());

				if (_gameObject != nullptr)
				{
					GameObject* bullet = new BulletPrefab();
					Instantiate(bullet, _transform->GetLocalPosition());
					bullet->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2(_face * _shootWay, 0), _transform);
					bullet->GetComponent<Transform>()->SetLocalScale(Vector2(_face * _shootWay, bullet->GetComponent<Transform>()->GetLocalScale().y));
					bullet->GetScriptComponent<Bullet>()->SetDamageBullet(_power[1]);
					bullet->GetComponent<Animator>()->Play(AnimClipLoader::LoadClip(AnimClipPath("NormalAttack")));
				}
			}
			else
			{
				GameObject* bullet = new BulletPrefab();
				Instantiate(bullet, _transform->GetLocalPosition());
				bullet->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2(_face * _shootWay, 0), _transform);
				bullet->GetComponent<Transform>()->SetLocalScale(Vector2(_face * _shootWay, bullet->GetComponent<Transform>()->GetLocalScale().y));

				bullet->GetScriptComponent<Bullet>()->SetDamageBullet(_power[2]);
				bullet->GetComponent<Animator>()->Play(AnimClipLoader::LoadClip(AnimClipPath("ChargeBulletAnim")));
			}
			_chargeLevel = 0;//차지레벨 0으로
		}


		if (_followTimerAddable)
			_attackFollowThoroughTimer += DELTA_TIME;

		if (_attackFollowThoroughTimer >= _attackFollowThoroughTime)
		{

			_chargable = false; //충전을 시작할 수 있게하고
			_chargeLevel = 0;//차지레벨 0으로
			_attackFollowThoroughTimer = 0.0f;
			_followTimerAddable = false;
			_isAttacking = false;
		}
	}


		if (_bHit || _isDashing)
		{
			_chargable = false; //충전을 시작하지 못하게 하고
			_chargeTimer = 0.0f;//차지 시간을 리셋시키고
			_chargeLevel = 0;//차지레벨 0으로
			_shootable = false;//쏠수 없는 상태로 만들고
			_attackFollowThoroughTimer = 0.0f;
			_followTimerAddable = false;
			_isAttacking = false;
		}



	if (_dashCoolTimer < _dashCoolTime)//대쉬 쿨이 안찼다면
		_dashCoolTimer += DELTA_TIME;//대쉬 쿨을 채워주고

	if (_dashCoolTimer >= _dashCoolTime)//대쉬 쿨 타임이 찼다면
		_isDashable = true;//대쉬를 할 수 있는 상태로 만들고

	if (_isDashable && _bDashKeyPressed)//대쉬 쿨타임이 채워졌을때 대쉬 버튼을 누르면
		_isDashing = true;//대쉬상태로 진입하게 한다.

	if (_bCheckGround && _bJumpKeyDown ||
		_bOnWall && _bJumpKeyDown)
		_bJumpEntry = true;
	


	/*
	 공격 끝날 때 바꿔줄 것
	 _attackStateEnd = false
	 공격 쿨타임 0으로
	 _shootable = false;
	*/
	//_currentState Change
	/*
		1. 스테이트를 업데이트 한다.
		2. 스테이트가 바뀌었다면,
		바뀌기 전 스테이트 업데이트를 하지 않고
		다음 스테이트를 설정한다.
		3. 또 바뀐다면 바뀌기 전까지 해준다.
	*/

	//todo: 벽 진입시 x축 Velocity 0으로


	if (_invincible)
	{
		_animator->_isRender = !_animator->_isRender;
		_bHit = false;
		_invincibleTimer += DELTA_TIME;
	}

	if (_invincibleTimer >= _invincibleTime)
	{
		_animator->_isRender = true;
		_invincible = false;
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

void B3_11::Update()
{
	_currentState->Update();
}

void B3_11::FinalUpdate()
{
	if (SCENE_MANAGER->isDebug)
	{
		Matrix matScale = Matrix::Identity();
		matScale._11 = 1;
		matScale._22 = 1;

		Matrix matTranslate = Matrix::Identity();
		matTranslate.dx = _transform->GetWorldPosition().x;
		matTranslate.dy = _transform->GetWorldPosition().y;

		Matrix textMatrix = matScale * matTranslate;

		textMatrix.dy -= 120.f;

		GEngine->SetTransform(textMatrix);

		// 여기서 string -> const char* 로 변환해서 넣어주는걸로 하였다..!
		const char* transText = _text->text.c_str();

		GEngine->DrawTextScreen(0, 0,
			300.f, 100.f, 0, transText);
	}
}
