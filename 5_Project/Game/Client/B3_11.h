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
/// �÷��̾� �������̺�� ���� �� ������Ʈȭ
/// 
/// �����ƾ� �� �ڵ� �� ����, �� �ȶ���
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
	//GameObject ����
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

	//B3_11 ����
	const int _maxHp;
	int _hp;
	const int _maxChargeLevel;
	int _chargeLevel;//0~2�ܰ� ǥ��
	const float _speed;
	const float _jumpPower;
	const float _wallJumpPower;
	const Vector2 _wallJumpDiagonal;//�� ���� ����
	int _power[4];//���� ���� chargeLevel���ؼ� ����� ����
	const float _knockBackPower;
public:
	Vector2 _knockBackDiagonal;//�˹����
private:
	const float _dashPower;
	float _face;//�ٶ󺸴� ����, -1 = ����, 1 = ������

	//��ų ���� ����
	bool _hasDash;//�뽬 ��ų�� �ִ���
	bool _hasCharge;//���� ��ų�� �ִ���

	bool _bOnWall;

	///State �ѱ�� ���ǵ�
	float _input;//-1 = left, 0 = neutral, 1 = right
	bool _wallSide[2];//�ε��� �� ���� [0] = left, [1] = right
	bool _groundWay[4];// 0 DOWN, 1 LEFT, 2 RIGHT , 3 UP
	bool _bJumpKeyDown;//����Ű�� ������
	bool _bJumpKeyPressed;//����Ű�� �����°�
	bool _bJumpEntry;//���� ���� ����
	bool _bAttackKeyPressed;//����Ű�� ������ �ִ°�
	bool _bDashKeyPressed;//�뽬Ű�� �����°�
	float _shootWay;//�� ���¿��� �ݴ�� ���ֱ� ����
public:
	bool _bCheckGround;//�ٴ� �浹 ����
private:
	bool _bCheckWall;//�� �浹 ����
	bool _isJumping;
public:
	bool _bHit;//�ǰ� ����
private:
	float _wallEscapeTimer;
	float _hitTimer;//�ǰ� �� ���� �ð�
	float _dashCoolTimer;//�뽬 ��Ÿ�� üĿ
	const float _dashCoolTime;//�뽬 ��Ÿ��
	float _dashTimer;//�뽬 ���ӽð�
	float _jumpTimer;//���� �� ���� �ð�
	const float _jumpTime;//���� ���� ���� �ð�
	const float _wallEscapeTime;//�� ���� ���� ���ֱ� ���� ��¦ �پ��ִ� �ð�
	const float _recoveryTime;//�ǰ� �� ���� ������ �ð�
	const float _dashTime;//�뽬 ���� �ð�
	float _deadDelay; // �װ� ������������ �ð�

	bool _invincible;

	float _invincibleTimer;
	float _invincibleTime;

	bool _isAttacking;//���� ��� ������ ����
	bool _chargable;//������ �����Ҽ� �ִ� ����
	bool _shootable;//Ű�� ���� ��� �ִ� ����

	bool _followTimerAddable;

	float _attackFollowThoroughTimer;
	const float _attackFollowThoroughTime;//���� ������ ���� ���� �ð�

	float _attackCoolTimer;
	const float _attackCoolTime;

	float _chargeTimer; // 
	const float _chargeTime; // ���� �����Ϸ� �ð�

	bool _isDashing;
	bool _isDashable;

	bool _jumpForceAddable;//���� ���� �ϱ� ����

	bool _chargeSound; // �������� ���ѹݺ� ����

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

	//�ý��� ���� ����
	Text* _text;
	const float _moveSoundDelay;
	GameObject* _fadeInObj;//Only ���� ���� �Ҵ� ���� �ʿ�x

public:
	virtual void PreProcess() override;

	virtual void OnCollisionEnter(ColliderBase* collider) override;
	virtual void OnCollisionStay(ColliderBase* collider) override;
	virtual void OnCollisionExit(ColliderBase* collider) override;

	virtual void OnTriggerEnter(ColliderBase* collider) override;
	virtual void OnTriggerStay(ColliderBase* collider) override;
	virtual void OnTriggerExit(ColliderBase* collider) override;

	virtual void FixedUpdate() override;//������
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