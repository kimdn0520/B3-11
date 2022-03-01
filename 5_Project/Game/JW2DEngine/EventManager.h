#pragma once
// 1. CallFunc클래스의 인스턴스를 만든다.
// - 콜백 함수로 사용할 함수를 매개변수로 생성한다.

// 2. EventManager에 인스턴스를 등록한다.

// 3. event를 실행시킨다.

// 4. EventManager는 때가 되면 등록된 CallFunc의 인스턴스를 동작시킨다.

// 5. 콜백 함수가 실행된다.

class MonoBehaviour;

class EventManager
{
	DECLARE_SINGLE(EventManager);

private:
	// vector<CallFunc*> _events;				// 모은 이벤트를 저장
	//map<string, void(*)(ColliderBase*)> _events;

public:
	// void Instance(CallFunc* func);			// 이벤트를 넣어줄 함수
	//void Instance(string str, MonoBehaviour* monoBehaviour);

	//vector<CallFunc*> GetEvent() { return _events; }
	//map<string, void(*) (ColliderBase*)> GetEvent() { return _events; }
};

