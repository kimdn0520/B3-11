#include "pch.h"
#include "Timer.h"

// 어떤 시간을 기준으로 상대적인 시간의 흐름을 계산
void Timer::Init()
{
	// GetTickCount64() 는 정밀도가 떨어진다.
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU 클럭
}

/// <summary>
/// 시작점과 끝지점에서 QueryPerformanceCounter 함수를 호출하면 수행시간동안 발생한 진동수를 얻을 수 있음
/// 그러나 이 값은 시간 단위가 아니기 때문에 QueryPerformanceFrequency함수로 얻는 주기로 나누어 시간 단위로 변환해야 함.
/// </summary>
void Timer::Update()
{
	// 현재 CPU 클럭 Count를 가져온다.
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// 현재 Count(currentCount)에서 전 Count(preCount)를 뺀 값을
	// frequency로 나누어주면 경과된 시간(초)이 나온다.
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount; // preCount에 currentCount를 저장

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime > 1.f)	// 1초를 넘어가는 순간
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);  // 1초간 Update문이 몇번 실행되었는지

		_frameTime = 0.f;	// 0으로 초기화
		_frameCount = 0;	// 0으로 초기화
	}
}
