#pragma once

class PENGUIN_WALK : public State
{
public:
	PENGUIN_WALK(Penguin* ref);

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

