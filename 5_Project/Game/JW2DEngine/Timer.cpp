#include "pch.h"
#include "Timer.h"

// � �ð��� �������� ������� �ð��� �帧�� ���
void Timer::Init()
{
	// GetTickCount64() �� ���е��� ��������.
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU Ŭ��
}

/// <summary>
/// �������� ���������� QueryPerformanceCounter �Լ��� ȣ���ϸ� ����ð����� �߻��� �������� ���� �� ����
/// �׷��� �� ���� �ð� ������ �ƴϱ� ������ QueryPerformanceFrequency�Լ��� ��� �ֱ�� ������ �ð� ������ ��ȯ�ؾ� ��.
/// </summary>
void Timer::Update()
{
	// ���� CPU Ŭ�� Count�� �����´�.
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// ���� Count(currentCount)���� �� Count(preCount)�� �� ����
	// frequency�� �������ָ� ����� �ð�(��)�� ���´�.
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount; // preCount�� currentCount�� ����

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime > 1.f)	// 1�ʸ� �Ѿ�� ����
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);  // 1�ʰ� Update���� ��� ����Ǿ�����

		_frameTime = 0.f;	// 0���� �ʱ�ȭ
		_frameCount = 0;	// 0���� �ʱ�ȭ
	}
}
