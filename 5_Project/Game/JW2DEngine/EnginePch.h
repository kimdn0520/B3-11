#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <time.h>
#include <array>
#include <functional>
#include "Vector2.h"
#include <cstdio>
#include <list>
#include <random>
#include <d2d1helper.h>	// D2D1  ������..
using namespace std;

#pragma comment(lib, "JW2DEngine.lib")

// typedef
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Matrix = D2D1::Matrix3x2F;

struct WindowInfo
{
	HWND	hWnd; // ��� ������
	int32	width; // �ʺ�
	int32	height; // ����
	bool	windowed; // â��� or ��üȭ��
};

class ColliderBase;
struct Info
{
	Vector2 reflectVec;
	Vector2 velocityVec;
	ColliderBase* otherCol;
	float compNum;
	int colDir;
};

enum class TAG
{
	Player,
	HeadTrigger,
	Enemy,
	Item,
	Bullet,
	Ground,
	MovableGround,
	GetThroughGround,
	PassHurdle,
	Hurdle,
	BrokenWall,
	Portal,
	OBB,
	UI,
	NONE,//ajw �ٲ۰�
	SPRITE,
	COLLIDER,
	SavePoint,
	ANGRYMOTION,
	FallGround,
};

// Rigidbody bodytype ����
enum class BODY_TYPE
{
	Dynamic,
	Kinematic,
	Static
};

// �ݶ��̴� �ε��� ����? ����
enum class COL_DIR//DOWN = 0, LEFT = 1, RIGHT = 2, UP = 3
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
};

// ��ư�� ����
enum class ButtonStatus
{
	NORMAL,		// �Ϲ�
	HIGHLIGHT,	// ���콺�� ���� ���� ��
	PRESSED,
};

// define 
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

#define GET_SINGLE(type)	type::GetInstance()

#define INPUT				GET_SINGLE(Input)
#define TIMER				GET_SINGLE(Timer)
#define SCENE_MANAGER		GET_SINGLE(SceneManager)
#define SOUND_MANAGER		GET_SINGLE(SoundManager)
#define EVENT_MANAGER		GET_SINGLE(EventManager)
#define DELTA_TIME			GET_SINGLE(Timer)->GetDeltaTime()

extern class JW2DEngine* GEngine;