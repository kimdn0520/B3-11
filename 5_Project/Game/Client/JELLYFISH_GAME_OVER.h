#pragma once

class JELLYFISH_GAME_OVER : public State
{
public:
	JELLYFISH_GAME_OVER(JellyFish* ref);

private:
	AnimationClip* animClip;
	class JellyFish* ref;

public:
	// State를 통해 상속됨
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

