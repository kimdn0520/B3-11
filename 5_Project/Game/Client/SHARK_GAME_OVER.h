#pragma once

class SHARK_GAME_OVER : public State
{
public:
	SHARK_GAME_OVER(Shark* ref);

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

