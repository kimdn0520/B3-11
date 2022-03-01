/// [JW2DEngine]

#include "pch.h"
#include "JW2DEngine.h"
#include "GameProcess.h"
#include "SceneManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	char	 szAppName[] = "JW2DEngine";
	HWND     hWnd;
	MSG	  	 msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	/// 윈도 클래스 등록
	RegisterClass(&wndclass);

	/// 윈도 생성
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	/// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	WindowInfo windowInfo;
	windowInfo.hWnd = hWnd;
	windowInfo.width = SCREEN_WIDTH;
	windowInfo.height = SCREEN_HEIGHT;
	windowInfo.windowed = true;

	GameProcess* gameProcess = new GameProcess();
	gameProcess->Init(windowInfo);

	/// 메시지 루프
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
 			gameProcess->Update();
		}
	}

	SCENE_MANAGER->Release();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC		    hdc;
	PAINTSTRUCT ps; // tagPAINTSTRUCT 

	switch (message)
	{
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			GEngine->ResizeScreen(width, height);
		}
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}