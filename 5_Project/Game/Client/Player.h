#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class Text;
class BoxCollider;
class ObjectPool;
class BulletPrefab;
//enum class State
//{
//	IDLE,
//	MOVE,
//	ATTACK,
//	DASH,
//	JUMP
//};

class Player : public MonoBehaviour
{
public:
	Player(GameObject* gameObject);
	~Player();
	
private:
	Transform* _transform;

	Rigidbody* _rigidbody;

	Animator* _animator;

	BoxCollider* _boxCollider;

	GameObject* _gameObject;

	Text* _text;

	//State _state;

	GameObject* _tmpObj;

	Vector2 _scale;
	Vector2 _diagonal;			// 대각선 점프와 넉백을 위한 백터
	Vector2 _pos;

	BulletPrefab* _bulletPrefab;	

	ObjectPool* _objectPool;

	GameObject* _fadeInObj;

	int _hp;
	float _damage;				// 캐릭터가 입은 공격
	float _circularSawDamage;	// 톱날 공격력
	float _laserTrapDamage;		// 전기 공격력
	float _power;				// 캐릭터 공격력
	float _speed;				// 캐릭터가 움직일 때 속도
	float _jumpPower;			// 캐릭터 점프 높이
	float _wallJumpPower;		// 벽점프 할 때 높이
	float _knockBackPower;		// 넉백할 때 힘
	float _dash;				// 대시 속도
	float _checkDashTime;		// 대시스킬 지속시간
	float _coolTime;			// 다음 대시스킬을 쓰기위한 쿨타임
	float _timer;				// 공격 딜레이를 주기위한 타이머
	float _invincibleTimer;		// 무적시간 관리 타이머
	float _attackCoolTime;		// 얼마만큼 공격 딜레이를 줄 지 정하기 위해 사용
	float _checkAttackCharge;	// 차지공격을 위해 키가 얼마나 눌렸는지에 대한 시간을 계산하기 위해 사용
	float _moveSoundDelay;		// 사운드 무한재생 방지
	float _knockBackX;			// 넉백 할 때 x축으로 밀어내기 위한 값
	float _knockBackY;			// 넉백 할 때 Y축으로 밀어내기 위한 값

	bool _isFlipped;			// 오른쪽 왼쪽 구분
	bool _isAttack;				// 공격을 할 수 있는지 못하는지
	bool _isWallAttack;			// 벽에서 공격을 할 수 있게 해주기 위해 사용
	bool _isJumping;			// 점프를 할 수 있는지 못하는지
	bool _isWallJumping;		// 그냥 점프랑 벽점프를 구별하기 위해서 사용
	bool _isDash;				// 대시를 할 수 있는지 못하는지
	bool _isDashEnd;			// 대시스킬 종료, 벽점프에서 대시스킬을 써도 벽 한면으로만 못올라가게 하기위해 사용
	bool _isWallCheck;			// 벽(ground의 left&right)인지 체크해서 벽이면 벽점프를 할 수 있게 하기위해 사용
	bool _isAttackEnd;			// 공격이 끝났는지 확인해주기 위해 사용
	bool _isDashSkill;			// 대시스킬 획득했는지 확인
	bool _isChargeSkill;		// 차지공격 스킬 획득했는지 확인
	bool _isInvincible;			// 캐릭터가 공격당했을 때 잠시동안 무적상태를 해주기위해
	bool _isCheckPoint;			// 장애물에 닿았을 때 체크포인트로 이동

	Vector2 _height;
	Vector2 _moveDir;			// 움직일 방향
	float _h;
	float _v;
	float _preHorizontal = 0;	// 이전의 _h 값

private:
	void Move();
	void Attack();
	void WallAttack();
	void Jump();
	void WallJump();
	void Dash();
	void Flipped();
	void AnimationUpdate();
	void InvincibleControl();
	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnCollisionStay(ColliderBase* collider) override;
	virtual void OnCollisionExit(ColliderBase* collider) override;
	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerStay(ColliderBase* collider) override;
	virtual void OnTriggerExit(ColliderBase* collider) override;

	virtual void FixedUpdate() override; 

	virtual void Update() override;

public:
	void SetObjectBulletPool(ObjectPool* objectpool) { _objectPool = objectpool; }

	bool GetIsDashSkill() { return _isDashSkill; }
	bool GetIsChargeSkill() { return _isChargeSkill; }

	int GetHp() {return _hp;}
	Vector2 GetPlayerPosition() {return _pos;}
	void SetFadeInObj(GameObject* fadeInObj) { _fadeInObj = fadeInObj; }

};

