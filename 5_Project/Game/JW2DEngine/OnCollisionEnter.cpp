#include "pch.h"
#include "OnCollisionEnter.h"

OnCollisionEnter::OnCollisionEnter(void(*func)())
{
	_func = func;
}

void OnCollisionEnter::Stop()
{
	_func();		// 콜백함수를 호출한다.
}
