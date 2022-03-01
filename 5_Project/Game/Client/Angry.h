#pragma once

class Angry : public State
{
public:
	Angry(AngryAnimation* ref);
private:
	AnimationClip* animClip;
	class AngryAnimation* ref;
public:
	// State을(를) 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};