#pragma once

class BOSS_HIT : public State
{
public:
	BOSS_HIT(Boss* ref);

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

