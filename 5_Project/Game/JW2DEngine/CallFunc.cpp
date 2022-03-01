#include "pch.h"
#include "CallFunc.h"

CallFunc::CallFunc(void (*func)())
{
	_func = func;
}
