#pragma once

/// <summary>
/// Update���� 1�����Ӹ��� �ѹ� �� ������.
/// Timer�� ����Ͽ� ���� �����ӿ��� ���� �����ӱ��� ����� �ð�(deltaTime)��
/// ���������ν� 1�ʰ� ������ ��ŭ�� �������� ������ �� �ִ�.
/// </summary>
class Timer
{
	DECLARE_SINGLE(Timer);

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	// �������� ����ϱ����� �뵵
	uint64	_frequency = 0;
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f;		// ���� �����ӿ��� ���� �����ӱ��� ����� �ð�

private:
	uint32	_frameCount = 0;		// Update���� ��� ����Ǿ����� �Ի�
	float	_frameTime = 0.f;		// ���� �ð�
	uint32	_fps = 0;				// framePerSecond �ʸ��� ��������� �������� ����ƴ��� ���
};

// ex) output.x += 1*deltaTime; 1�ʿ� 1�� �����̴� �ڵ��̴�. �䷱������