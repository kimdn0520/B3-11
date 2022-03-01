#pragma once

class BOSS_IDLE : public State
{
public:
	BOSS_IDLE(Boss* ref);

private:
	AnimationClip* animClip;
	class Boss* ref;

public:
	// State를 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

