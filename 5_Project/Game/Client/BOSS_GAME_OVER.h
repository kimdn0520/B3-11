#pragma once

class BOSS_GAME_OVER : public State
{
public:
	BOSS_GAME_OVER(Boss* ref);

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

