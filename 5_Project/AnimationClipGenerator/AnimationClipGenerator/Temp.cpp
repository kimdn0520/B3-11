// Temp.cpp: 구현 파일
//

#include "pch.h"
#include "AnimationClipGenerator.h"
#include "Temp.h"


// Temp

IMPLEMENT_DYNCREATE(Temp, CWinThread)

Temp::Temp()
{
}

Temp::~Temp()
{
}

BOOL Temp::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int Temp::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(Temp, CWinThread)
END_MESSAGE_MAP()


// Temp 메시지 처리기
