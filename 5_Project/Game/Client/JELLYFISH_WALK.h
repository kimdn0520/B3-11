#pragma once

class JELLYFISH_WALK : public State
{
public:
	JELLYFISH_WALK(JellyFish* ref);

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

