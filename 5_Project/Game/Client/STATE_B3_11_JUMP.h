#pragma once

class STATE_B3_11_JUMP : public State
{
public:
	STATE_B3_11_JUMP(B3_11* ref);
private:
	AnimationClip* animClip;
	class B3_11* ref;
public:
	// State��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};