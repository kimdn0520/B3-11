#pragma once

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	// 프레임 조절
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _preTime;
	LARGE_INTEGER _curTime;
	const float _frame = 0.0166666f; // 60프레임
	float _checkTime = 0.0f;

public:
	void Init(const WindowInfo& info);

	void Update();

	void MakePool();
};