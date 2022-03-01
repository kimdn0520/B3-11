#pragma once

class SHARK_RUN : public State
{
public:
	SHARK_RUN(Shark* ref);

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

