#pragma once

class JELLYFISH_HIT : public State
{
public:
	JELLYFISH_HIT(JellyFish* ref);

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

