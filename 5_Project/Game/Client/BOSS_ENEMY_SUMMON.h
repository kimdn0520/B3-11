#pragma once
class BOSS_ENEMY_SUMMON : public State
{
public:
	BOSS_ENEMY_SUMMON(Boss* ref);

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

