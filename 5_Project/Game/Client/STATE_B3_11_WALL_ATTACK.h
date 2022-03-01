#pragma once

class STATE_B3_11_WALL_ATTACK : public State
{
public:
	STATE_B3_11_WALL_ATTACK(B3_11* ref);
private:
	AnimationClip* animClip[4];
	class B3_11* ref;
public:
	// State을(를) 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};