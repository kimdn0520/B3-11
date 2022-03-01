#pragma once

class Sprite;

/// <summary>
/// 실질적으로 구성된 애니메이션을 가지고 있다.
/// IDLE, MOVE, JUMP... 등등
/// </summary>
class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

public:
	// LoardSpriteFromSheet 를 통해서 여기다가 스프라이트를 넣어줄거임.
	void SetSpriteAnimData(Sprite* sprite);

	// 인덱스에 해당하는 스프라이트 클립 반환
	Sprite* GetFrame(int index);

	// 이 애니메이션 클립의 스프라이트 총 장수를 반환한다.
	int GetAnimTotalFrame();

private:
	vector<Sprite*> _spriteAnim;
};

