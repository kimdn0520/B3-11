#include "pch.h"
#include "OnCollisionEnter.h"

OnCollisionEnter::OnCollisionEnter(void(*func)())
{
	_func = func;
}

void OnCollisionEnter::Stop()
{
	_func();		// �ݹ��Լ��� ȣ���Ѵ�.
}
