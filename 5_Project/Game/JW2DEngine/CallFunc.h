#pragma once

class CallFunc
{
public:
	CallFunc(void (*func)());

private:
	void (*_func)();	// �Լ������͸� ��������� ������.
};

