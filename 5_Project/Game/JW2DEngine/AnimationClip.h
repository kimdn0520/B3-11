#pragma once

class Sprite;

/// <summary>
/// ���������� ������ �ִϸ��̼��� ������ �ִ�.
/// IDLE, MOVE, JUMP... ���
/// </summary>
class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

public:
	// LoardSpriteFromSheet �� ���ؼ� ����ٰ� ��������Ʈ�� �־��ٰ���.
	void SetSpriteAnimData(Sprite* sprite);

	// �ε����� �ش��ϴ� ��������Ʈ Ŭ�� ��ȯ
	Sprite* GetFrame(int index);

	// �� �ִϸ��̼� Ŭ���� ��������Ʈ �� ����� ��ȯ�Ѵ�.
	int GetAnimTotalFrame();

private:
	vector<Sprite*> _spriteAnim;
};

