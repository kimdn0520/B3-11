#pragma once
// 1. CallFuncŬ������ �ν��Ͻ��� �����.
// - �ݹ� �Լ��� ����� �Լ��� �Ű������� �����Ѵ�.

// 2. EventManager�� �ν��Ͻ��� ����Ѵ�.

// 3. event�� �����Ų��.

// 4. EventManager�� ���� �Ǹ� ��ϵ� CallFunc�� �ν��Ͻ��� ���۽�Ų��.

// 5. �ݹ� �Լ��� ����ȴ�.

class MonoBehaviour;

class EventManager
{
	DECLARE_SINGLE(EventManager);

private:
	// vector<CallFunc*> _events;				// ���� �̺�Ʈ�� ����
	//map<string, void(*)(ColliderBase*)> _events;

public:
	// void Instance(CallFunc* func);			// �̺�Ʈ�� �־��� �Լ�
	//void Instance(string str, MonoBehaviour* monoBehaviour);

	//vector<CallFunc*> GetEvent() { return _events; }
	//map<string, void(*) (ColliderBase*)> GetEvent() { return _events; }
};

