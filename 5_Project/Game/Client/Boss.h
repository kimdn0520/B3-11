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
	//GameObject 정보
	GameObject* _gameObject;
	Transform* _transform;
	Animator* _animator;
	CircleCollider* _circleCollider;
	Rigidbody* _rigidbody;

	//Boss 스펙
	const int _maxHp;
	int _hp;
	float _power;

	//State 넘기는 조건들
	float _attackCoolTime = 0.f;	// 5초후에 공격할거임
	float _attackDelay = 0.f;		// 잠깐 공격하고 IDLE 좀 늦게 들어가기위해서..
	bool _isHorizontalAtk;			// 수평 공격할때가 되면..
	bool _isVerticalAtk;			// 수직 공격할때가 되면..
	bool _isEnemySummon;			// 적 소환할때가 되면..
	float _deadDelay = 0.f;			// 죽고 사라지기까지의 시간
	bool _isHit = false;			// 총알에 맞으면

	// 여러가지
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

	//시스템 관련 변수
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

	virtual void FixedUpdate() override;//물리쪽
	virtual void Update() override;
	virtual void FinalUpdate() override;
};

