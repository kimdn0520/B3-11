#pragma once

class PENGUIN_RUN : public State
{
public:
	PENGUIN_RUN(Penguin* ref);

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

