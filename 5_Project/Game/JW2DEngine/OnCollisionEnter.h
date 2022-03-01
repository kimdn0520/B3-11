#pragma once

#include "Event.h"

class OnCollisionEnter : public Event
{
public:
	OnCollisionEnter(void(*func)());
	virtual void Stop();

private:
	void(*_func)();			// 함수 포인터를 멤버 변수로 가진다.
};

