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

	//������Ʈ ����
	//todo : ù ���� STATE FALL��
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
	//������Ʈ �Ҹ�
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

//todo : ���ǵ� �� ������ �ϰ�
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
		_bJumpKeyPressed = INPUT->GetButton(KEY_TYPE::SPACE);//���� �ٿ��̶�, ���� ������ ���� ���� �� ��
		_bAttackKeyPressed = INPUT->GetButton(KEY_TYPE::CTRL);
		_bDashKeyPressed =  (INPUT->GetButtonDown(KEY_TYPE::SHIFT) &&( _hasDash || SCENE_MANAGER->isTutorialScene()));
	}


	{
		if (_attackCoolTimer < _attackCoolTime)//��Ÿ���� ��á����
			_attackCoolTimer += DELTA_TIME;//ä���
		else//��Ÿ���� ä��������
			_chargable = true;//������ �����ϰ� �Ѵ�.


		if (_chargable && _bAttackKeyPressed)//������ ������ �� ������ ������
		{

			_chargeTimer += DELTA_TIME;//������ �ϰ�
			_shootable = true;//��� �ִ� ���·� �����.
			_isAttacking = true;//���� ��� ������ ����
		}


		if (_chargeTimer > _chargeTime && (_hasCharge || SCENE_MANAGER->isTutorialScene()))//������ ������ �ð� ��ŭ �Ǹ�
		{
			_chargeLevel = _chargeLevel < _maxChargeLevel ? _chargeLevel + 1 : _chargeLevel;//���������� �ø���
			_chargeTimer = 0.0f;//����Ÿ���� �ʱ�ȭ �����ش�.
		}


		if (_shootable && !_bAttackKeyPressed)//�� �� �ִ� ������ �� ����Ű�� �ôٸ�
		{

			SOUND_MANAGER->PlayerAttack();
			_attackCoolTimer = 0.0f;//���� ������ �����ϰ�
			_chargable = false; //������ �������� ���ϰ� �ϰ�
			_chargeTimer = 0.0f;//���� �ð��� ���½�Ű��
			_shootable = false;//��� ���� ����
			_followTimerAddable = true;//��� ���� ������� �ɸ��� �ð��� ���� �����Ѵ�.


			if (_chargeLevel < 3)//���������� üũ �ƽ� ������ �ƴ϶��
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
			_chargeLevel = 0;//�������� 0����
		}


		if (_followTimerAddable)
			_attackFollowThoroughTimer += DELTA_TIME;

		if (_attackFollowThoroughTimer >= _attackFollowThoroughTime)
		{

			_chargable = false; //������ ������ �� �ְ��ϰ�
			_chargeLevel = 0;//�������� 0����
			_attackFollowThoroughTimer = 0.0f;
			_followTimerAddable = false;
			_isAttacking = false;
		}
	}


		if (_bHit || _isDashing)
		{
			_chargable = false; //������ �������� ���ϰ� �ϰ�
			_chargeTimer = 0.0f;//���� �ð��� ���½�Ű��
			_chargeLevel = 0;//�������� 0����
			_shootable = false;//��� ���� ���·� �����
			_attackFollowThoroughTimer = 0.0f;
			_followTimerAddable = false;
			_isAttacking = false;
		}



	if (_dashCoolTimer < _dashCoolTime)//�뽬 ���� ��á�ٸ�
		_dashCoolTimer += DELTA_TIME;//�뽬 ���� ä���ְ�

	if (_dashCoolTimer >= _dashCoolTime)//�뽬 �� Ÿ���� á�ٸ�
		_isDashable = true;//�뽬�� �� �� �ִ� ���·� �����

	if (_isDashable && _bDashKeyPressed)//�뽬 ��Ÿ���� ä�������� �뽬 ��ư�� ������
		_isDashing = true;//�뽬���·� �����ϰ� �Ѵ�.

	if (_bCheckGround && _bJumpKeyDown ||
		_bOnWall && _bJumpKeyDown)
		_bJumpEntry = true;
	


	/*
	 ���� ���� �� �ٲ��� ��
	 _attackStateEnd = false
	 ���� ��Ÿ�� 0����
	 _shootable = false;
	*/
	//_currentState Change
	/*
		1. ������Ʈ�� ������Ʈ �Ѵ�.
		2. ������Ʈ�� �ٲ���ٸ�,
		�ٲ�� �� ������Ʈ ������Ʈ�� ���� �ʰ�
		���� ������Ʈ�� �����Ѵ�.
		3. �� �ٲ�ٸ� �ٲ�� ������ ���ش�.
	*/

	//todo: �� ���Խ� x�� Velocity 0����


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
		_currentState->End();//���� ������Ʈ ������ �� ����
		_currentState = _states[_newState];//�ٲ㳢���ְ�
 	 	_currentState->Start();//���ο� ������Ʈ ���� ����
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

		// ���⼭ string -> const char* �� ��ȯ�ؼ� �־��ִ°ɷ� �Ͽ���..!
		const char* transText = _text->text.c_str();

		GEngine->DrawTextScreen(0, 0,
			300.f, 100.f, 0, transText);
	}
}
