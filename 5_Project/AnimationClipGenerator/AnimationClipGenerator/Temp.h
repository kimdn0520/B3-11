#pragma once



// Temp

class Temp : public CWinThread
{
	DECLARE_DYNCREATE(Temp)

protected:
	Temp();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Temp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


