#pragma once

#include "Event.h"

class OnCollisionEnter : public Event
{
public:
	OnCollisionEnter(void(*func)());
	virtual void Stop();

private:
	void(*_func)();			// �Լ� �����͸� ��� ������ ������.
};

