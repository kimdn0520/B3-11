#pragma once

class JELLYFISH_ATTACK : public State
{
public:
	JELLYFISH_ATTACK(JellyFish* ref);

private:
	AnimationClip* animClip;
	class JellyFish* ref;

public:
	// State�� ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

