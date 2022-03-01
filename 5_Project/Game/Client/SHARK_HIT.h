#pragma once

class SHARK_HIT : public State
{
public:
	SHARK_HIT(Shark* ref);

private:
	AnimationClip* animClip;
	class Shark* ref;

public:
	// State�� ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

