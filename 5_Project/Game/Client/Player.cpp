#include "pch.h"
//#include "Player.h"
//#include "Input.h"
//#include "Timer.h"
//#include "GameObject.h"
//#include "Transform.h"
//#include "Rigidbody.h"
//#include "Animator.h"
//#include "Text.h"
//#include "ColliderBase.h"
//#include "SceneManager.h"
//#include "SoundManager.h"
//#include "BulletPrefab.h"
//#include "BoxCollider.h"
//#include "Bullet.h"
//#include "Turtle.h"
//#include "ObjectPool.h"
//#include "EnemyController.h"
//#include "Hurdle.h"
//#include "BoxCollider.h"
//#include "MapLoader.h"
//#include "FadeIn.h"
//
//Player::Player(GameObject* gameObject)
//	: MonoBehaviour(gameObject),
//
//	_state(State::IDLE), _speed(70.f), _jumpPower(70.0f), _wallJumpPower(50.f), _isJumping(false), _h(0.f), _v(0.f), _hp(3), _power(10.f), _damage(1.f), _knockBackPower(70.f), _knockBackX(0.f), _knockBackY(0.f), _moveSoundDelay(0.f),
//	_isAttack(false), _isWallJumping(false), _scale(_transform->GetLocalScale()), _isDash(false), _isFlipped(false), _isDashEnd(false), _isAttackEnd(false), _isWallAttack(false),
//	_checkDashTime(0.f), _coolTime(3.f), _dash(35.f), _timer(0.f), _attackCoolTime(0.8f), _gameObject(nullptr), _isDashSkill(false), _isChargeSkill(false), _isInvincible(false),
//	_transform(gameObject->GetComponent<Transform>()),
//	_rigidbody(gameObject->GetComponent<Rigidbody>()),
//	_animator(gameObject->GetComponent<Animator>()),
//	_text(gameObject->GetComponent<Text>()),
//	_boxCollider(gameObject->GetComponent<BoxCollider>())
//{
//	_rigidbody->SetLinearDragX(0.5f);
//	_rigidbody->SetLinearDragY(0.08f);
//	_rigidbody->SetGravityScale(10.0f);
//}
//
//Player::~Player()
//{
//
//}
//
//void Player::FixedUpdate()
//{
//	Dash();
//	WallJump();
//	Jump();
//	Move();
//}
//
//void Player::Update()
//{
//	_isWallCheck = false;
//
//	Flipped();
//
//	Attack();
//
//	WallAttack();
//
//	AnimationUpdate();
//
//	InvincibleControl();
//}
//
//void Player::Move()
//{
//	_preHorizontal = _h;
//
//	_h = INPUT->GetAxisRawHorizontal();
//	// _v = INPUT->GetAxisRawVertical();
//	// SOUND_MANAGER->PlayerMove();
//
//	_moveDir = Vector2(_h, _v);
//
//	_rigidbody->AddForce(_moveDir * _speed * DELTA_TIME);
//
//	if (_h == 0)
//	{
//		if (!_isDashEnd)
//			_rigidbody->SetLinearDragX(1.0f);
//		else
//			_rigidbody->SetLinearDragX(0.08f);
//	}
//	else
//	{
//		_rigidbody->SetLinearDragX(0.08f);
//	}
//
//	if (INPUT->GetButton(KEY_TYPE::LEFT) || INPUT->GetButton(KEY_TYPE::RIGHT))
//	{
//		if (_rigidbody->GetVelocity().y == 0)
//		{
//			_moveSoundDelay += DELTA_TIME;
//			if (_moveSoundDelay >= 0.5f)
//			{
//				SOUND_MANAGER->PlayerMove();
//				_moveSoundDelay = 0;
//			}
//		}
//	}
//	//_transform->Translate(_moveDir.Normalized() * _speed * DELTA_TIME);
//	//_transform->SetLocalPosition(_transform->GetLocalPosition() + _moveDir * 10.f);
//}
//
//void Player::Attack()
//{
//	// CTRL버튼을 누르고 있을 때 시간을 체크해서 눌린 시간별로 공격력을 정해줌.
//	if (INPUT->GetButton(KEY_TYPE::CTRL) && !_isWallJumping && !_isAttack && _isChargeSkill && !_isWallAttack)
//	{
//		_checkAttackCharge += DELTA_TIME;
//
//		if (_checkAttackCharge <= 1.f)
//		{
//			OutputDebugString("공격1");
//			_power = 10.0f;
//		}
//		else if (_checkAttackCharge > 2.f)
//		{
//			OutputDebugString("공격2");
//			_power = 30.f;
//		}
//	}
//	// CTRL버튼을 땠을 때 저장 된 공격력을 지닌 총알을 오브젝트 풀에서 하나 생성한 다음 
//	// 플레이어가 바라보고 있는 방향으로 발사시킴
//	else if (INPUT->GetButtonUp(KEY_TYPE::CTRL) && !_isWallJumping && !_isAttack && !_isWallAttack)
//	{
//		//GET_SINGLE(ObjectPool<EnemyController>)->SpawnFromPool("TestEnemyPrefab", Vector2(600, 800));
//		if (!_isFlipped)
//		{
//			_gameObject = GET_SINGLE(ObjectPool)->SpawnFromPool("BulletPrefab", _transform->GetLocalPosition());
//
//			if (_gameObject != nullptr)
//			{
//				_gameObject->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2::Right, !_isFlipped, _transform, true);
//				_gameObject->GetScriptComponent<Bullet>()->SetDamageBullet(_power);
//				_gameObject = nullptr;
//			}
//		}
//		else if (_isFlipped)
//		{
//			_gameObject = GET_SINGLE(ObjectPool)->SpawnFromPool("BulletPrefab", _transform->GetLocalPosition());
//
//			if (_gameObject != nullptr)
//			{
//				_gameObject->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2::Left, _isFlipped, _transform, true);
//				_gameObject->GetScriptComponent<Bullet>()->SetDamageBullet(_power);
//				_gameObject = nullptr;
//			}
//		}
//		_isAttack = true;
//
//		_isAttackEnd = true;
//
//		_checkAttackCharge = 0;
//		SOUND_MANAGER->PlayerAttack();
//	}
//
//	// 공격키를 연속으로 누르지 못하게 하기 위해 
//	// _isAttackEnd로 조절을 해줌 
//	// _attackCoolTime만큼 공격키를 누를 수 없다.
//	if (_isAttack)
//	{
//		_timer += DELTA_TIME;
//
//		if (_timer >= 0.8)
//		{
//			_isAttackEnd = false;
//		}
//
//		if (!_isAttackEnd)
//		{
//			if (_timer > _attackCoolTime)
//			{
//				_timer = 0;
//				_isAttack = false;
//			}
//		}
//	}
//}
//
//void Player::WallAttack()
//{
//	if (INPUT->GetButton(KEY_TYPE::CTRL) && !_isWallJumping && !_isAttack && _isChargeSkill && _isWallAttack)
//	{
//		_checkAttackCharge += DELTA_TIME;
//
//		if (_checkAttackCharge <= 1.f)
//		{
//			OutputDebugString("공격1");
//			_power = 10.0f;
//		}
//		else if (_checkAttackCharge > 2.f)
//		{
//			OutputDebugString("공격2");
//			_power = 30.f;
//		}
//	}
//	// CTRL버튼을 땠을 때 저장 된 공격력을 지닌 총알을 오브젝트 풀에서 하나 생성한 다음 
//	// 플레이어가 바라보고 있는 방향으로 발사시킴
//	else if (INPUT->GetButtonUp(KEY_TYPE::CTRL) && !_isWallJumping && !_isAttack && _isWallAttack)
//	{
//		//GET_SINGLE(ObjectPool<EnemyController>)->SpawnFromPool("TestEnemyPrefab", Vector2(600, 800));
//		if (!_isFlipped)
//		{
//			_gameObject = GET_SINGLE(ObjectPool)->SpawnFromPool("BulletPrefab", _transform->GetLocalPosition());
//
//			if (_gameObject != nullptr)
//			{
//				_gameObject->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2::Left, _isFlipped, _transform, true);
//				_gameObject->GetScriptComponent<Bullet>()->SetDamageBullet(_power);
//				_gameObject = nullptr;
//			}
//		}
//		else if (_isFlipped)
//		{
//			_gameObject = GET_SINGLE(ObjectPool)->SpawnFromPool("BulletPrefab", _transform->GetLocalPosition());
//
//			if (_gameObject != nullptr)
//			{
//				_gameObject->GetScriptComponent<Bullet>()->SetBulletInfo(Vector2::Right, !_isFlipped, _transform, true);
//				_gameObject->GetScriptComponent<Bullet>()->SetDamageBullet(_power);
//				_gameObject = nullptr;
//			}
//		}
//		_isAttack = true;
//
//		_isAttackEnd = true;
//
//		_checkAttackCharge = 0;
//	}
//
//	// 공격키를 연속으로 누르지 못하게 하기 위해 
//	// _isAttackEnd로 조절을 해줌 
//	// _attackCoolTime만큼 공격키를 누를 수 없다.
//	if (_isAttack)
//	{
//		_timer += DELTA_TIME;
//
//		if (_timer >= 0.8)
//		{
//			_isAttackEnd = false;
//		}
//
//		if (!_isAttackEnd)
//		{
//			if (_timer > _attackCoolTime)
//			{
//				_timer = 0;
//				_isAttack = false;
//			}
//		}
//	}
//}
//
//// 일반 점프
//void Player::Jump()
//{
//	if (INPUT->GetButtonDown(KEY_TYPE::SPACE) && !_isJumping && !_isWallJumping && !SCENE_MANAGER->GetIsReservedTimeControl())
//	{
//		SOUND_MANAGER->PlayerJump();
//		OutputDebugString("점프했당 \n");
//		_rigidbody->GetVelocity();
//		_rigidbody->AddForce(Vector2::Up * _jumpPower);
//	}
//}
//
//// 벽점프 함수
//// _isWallCheck가 true일 때 실행이 된다.
//void Player::WallJump()
//{
//	if (!_isWallCheck) return;
//
//	// 벽점프 가능상태
//	if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
//	{
//		_isWallJumping = true;
//		OutputDebugString("벽점프 중\n");
//		_rigidbody->SetVelocity((Vector2(0, 0)));
//		_rigidbody->AddForce(_diagonal * _wallJumpPower);
//		_rigidbody->SetLinearDragY(0.08f);
//	}
//}
//
//// 대시 중이면 _checkDashTime으로 시간을 체크해서 _coolTime동안은 대시 스킬을 못쓰게 막고 
//// 대시 스킬이 끝날 때 마찰력을 받아서 천천히 멈추게 하지 않기 위해
//// _checkDashTime이 0.4보다 크거나 같으면 x축의 속도를 0으로 만들어준다.
//void Player::Dash()
//{
//	if (INPUT->GetButtonDown(KEY_TYPE::SHIFT) && !_isDash && _isDashSkill)
//	{
//		OutputDebugString("대시 \n");
//
//		if (!_isFlipped)
//		{
//			_rigidbody->AddForce(Vector2::Right * _dash);
//		}
//		else if (_isFlipped)
//		{
//			_rigidbody->AddForce(Vector2::Left * _dash);
//		}
//		_isDash = true;
//		_isDashEnd = true;
//	}
//
//	if (_isDash)
//	{
//		_checkDashTime += DELTA_TIME;
//
//		if (_checkDashTime >= 0.4)
//		{
//			if (_isDashEnd)
//			{
//				_rigidbody->SetVelocity({ 0,_rigidbody->GetVelocity().y });
//
//				OutputDebugString("대시 끝 \n");
//
//				_isDashEnd = false;
//			}
//		}
//
//		if (!_isDashEnd)
//		{
//			if (_checkDashTime > _coolTime)
//			{
//				_checkDashTime = 0;
//
//				_isDash = false;
//			}
//		}
//	}
//
//}
//
//void Player::Flipped()
//{
//	if (_h > 0)
//	{
//		_isFlipped = false;
//	}
//	else if (_h < 0)
//	{
//		_isFlipped = true;
//	}
//}
//
//void Player::AnimationUpdate()
//{
//	if (_isAttack == true)
//	{
//		_animator->Play("Attack");
//	}
//	else if (_h == 0)
//	{
//		_animator->Play("Idle");
//	}
//	else if (_h != 0)
//	{
//		_animator->Play("Walk");
//
//		if (_h < 0)
//		{
//			_transform->SetLocalScale(Vector2(-1 * _scale.x, 1 * _scale.y));
//		}
//		else if (_h > 0)
//		{
//			_transform->SetLocalScale(Vector2(1 * _scale.x, 1 * _scale.y));
//		}
//	}
//	else if (_isDash == true)
//	{
//		_animator->Play("Dash");
//	}
//	else if (_hp <= 0)
//	{
//		_animator->Play("Dead");
//	}
//}
//
//void Player::InvincibleControl()
//{
//	if (_isInvincible)
//	{
//		_invincibleTimer += DELTA_TIME;
//
//		if (_invincibleTimer >= 1.5f)
//		{
//			_isInvincible = false;
//			_invincibleTimer = 0;
//		}
//	}
//}
//
//void Player::OnCollisionEnter(ColliderBase* collider)
//{
//	if (collider->CompareTag(TAG::Ground))
//	{
//		//_rigidbody->SetGravityScale(1.0f);
//	}
//
//	if (collider->CompareTag(TAG::Enemy))
//	{
//		if (!_isDashEnd && !_isInvincible)
//		{
//			_knockBackX = _transform->GetLocalPosition().x - collider->GetGameObject()->GetComponent<Transform>()->GetLocalPosition().x > 0 ? 1 : -1;
//
//			_knockBackY = _transform->GetLocalPosition().y - collider->GetGameObject()->GetComponent<Transform>()->GetLocalPosition().y > 0 ? 1 : -1;
//
//			_rigidbody->AddForce(Vector2(_knockBackX, _knockBackY) * _knockBackPower);
//
//			_hp -= _damage;
//
//			_isInvincible = true;
//		}
//	}
//	//_isJumping = true;
//
//	//if (collider->CompareTag(TAG::Ground) || collider->CompareTag(TAG::MovableGround) || collider->CompareTag(TAG::GetThroughGround))
//	//{
//	//	// 벽점프에서 대각선으로 주는 힘때문에 바닥에 착지할 때 밀리는 현상이 있어 그걸 없애주기 위해 x의 속도를 0으로 만들어줌
//	//	if (collider->GetColDir() == (int)COL_DIR::UP)
//	//	{
//	//		_rigidbody->SetVelocity({ 0,_rigidbody->GetVelocity().y });
//	//	}
//	//}
//}
//
//void Player::OnCollisionStay(ColliderBase* collider)
//{
//	if (collider->CompareTag(TAG::MovableGround) && _boxCollider->GetColDir() == (int)COL_DIR::DOWN)
//	{
//		_isJumping = false;
//		_isWallCheck = false;
//		_rigidbody->SetGravityScale(1.0f);
//	}
//	else if (collider->CompareTag(TAG::GetThroughGround) && _boxCollider->GetColDir() == (int)COL_DIR::DOWN)
//	{
//		_isJumping = false;
//		_isWallCheck = false;
//		_rigidbody->SetGravityScale(1.0f);
//	}
//
//	if (collider->CompareTag(TAG::Ground))
//	{
//		if (_boxCollider->GetColDir() == (int)COL_DIR::DOWN)
//		{
//			_isJumping = false;
//			_isWallCheck = false;
//			_rigidbody->SetGravityScale(1.0f);
//		}
//		// 바닥이 아니고 벽에 닿았을 때 마찰력을 줘서 천천히 떨어지게 해주면서 벽점프를 할 수 있게 해준다.
//		// _diagonal은 반대편 벽으로 가기 위해 구해준 대각선이다.
//		else if (_boxCollider->GetColDir() == (int)COL_DIR::LEFT)
//		{
//			_diagonal = ((Vector2::Up + Vector2::Right) * 1.3f).Normalized();
//
//			_isDashEnd = false;
//		}
//		else if (_boxCollider->GetColDir() == (int)COL_DIR::RIGHT)
//		{
//			_diagonal = ((Vector2::Up + Vector2::Left) * 1.3f).Normalized();
//
//			_isDashEnd = false;
//		}
//
//		// 벽에 닿으면 _isWallCheck를 true로 바꿔줘서 벽점프를 할 수 있게 해준다.
//		if (((_boxCollider->GetColDir() == (int)COL_DIR::LEFT && INPUT->GetButton(KEY_TYPE::LEFT) && _rigidbody->GetVelocity().y > 0) || (_boxCollider->GetColDir() == (int)COL_DIR::RIGHT && INPUT->GetButton(KEY_TYPE::RIGHT) && _rigidbody->GetVelocity().y > 0)))
//		{
//			_rigidbody->SetLinearDragY(0.5f);
//
//			_isDashEnd = false;
//
//			_isWallCheck = true;
//
//			_isWallAttack = true;
//
//			_isJumping = true;
//		}
//
//		if (_rigidbody->GetVelocity().y <= 0)
//		{
//			_rigidbody->SetLinearDragY(0.08f);
//			_isWallCheck = false;
//		}
//	}
//
//	//if (collider->CompareTag(TAG::Ground) || collider->CompareTag(TAG::MovableGround))
//	//{
//	//	// rigid->Addforce이용한 Move로 바꾸었는데 지상에서 마찰때매 미끄러지는걸 방지하기위해
//	//	// 이전의 _h 값과 비교하여 다르다면 x속도를 0으로 주었다.
//	//	if (_h != _preHorizontal)
//	//	{
//	//		_rigidbody->SetVelocity(Vector2(0, _rigidbody->GetVelocity().y));
//	//	}
//
// // 		if (collider->GetColDir() == (int)COL_DIR::UP)
//	//	{
//	//		// 땅이랑 계속 부딪혀서 땅에 닿으면 그레비티 스케일 0.01f으로 주는걸로 일단 해봤음
//	//		//_rigidbody->SetGravityScale(0.01f);
//
//	//		_isJumping = false;
//	//		_isWallCheck = false;
//	//	}
//
//	//	// 바닥이 아니고 벽에 닿았을 때 마찰력을 줘서 천천히 떨어지게 해주면서 벽점프를 할 수 있게 해준다.
//	//	// _diagonal은 반대편 벽으로 가기 위해 구해준 대각선이다.
//	//	if (collider->GetColDir() == (int)COL_DIR::LEFT)
//	//	{
//	//		_diagonal = ((Vector2::Up + Vector2::Left) * 1.3f).Normalized();
//
//	//		_isDashEnd = false;
//
//	//	}
//	//	else if (collider->GetColDir() == (int)COL_DIR::RIGHT)
//	//	{
//	//		_diagonal = ((Vector2::Up + Vector2::Right) * 1.3f).Normalized();
//
//	//		_isDashEnd = false;
//	//	}
//
//	//	// 벽에 닿으면 _isWallCheck를 true로 바꿔줘서 벽점프를 할 수 있게 해준다.
//	//	if ((collider->GetColDir() == (int)COL_DIR::LEFT && INPUT->GetButton(KEY_TYPE::RIGHT) || collider->GetColDir() == (int)COL_DIR::RIGHT && INPUT->GetButton(KEY_TYPE::LEFT))
//	//		&& _rigidbody->GetVelocity().y > 0)
//	//	{
//	//		_rigidbody->SetLinearDragY(1.f);
//
//	//		_isDashEnd = false;
//
//	//		_isWallCheck = true;
//
//	//		_isWallAttack = true;
//	//	}
//
//	//	if (_rigidbody->GetVelocity().y <= 0)
//	//	{
//	//		_rigidbody->SetLinearDragY(0.08f);
//	//		_isWallCheck = false;
//	//	}
//	//}
//	//else if (collider->CompareTag(TAG::Enemy))
//	//{
//	//	collider->GetColDir();
//	//}
//	//else if (collider->CompareTag(TAG::GetThroughGround))
//	//{
//	//	if (_h != _preHorizontal)
//	//	{
//	//		_rigidbody->SetVelocity(Vector2(0, _rigidbody->GetVelocity().y));
//	//	}
//
//	//	if (collider->GetColDir() == (int)COL_DIR::UP)
//	//	{
//	//		_isJumping = false;
//	//	}
//	//}
//
//	/*if (collider->CompareTag(TAG::Ground))
//	{
//		if (collider->GetColDir() == (int)COL_DIR::RIGHT && collider->GetColDir() == (int)COL_DIR::LEFT && collider->GetColDir() == (int)COL_DIR::UP)
//		{
//			if (_h != _preHorizontal)
//			{
//				_rigidbody->SetVelocity(Vector2(0, _rigidbody->GetVelocity().y));
//			}
//
//			_rigidbody->SetGravityScale(0.01f);
//
//			_isJumping = false;
//			_isWallCheck = false;
//		}
//	}*/
//
//}
//
//void Player::OnCollisionExit(ColliderBase* collider)
//{
//	if (collider->CompareTag(TAG::Ground) || collider->CompareTag(TAG::MovableGround) || collider->CompareTag(TAG::GetThroughGround))
//	{
//		_rigidbody->SetGravityScale(10.0f);
//
//		_isJumping = true;
//
//		_isWallJumping = false;
//
//		_isWallCheck = false;
//
//		_isWallAttack = false;
//
//		_diagonal = Vector2(0, 0);
//
//		_rigidbody->SetLinearDragX(0.5f);
//		_rigidbody->SetLinearDragY(0.08f);
//	}
//}
//
//void Player::OnTriggerEnter(ColliderBase* collider)
//{
//	if (collider->CompareTag(TAG::Item))
//	{
//		if (collider->GetGameObject()->GetName() == "Dash")
//		{
//			_isDashSkill = true;
//		}
//		else if (collider->GetGameObject()->GetName() == "Charge")
//		{
//			_isChargeSkill = true;
//		}
//	}
//
//	if (collider->CompareTag(TAG::Portal))
//	{
//		_fadeinObj->SetLoadSceneName(collider->GetGameObject()->GetName());
//		//SCENE_MANAGER->LoadScene(collider->GetGameObject()->GetName());
//		//SCENE_MANAGER->LoadScene("MainStage1");
//	}
//
//
//}
//
//void Player::OnTriggerStay(ColliderBase* collider)
//{
//	if (collider->CompareTag(TAG::Hurdle))
//	{
//		if (!_isDashEnd && !_isInvincible)
//		{
//			//_diagonal = Vector2(_transform->GetLocalPosition() - collider->GetGameObject()->GetComponent<Transform>()->GetLocalPosition()).Normalized();
//
//			//_rigidbody->AddForce(_diagonal * _knockBackPower);
//
//			_knockBackX = _transform->GetLocalPosition().x - collider->GetGameObject()->GetComponent<Transform>()->GetLocalPosition().x > 0 ? 1 : -1;
//
//			_knockBackY = _transform->GetLocalPosition().y - collider->GetGameObject()->GetComponent<Transform>()->GetLocalPosition().y > 0 ? 1 : -1;
//
//			_rigidbody->AddForce(Vector2(_knockBackX, _knockBackY) * _knockBackPower);
//
//			_rigidbody->Update();
//
//			_hp -= _damage;
//
//			_isInvincible = true;
//		}
//	}
//}
//
//void Player::OnTriggerExit(ColliderBase* collider)
//{
//}