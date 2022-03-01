#pragma once

class SHARK_HIT : public State
{
public:
	SHARK_HIT(Shark* ref);

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

