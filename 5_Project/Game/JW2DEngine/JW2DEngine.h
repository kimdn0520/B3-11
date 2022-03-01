#pragma once

// Direct2D 동작 순서
// 1. ID2D1Factory를 생성
// 2. WICFactory를 생성
// 3. ID2D1HwndRenderTarget을 생성
// 4. 브러시, 리소스 생성 및 RenderTarget에 지정
// 5. 리소스 해제(Factory 등..) - 모든 사용이 끝났을 때만 하면 된다.

#pragma comment(lib, "d2d1.lib")	// Direct2D API를 사용하기 위해서 참조해야 하는 라이브러리
#pragma comment(lib, "dwrite.lib")	// writefactory를 쓰기 위해 참조해야하는 라이브러리
#pragma comment(lib, "windowscodecs.lib") // WIC를 쓰기 위해 참조해야하는 라이브러리

// MK2. Effect를 사용하기 위한 DeviceContext를 위해서는 D3D11을 사용해야 한다. (정확히는 DXGI가 필요하다)
#pragma comment(lib, "d3d11.lib")			// D3D11
#pragma comment(lib, "dxguid.lib")			// DXGI

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <d2d1_1.h>
#include <d3d11.h>			
#include <dxgi1_2.h>		
#include "d2d1effects_2.h"

#include "DRMacro.h"
#include "Timer.h"
#include "Input.h"
#include "SceneManager.h"
#include "SoundManager.h"

class GameObject;
class Sprite;
class Transform;

using namespace D2D1;

class JW2DEngine
{
public:
	JW2DEngine();
	~JW2DEngine();

public:
	const WindowInfo& GetWindow() { return _window; }
	
	void Init(const WindowInfo& info);

	void BeginRender();
	void EndRender();

	void DrawTextScreen(int x, int y, int width, int height, float rotation, const char* str, ...);
	void DrawBackGroundScreen();
	void DrawGridScreen(int interval, float thick);
	void DrawCircleScreen(int x, int y, int radius);
	void DrawFillCircleScreen(int x, int y, int radius);
	void DrawRectScreen(int x1, int y1, int x2, int y2);
	void DrawFillRectScreen(int x1, int y1, int x2, int y2);
	void DrawLine(POINT point1, POINT point2);

	void SetTransform(Matrix transformMatrix);

	GameObject* GetMainCamera() { return _mainCamera; }
	void SetMainCamera(GameObject* mainCamera);
	Transform* GetMainCameraTransform() { return _mainCameraTransform; }

    void SetBrushColor(float r, float g, float b, float a);
	void ResizeScreen(uint32 width, uint32 height);

	ID2D1SolidColorBrush*  GetBlackBrush() { return _blackBrush; }

	// 시트 형태를 불러와서 벡터에다가 저장해둘거임.
	ID2D1Bitmap* LoadSpriteSheet(wstring _filePath);
	wchar_t* ConvertCStoWCS(const char* orig);

	// 스프라이트 시트 데이터를 읽어서 스프라이트를 잘라서 객체를 생성해서 벡터에 저장할거임.
	Sprite* LoadSpriteFromSheet(wstring sheetFilePath, Vector2 oriPos, int width, int height, Vector2 pivot, float delayFrame, float opacity);
	map<wstring, Sprite*> sprites;

	// 스프라이트를 그린다.
	void DrawSprite(Sprite* sprite, Transform* transform);
	void DrawTexture(wstring _filePath, Vector2 pos);

private:
	HRESULT CreateDeviceResources();

	// 재사용할 경우 장치 release 하라는것?
	void DiscardDeviceResources();

	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	HRESULT LoadBitmapFromFile
	(
		ID2D1RenderTarget* renderTarget,
		IWICImagingFactory* IWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);


private:
	WindowInfo	  _window;
	HWND		  _hWnd;
	ID2D1Factory* _factory;

	// Direct2D를 사용하여 프로그램을 할 때 이미지 파일에서
	// 이미지를 읽거나 저장하려면 WIC를 사용한다.
	IWICImagingFactory* _WICFactory;
	IDWriteFactory*     _writeFactory;			// 모든 후속 DirectWrite 객체를 만드는데 사용
	IDWriteTextFormat*  _textFormat;			// 폰트 및 단락 특성, 로케일 정보를 설명하는 인터페이스
	IWICBitmapFlipRotator* _flipRotator;		// 회전하거나 반전시킬수 있대욤 어케쓰는거임?

	// Factory 객체로 리소스 생성이 가능한 여건을 만들었다면
	// 이러한 리소스를 어디에 그릴 것인지 대상을 지정해야 한다. 그게 RenderTarget 임
	ID2D1HwndRenderTarget* _renderTarget;		// 그리기 명령을 렌더링하는 객체
	ID2D1DeviceContext* _deviceContext;			// 이펙트를 위한 디바이스콘텍스트
	ID2D1PathGeometry* _pathGeometry;			// 간단한, 또는 복잡한 도형을 나타내는 객체
	ID2D1LinearGradientBrush* _linearGradientBrush;	// 선형 그라데이션을 사용해서 만들 브러쉬 객체
	ID2D1RadialGradientBrush* _radialGradientBrush;	// 대충 가운데에 그라데이션 해주는 것같은데?

	// DeviceContext를 쓰기위한 것들...
	// 할라했는데요... Resize 함수가 없어서 안할래요 물론 이펙트효과가 필요하다면 다시 해볼게염
	//ID2D1DeviceContext* _deviceContext;		    // RenderTarget대신 사용할 DC. 사실 상속한 것이다.
	//D3D_FEATURE_LEVEL _featureLevel;			// 어디까지 기능을 지원하는가? Cached renderer properties.
	//ID2D1Device* _D2DDevice1;					// D2D디바이스
	//IDXGISwapChain1* _swapChain;
	//ID2D1Bitmap1* _D2DTargetBitmap;
	//ID2D1Factory1* _D2DFactory1;				// MK2. 이펙트를 지원하기 위해서, Device Context를 사용해야 하고, Factory의 버전업이 필요함.
	//float _dpi;
	
	ID2D1SolidColorBrush* _blackBrush;			// 검정색
	ID2D1SolidColorBrush* _nowBrush;			// 현재 brush
	
	ID2D1Bitmap* _bitmap;
	ID2D1Bitmap* _anotherBitmap;

	// [map] Sprite Sheets들의 모임. 여기서 Sprite를 잘라서 사용한다.
	map<wstring , ID2D1Bitmap*> _spriteSheets;//A재우 : const wchar_t*에서 wstring으로 바꿈 const wchar_t*로 하니 포인터 비교로 해서 문자열 비교가 안됨..

	// 메인 카메라
	// 카메라 컴포넌트를 추가할때 SetMainCamera로 메인카메라 등록을 시켜준다음
	// SetTransform 값을 카메라에 맞게 조정한다.
	GameObject* _mainCamera;
	Transform* _mainCameraTransform;

	//동훈님 여기 쓰세요~ 1.0f가 원래 배율입니다~ 0.5f 50퍼센트, 0.1f 10퍼센트 이런식예요~
	float scalerXXX = 1.0f;//<- 숫자 변경
};

