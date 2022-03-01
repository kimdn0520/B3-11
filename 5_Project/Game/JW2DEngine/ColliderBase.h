#pragma once
#include "Component.h"

class ColliderBase : public Component
{
public:
	ColliderBase(GameObject* gameObject);
	virtual ~ColliderBase();

public:
	bool CompareTag(TAG tag);

	bool GetTrigger() { return _isTrigger; }

	void SetTrigger(bool value) { _isTrigger = value; }

	bool GetIsOnCollision() { return _isCollision; }
	void SetCollision(bool value);

	Transform* GetTransform() { return transform; }

	Rigidbody* GetRigidBody() { return rigidbody; }

	Vector2 GetPosition() { return position; }

	bool GetOtherColliderInfo(ColliderBase* col);
	
	void SetOtherColliderInfo(ColliderBase* col, bool value);

	inline Matrix GetColMatrix() { return _colMatrix; }

	void SetColliderLocation(Vector2 colLocation) { _colLocation = colLocation; }
	
	int GetColDir() { return _colDir; }
	void SetColDir(int colDir) { _colDir = colDir; }

	vector<bool> GetColDirVec() { return _colDirVec; }// 0 DOWN, 1 LEFT, 2 RIGHT , 3 UP
	void SetColDirVec(int coldir) { _colDirVec[coldir] = true; }
	void ResetColDirVec() 
	{
		_colDirVec[0] = false;  _colDirVec[1] = false;
		_colDirVec[2] = false;  _colDirVec[3] = false;
	}

	void ResetCollsionInfo();

protected:
	Transform* transform;

	Rigidbody* rigidbody;

	Vector2 position;

	bool _isCollision;

	bool _isTrigger;

	int _colDir = -1; // 0 DOWN, 1 LEFT, 2 RIGHT , 3 UP

	vector<bool> _colDirVec = { false, false, false, false };

protected:
	virtual bool CheckCollision(ColliderBase* other){ return false; }

	virtual void FixedUpdate() {};

	virtual void Update() {};

protected:
	unordered_map<ColliderBase*, bool> _otherColliderInfo; // 주소, 태그, 충돌여부
	
	Vector2 _colLocation;		// 이걸로 콜라이더의 위치 조절

	Matrix _colMatrix;			// col 자체의 matrix
};

