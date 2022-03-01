#pragma once
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
public:
	BoxCollider(class GameObject* gameObject);
	~BoxCollider();

public:
	inline vector<Vector2>& GetVertices() { return _vertices; }

	void SetWH(float width, float height) 
	{ 
		_width = width;
		_initWidth = width;
		_height = height;
		_initHeight = height;
	}

	Vector2 GetReflectVec() { return reflectVec; }
	Vector2 GetVelocityVec() { return velocityVec; }
	bool GetIsCheck() { return _isCheck; }
	void SetIsCheck(bool value) { _isCheck = value;}
	void ResetRealXY() { _realXd = 0.f; _realYd = 0.f; }
	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

	virtual bool CheckCollision(ColliderBase* other) override;

	virtual void Update() override;

	virtual void FinalUpdate() override;

	// 아 몰라 일단 퍼블릭에 둘래
	// COL_DIR , ([reflectVec, 비교할 수] VelocityVec)
	//map<int, pair<pair<Vector2, float>, Vector2>> _reflMap;
	
	// COL_DIR, 부딪힌 대상.. ([reflectVec, 비교할 수], reflectVec.mag VelocityVec)
    map<int , Info*> _reflMap;


private:
	float _initWidth;
	float _initHeight;

	float _width;
	float _height;

	Vector2 _scale;

	Vector2 _lt;
	Vector2 _rt;
	Vector2 _rb;
	Vector2 _lb;

	vector<Vector2> _vertices;

	float _realXd = 0.f;
	float _realYd = 0.f;
	float _realBig = 0.f;
	float _big = 0.f;
	Vector2 reflectVec = { 0, 0 };
	Vector2 velocityVec;
	bool _isCheck = false;

};

