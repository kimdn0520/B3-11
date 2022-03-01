#pragma once

// Direct2D ���� ����
// 1. ID2D1Factory�� ����
// 2. WICFactory�� ����
// 3. ID2D1HwndRenderTarget�� ����
// 4. �귯��, ���ҽ� ���� �� RenderTarget�� ����
// 5. ���ҽ� ����(Factory ��..) - ��� ����� ������ ���� �ϸ� �ȴ�.

#pragma comment(lib, "d2d1.lib")	// Direct2D API�� ����ϱ� ���ؼ� �����ؾ� �ϴ� ���̺귯��
#pragma comment(lib, "dwrite.lib")	// writefactory�� ���� ���� �����ؾ��ϴ� ���̺귯��
#pragma comment(lib, "windowscodecs.lib") // WIC�� ���� ���� �����ؾ��ϴ� ���̺귯��

// MK2. Effect�� ����ϱ� ���� DeviceContext�� ���ؼ��� D3D11�� ����ؾ� �Ѵ�. (��Ȯ���� DXGI�� �ʿ��ϴ�)
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

	// ��Ʈ ���¸� �ҷ��ͼ� ���Ϳ��ٰ� �����صѰ���.
	ID2D1Bitmap* LoadSpriteSheet(wstring _filePath);
	wchar_t* ConvertCStoWCS(const char* orig);

	// ��������Ʈ ��Ʈ �����͸� �о ��������Ʈ�� �߶� ��ü�� �����ؼ� ���Ϳ� �����Ұ���.
	Sprite* LoadSpriteFromSheet(wstring sheetFilePath, Vector2 oriPos, int width, int height, Vector2 pivot, float delayFrame, float opacity);
	map<wstring, Sprite*> sprites;

	// ��������Ʈ�� �׸���.
	void DrawSprite(Sprite* sprite, Transform* transform);
	void DrawTexture(wstring _filePath, Vector2 pos);

private:
	HRESULT CreateDeviceResources();

	// ������ ��� ��ġ release �϶�°�?
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

	// Direct2D�� ����Ͽ� ���α׷��� �� �� �̹��� ���Ͽ���
	// �̹����� �аų� �����Ϸ��� WIC�� ����Ѵ�.
	IWICImagingFactory* _WICFactory;
	IDWriteFactory*     _writeFactory;			// ��� �ļ� DirectWrite ��ü�� ����µ� ���
	IDWriteTextFormat*  _textFormat;			// ��Ʈ �� �ܶ� Ư��, ������ ������ �����ϴ� �������̽�
	IWICBitmapFlipRotator* _flipRotator;		// ȸ���ϰų� ������ų�� �ִ�� ���ɾ��°���?

	// Factory ��ü�� ���ҽ� ������ ������ ������ ������ٸ�
	// �̷��� ���ҽ��� ��� �׸� ������ ����� �����ؾ� �Ѵ�. �װ� RenderTarget ��
	ID2D1HwndRenderTarget* _renderTarget;		// �׸��� ����� �������ϴ� ��ü
	ID2D1DeviceContext* _deviceContext;			// ����Ʈ�� ���� ����̽����ؽ�Ʈ
	ID2D1PathGeometry* _pathGeometry;			// ������, �Ǵ� ������ ������ ��Ÿ���� ��ü
	ID2D1LinearGradientBrush* _linearGradientBrush;	// ���� �׶��̼��� ����ؼ� ���� �귯�� ��ü
	ID2D1RadialGradientBrush* _radialGradientBrush;	// ���� ����� �׶��̼� ���ִ� �Ͱ�����?

	// DeviceContext�� �������� �͵�...
	// �Ҷ��ߴµ���... Resize �Լ��� ��� ���ҷ��� ���� ����Ʈȿ���� �ʿ��ϴٸ� �ٽ� �غ��Կ�
	//ID2D1DeviceContext* _deviceContext;		    // RenderTarget��� ����� DC. ��� ����� ���̴�.
	//D3D_FEATURE_LEVEL _featureLevel;			// ������ ����� �����ϴ°�? Cached renderer properties.
	//ID2D1Device* _D2DDevice1;					// D2D����̽�
	//IDXGISwapChain1* _swapChain;
	//ID2D1Bitmap1* _D2DTargetBitmap;
	//ID2D1Factory1* _D2DFactory1;				// MK2. ����Ʈ�� �����ϱ� ���ؼ�, Device Context�� ����ؾ� �ϰ�, Factory�� �������� �ʿ���.
	//float _dpi;
	
	ID2D1SolidColorBrush* _blackBrush;			// ������
	ID2D1SolidColorBrush* _nowBrush;			// ���� brush
	
	ID2D1Bitmap* _bitmap;
	ID2D1Bitmap* _anotherBitmap;

	// [map] Sprite Sheets���� ����. ���⼭ Sprite�� �߶� ����Ѵ�.
	map<wstring , ID2D1Bitmap*> _spriteSheets;//A��� : const wchar_t*���� wstring���� �ٲ� const wchar_t*�� �ϴ� ������ �񱳷� �ؼ� ���ڿ� �񱳰� �ȵ�..

	// ���� ī�޶�
	// ī�޶� ������Ʈ�� �߰��Ҷ� SetMainCamera�� ����ī�޶� ����� �����ش���
	// SetTransform ���� ī�޶� �°� �����Ѵ�.
	GameObject* _mainCamera;
	Transform* _mainCameraTransform;

	//���ƴ� ���� ������~ 1.0f�� ���� �����Դϴ�~ 0.5f 50�ۼ�Ʈ, 0.1f 10�ۼ�Ʈ �̷��Ŀ���~
	float scalerXXX = 1.0f;//<- ���� ����
};

