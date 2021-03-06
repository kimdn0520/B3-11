#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;
class Rigidbody;
class Animator;
class Text;
class BoxCollider;
class State;

class Shark : public MonoBehaviour
{
	friend class SHARK_WALK;
	friend class SHARK_RUN;
	friend class SHARK_ATTACK;
	friend class SHARK_HIT;
	friend class SHARK_GAME_OVER;

public:
	Shark(GameObject* gameObject);
	~Shark();

private:
	//GameObject 정보
	GameObject* _gameObject;
	Transform* _transform;
	Rigidbody* _rigidbody;
	const float _defaultLinearDragX;
	const float _defaultLinearDragY;
	const float _defaultGravityScale;
	Animator* _animator;
	BoxCollider* _boxCollider;

	//Shark 스펙
	const int _maxHp;
	int _hp;
	float _speed;
	const float _knockBackPower;
	Vector2 _knockBackDiagonal;//넉백방향
	float _attackCoolTime;
	float _face; //바라보는 방향, -1 = 왼쪽, 1 = 오른쪽
	float _h;
	float _v;
	float _moveTimer;
	Vector2 _moveDir = { 1.f, 1.f };
	float _dist;
	float _hittedDmg;
	bool _isDead = false;
	float _deadDelay = 0.f;

	//State 넘기는 조건들
	bool _isInDetect = false;
	bool _isInAtkDetect = false;
	bool _isHit = false;

	enum
	{
		WALK,
		RUN,
		ATTACK,
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
	Transform* _playerTransform;

public:
	int GetState() { return _newState; }
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
	void SetPlayerTransform(Transform* playerTransform) { _playerTransform = playerTransform; }
	
};

