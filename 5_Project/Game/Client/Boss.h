#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class Text;
class BoxCollider;
class CircleCollider;
class State;

class Boss : public MonoBehaviour
{
	friend class BOSS_IDLE;
	friend class BOSS_HORIZONTAL_ATTACK;
	friend class BOSS_VERTICAL_ATTACK;
	friend class BOSS_ENEMY_SUMMON;
	friend class BOSS_HIT;
	friend class BOSS_GAME_OVER;

public:
	Boss(GameObject* gameObject);
	~Boss();

private:
	//GameObject ����
	GameObject* _gameObject;
	Transform* _transform;
	Animator* _animator;
	CircleCollider* _circleCollider;
	Rigidbody* _rigidbody;

	//Boss ����
	const int _maxHp;
	int _hp;
	float _power;

	//State �ѱ�� ���ǵ�
	float _attackCoolTime = 0.f;	// 5���Ŀ� �����Ұ���
	float _attackDelay = 0.f;		// ��� �����ϰ� IDLE �� �ʰ� �������ؼ�..
	bool _isHorizontalAtk;			// ���� �����Ҷ��� �Ǹ�..
	bool _isVerticalAtk;			// ���� �����Ҷ��� �Ǹ�..
	bool _isEnemySummon;			// �� ��ȯ�Ҷ��� �Ǹ�..
	float _deadDelay = 0.f;			// �װ� ������������ �ð�
	bool _isHit = false;			// �Ѿ˿� ������

	// ��������
	float _hittedDmg = 0.f;

	enum
	{
		IDLE,
		HORIZONTAL_ATTACK,
		VERTICALL_ATTACK,
		ENEMY_SUMMON,
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
	const float _soundDelay;

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
};

