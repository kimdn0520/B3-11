#pragma once

/// <summary>
/// Update문을 1프레임마다 한번 씩 수행함.
/// Timer를 사용하여 이전 프레임에서 현재 프레임까지 경과된 시간(deltaTime)을
/// 곱해줌으로써 1초간 정해진 만큼의 움직임을 구현할 수 있다.
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
	// 프레임을 계산하기위한 용도
	uint64	_frequency = 0;
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f;		// 이전 프레임에서 현재 프레임까지 경과된 시간

private:
	uint32	_frameCount = 0;		// Update문에 몇번 실행되었는지 게산
	float	_frameTime = 0.f;		// 누적 시간
	uint32	_fps = 0;				// framePerSecond 초마다 평균적으로 몇프레임 실행됐는지 계산
};

// ex) output.x += 1*deltaTime; 1초에 1씩 움직이는 코드이다. 요런느낌쓰