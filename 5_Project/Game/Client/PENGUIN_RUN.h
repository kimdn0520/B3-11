#pragma once

class PENGUIN_RUN : public State
{
public:
	PENGUIN_RUN(Penguin* ref);

private:
	AnimationClip* animClip;
	class Penguin* ref;

public:
	// State�� ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

