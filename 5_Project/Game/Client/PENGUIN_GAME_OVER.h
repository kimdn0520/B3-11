#pragma once

class PENGUIN_GAME_OVER : public State
{
public:
	PENGUIN_GAME_OVER(Penguin* ref);

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

