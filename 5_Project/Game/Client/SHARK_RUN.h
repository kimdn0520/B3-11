#pragma once

class SHARK_RUN : public State
{
public:
	SHARK_RUN(Shark* ref);

private:
	AnimationClip* animClip;
	class Shark* ref;

public:
	// State를 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

