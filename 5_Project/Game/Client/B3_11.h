#pragma once

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class Text;
class BoxCollider;
class ObjectPool;
class BulletPrefab;
class FadeIn;
class State;

/// <summary>
/// 플레이어 모노비헤이비어 정리 및 스테이트화
/// 
/// 개미쳤어 나 코딩 개 잘해, 개 똑똑해
///  written by Ssreppa 20220202
/// </summary>

class B3_11 : public MonoBehaviour
{
	friend class STATE_B3_11_IDLE;
	friend class STATE_B3_11_IDLE_ATTACK;
	friend class STATE_B3_11_WALK;
	friend class STATE_B3_11_WALK_ATTACK;
	friend class STATE_B3_11_JUMP;
	friend class STATE_B3_11_JUMP_ATTACK;
	friend class STATE_B3_11_FALL;
	friend class STATE_B3_11_FALL_ATTACK;
	friend class STATE_B3_11_WALL;
	friend class STATE_B3_11_WALL_ATTACK;
	friend class STATE_B3_11_DASH;
	friend class STATE_B3_11_HIT;
	friend class STATE_B3_11_GAME_OVER;
public:										 
	B3_11(GameObject* gameObject);
	~B3_11();

private:
	//GameObject 정보
	GameObject* _gameObject;
	Transform* _transform;
	Rigidbody* _rigidbody;
	const float _defaultLinearDragX;
	const float _defaultLinearDragY;
	const float _defaultGravityScale;
	Animator* _animator;
public:
	BoxCollider* _boxCollider;
private:


	GameObject* _bullet;

	//B3_11 스펙
	const int _maxHp;
	int _hp;
	const int _maxChargeLevel;
	int _chargeLevel;//0~2단계 표시
	const float _speed;
	const float _jumpPower;
	const float _wallJumpPower;
	const Vector2 _wallJumpDiagonal;//벽 점프 방향
	int _power[4];//공격 뎀지 chargeLevel통해서 사용할 예정
	const float _knockBackPower;
public:
	Vector2 _knockBackDiagonal;//넉백방향
private:
	const float _dashPower;
	float _face;//바라보는 방향, -1 = 왼쪽, 1 = 오른쪽

	//스킬 보유 여부
	bool _hasDash;//대쉬 스킬이 있는지
	bool _hasCharge;//차지 스킬이 있는지

	bool _bOnWall;

	///State 넘기는 조건들
	float _input;//-1 = left, 0 = neutral, 1 = right
	bool _wallSide[2];//부딪힌 벽 방향 [0] = left, [1] = right
	bool _groundWay[4];// 0 DOWN, 1 LEFT, 2 RIGHT , 3 UP
	bool _bJumpKeyDown;//점프키를 눌렀나
	bool _bJumpKeyPressed;//점프키를 눌렀는가
	bool _bJumpEntry;//점프 진입 조건
	bool _bAttackKeyPressed;//공격키를 누르고 있는가
	bool _bDashKeyPressed;//대쉬키를 눌렀는가
	float _shootWay;//벽 상태에서 반대로 쏴주기 위해
public:
	bool _bCheckGround;//바닥 충돌 여부
private:
	bool _bCheckWall;//벽 충돌 여부
	bool _isJumping;
public:
	bool _bHit;//피격 여부
private:
	float _wallEscapeTimer;
	float _hitTimer;//피격 후 지난 시간
	float _dashCoolTimer;//대쉬 쿨타임 체커
	const float _dashCoolTime;//대쉬 쿨타임
	float _dashTimer;//대쉬 지속시간
	float _jumpTimer;//점프 후 지난 시간
	const float _jumpTime;//점프 가속 가능 시간
	const float _wallEscapeTime;//벽 점프 쉽게 해주기 위해 살짝 붙어있는 시간
	const float _recoveryTime;//피격 후 정신 차리는 시간
	const float _dashTime;//대쉬 지속 시간
	float _deadDelay; // 죽고 사라지기까지의 시간

	bool _invincible;

	float _invincibleTimer;
	float _invincibleTime;

	bool _isAttacking;//공격 모션 나가는 변수
	bool _chargable;//충전을 시작할수 있는 상태
	bool _shootable;//키를 떼면 쏠수 있는 상태

	bool _followTimerAddable;

	float _attackFollowThoroughTimer;
	const float _attackFollowThoroughTime;//공격 끝나고 여운 남는 시간

	float _attackCoolTimer;
	const float _attackCoolTime;

	float _chargeTimer; // 
	const float _chargeTime; // 공격 충전완료 시간

	bool _isDashing;
	bool _isDashable;

	bool _jumpForceAddable;//낮점 높점 하기 위해

	bool _chargeSound; // 차지사운드 무한반복 방지

	float _walkSoundTimer;
	const float _walkSoundCoolTime;

	enum
	{
		IDLE,
		IDLE_ATTACK,
		WALK,
		WALK_ATTACK,
		JUMP,
		JUMP_ATTACK,
		FALL,
		FALL_ATTACK,
		WALL,
		WALL_ATTACK,
		DASH,
		HIT,
		GAME_OVER
	};

	State* _currentState;
	int _oldState, _newState;
	map<int, State*> _states;

	void AddState(int stateEnum, State* state) { _states.insert({ stateEnum, state }); }

	void VisualizeState();

	//시스템 관련 변수
	Text* _text;
	const float _moveSoundDelay;
	GameObject* _fadeInObj;//Only 인지 관계 할당 해제 필요x

public:
	virtual void PreProcess() override;

	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnCollisionStay(ColliderBase* collider) override;
	virtual void OnCollisionExit(ColliderBase* collider) override;

	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerStay(ColliderBase* collider) override;
	virtual void OnTriggerExit(ColliderBase* collider) override;

	virtual void FixedUpdate() override;//물리쪽
	virtual void Update() override;
	virtual void FinalUpdate() override;

public:
	int GetHp() { return _hp; }
	bool GetIsDashSkill() { return _hasDash; }
	bool GetIsChargeSkill() { return _hasCharge; }
	void SetDashExist(bool isDashSkill) { _hasDash = isDashSkill; }
	void SetChargeExist(bool isChargeSkill) { _hasCharge = isChargeSkill; }
	void SetCurHp(int hp) { _hp = hp; }
	
	void SetFadeInObj(GameObject* fadeInObj) { _fadeInObj = fadeInObj; }
};