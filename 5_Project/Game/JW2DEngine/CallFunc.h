#pragma once

class CallFunc
{
public:
	CallFunc(void (*func)());

private:
	void (*_func)();	// 함수포인터를 멤버변수로 가진다.
};

