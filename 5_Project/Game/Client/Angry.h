#pragma once

class Angry : public State
{
public:
	Angry(AngryAnimation* ref);
private:
	AnimationClip* animClip;
	class AngryAnimation* ref;
public:
	// State��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual int FixedUpdate() override;
	virtual void Update() override;
	virtual void End() override;
};