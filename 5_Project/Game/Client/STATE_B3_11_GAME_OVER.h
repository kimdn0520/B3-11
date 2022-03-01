#pragma once
class STATE_B3_11_GAME_OVER : public State
{
public:
	STATE_B3_11_GAME_OVER(B3_11* ref);
private:
	AnimationClip* animClip;
	AnimationClip* gameOverClip;
	class B3_11* ref;
public:
	// State��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};

