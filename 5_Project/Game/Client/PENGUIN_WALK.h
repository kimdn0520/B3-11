#pragma once

class PENGUIN_WALK : public State
{
public:
	PENGUIN_WALK(Penguin* ref);

private:
	AnimationClip* animClip;
	class Penguin* ref;

public:
	// State를 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

