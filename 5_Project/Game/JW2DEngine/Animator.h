#pragma once
#include "Component.h"

class AnimationClip;
class Transform;
class Sprite;

/// <summary>
/// �ش��ϴ� ������Ʈ�� �ִϸ��̼� Ŭ������ ���ִ�.
/// Ŭ������ ����ϰ� �����Ѵ�.
/// </summary>
class Animator : public Component
{
public:
	Animator(GameObject* gameObject);
	~Animator();

public:
	map<string, AnimationClip*> GetAniClipData() { return _aniClipData; }
	
	// map�� ���� name�� �̸������� AnimationClip ��ü�� �����Ѵ�.
	void CreateAnimClip(string name);

	void AddAnimClip(string name, AnimationClip* animClip);

	void InputClipData(string name, Sprite* sprite);

	void Play(const string& name);
	
	void Play(AnimationClip* clip);

	int GetFrameIndex() { return _currentIndex; }

	virtual void FinalUpdate() override;

	void StopPlay() { _isPlay = false;}

	void StopRender() {_isRender = false;}

	void ResumeRender() {_isRender = true;}

private:
	Transform* _transform;

	map<string, AnimationClip*> _aniClipData;
	
	int _currentIndex;		// ���� ����ϰ��ִ� Ŭ�� �� ��������Ʈ �ε���

	int _totalFrameOfClip;	// �����Ǿ� �ִ� �ִϸ��̼� Ŭ���� �� ��������Ʈ ����

	float _loadTime;

	string _name;

	bool _isPlay;

public:
	bool _isRender;		//�׸��� ���߱�

private:
	//����찡 �������̵��� �ִϸ�����
	AnimationClip* _currentCilp;
public:
	void ContinuosPlay(AnimationClip* clip);//���� ǥ���� �Լ� ���� ���� ���� �ٸ� �� ���� ���������� �Ѿ��
};

