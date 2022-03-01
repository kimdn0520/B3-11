#pragma once

class BOSS_VERTICAL_ATTACK : public State
{
public:
	BOSS_VERTICAL_ATTACK(Boss* ref);

private:
	AnimationClip* animClip;
	class Boss* ref;

public:
	// State�� ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

