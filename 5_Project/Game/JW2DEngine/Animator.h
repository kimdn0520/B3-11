#pragma once
#include "Component.h"

class AnimationClip;
class Transform;
class Sprite;

/// <summary>
/// 해당하는 오브젝트의 애니메이션 클립들이 모여있다.
/// 클립들을 재생하고 관리한다.
/// </summary>
class Animator : public Component
{
public:
	Animator(GameObject* gameObject);
	~Animator();

public:
	map<string, AnimationClip*> GetAniClipData() { return _aniClipData; }
	
	// map에 넣을 name의 이름을가진 AnimationClip 객체를 생성한다.
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
	
	int _currentIndex;		// 현재 출력하고있는 클립 내 스프라이트 인덱스

	int _totalFrameOfClip;	// 지정되어 있는 애니메이션 클립의 총 스프라이트 갯수

	float _loadTime;

	string _name;

	bool _isPlay;

public:
	bool _isRender;		//그리기 멈추기

private:
	//안재우가 오버라이드한 애니메이터
	AnimationClip* _currentCilp;
public:
	void ContinuosPlay(AnimationClip* clip);//차지 표현용 함수 같은 동작 색깔 다를 때 같은 프레임으로 넘어가게
};

