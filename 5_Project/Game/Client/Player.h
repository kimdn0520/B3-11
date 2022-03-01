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
	Vector2 _diagonal;			// �밢�� ������ �˹��� ���� ����
	Vector2 _pos;

	BulletPrefab* _bulletPrefab;	

	ObjectPool* _objectPool;

	GameObject* _fadeInObj;

	int _hp;
	float _damage;				// ĳ���Ͱ� ���� ����
	float _circularSawDamage;	// �鳯 ���ݷ�
	float _laserTrapDamage;		// ���� ���ݷ�
	float _power;				// ĳ���� ���ݷ�
	float _speed;				// ĳ���Ͱ� ������ �� �ӵ�
	float _jumpPower;			// ĳ���� ���� ����
	float _wallJumpPower;		// ������ �� �� ����
	float _knockBackPower;		// �˹��� �� ��
	float _dash;				// ��� �ӵ�
	float _checkDashTime;		// ��ý�ų ���ӽð�
	float _coolTime;			// ���� ��ý�ų�� �������� ��Ÿ��
	float _timer;				// ���� �����̸� �ֱ����� Ÿ�̸�
	float _invincibleTimer;		// �����ð� ���� Ÿ�̸�
	float _attackCoolTime;		// �󸶸�ŭ ���� �����̸� �� �� ���ϱ� ���� ���
	float _checkAttackCharge;	// ���������� ���� Ű�� �󸶳� ���ȴ����� ���� �ð��� ����ϱ� ���� ���
	float _moveSoundDelay;		// ���� ������� ����
	float _knockBackX;			// �˹� �� �� x������ �о�� ���� ��
	float _knockBackY;			// �˹� �� �� Y������ �о�� ���� ��

	bool _isFlipped;			// ������ ���� ����
	bool _isAttack;				// ������ �� �� �ִ��� ���ϴ���
	bool _isWallAttack;			// ������ ������ �� �� �ְ� ���ֱ� ���� ���
	bool _isJumping;			// ������ �� �� �ִ��� ���ϴ���
	bool _isWallJumping;		// �׳� ������ �������� �����ϱ� ���ؼ� ���
	bool _isDash;				// ��ø� �� �� �ִ��� ���ϴ���
	bool _isDashEnd;			// ��ý�ų ����, ���������� ��ý�ų�� �ᵵ �� �Ѹ����θ� ���ö󰡰� �ϱ����� ���
	bool _isWallCheck;			// ��(ground�� left&right)���� üũ�ؼ� ���̸� �������� �� �� �ְ� �ϱ����� ���
	bool _isAttackEnd;			// ������ �������� Ȯ�����ֱ� ���� ���
	bool _isDashSkill;			// ��ý�ų ȹ���ߴ��� Ȯ��
	bool _isChargeSkill;		// �������� ��ų ȹ���ߴ��� Ȯ��
	bool _isInvincible;			// ĳ���Ͱ� ���ݴ����� �� ��õ��� �������¸� ���ֱ�����
	bool _isCheckPoint;			// ��ֹ��� ����� �� üũ����Ʈ�� �̵�

	Vector2 _height;
	Vector2 _moveDir;			// ������ ����
	float _h;
	float _v;
	float _preHorizontal = 0;	// ������ _h ��

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

