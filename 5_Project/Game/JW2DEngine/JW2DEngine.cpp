#include "pch.h"
#include "JW2DEngine.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

JW2DEngine::JW2DEngine()
	: _hWnd(nullptr), _factory(nullptr), _WICFactory(nullptr),
	_writeFactory(nullptr), _renderTarget(nullptr), _textFormat(nullptr),
	_pathGeometry(nullptr), _linearGradientBrush(nullptr), _blackBrush(nullptr),
	_nowBrush(nullptr), _bitmap(nullptr), _anotherBitmap(nullptr), _mainCamera(nullptr)
{}

JW2DEngine::~JW2DEngine()
{
	SafeRelease(&_factory);

	//SAFE_RELEASE �ӽù������� ��ħ... �� ���μ������� ��ü 2���� �������� �� wicFactory�� �����ؼ� �Ҹ��� 2�� �ҷ��� ���� �� ���� ������,
	//���Ҵ��ϰ� �ٽ� release�ϴ� ��������...
	CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void**>(&_WICFactory)
	);

	SafeRelease(&_WICFactory);
	SafeRelease(&_writeFactory);
	SafeRelease(&_renderTarget);
	SafeRelease(&_textFormat);
	SafeRelease(&_pathGeometry);
	SafeRelease(&_linearGradientBrush);
	SafeRelease(&_blackBrush);
	SafeRelease(&_bitmap);
	SafeRelease(&_anotherBitmap);
	SOUND_MANAGER->Release();
}

void JW2DEngine::Init(const WindowInfo& info)
{
	_window = info;
	_hWnd = info.hWnd;		// �ڵ��� �޾��ش�.


	HRESULT hr = S_OK;
	static const WCHAR msc_fontName[] = L"�ü�";
	static const FLOAT msc_fontSize = 20;
	ID2D1GeometrySink* pSink = NULL;

	// �̱� ������� factory ��ü�� �����Ѵ�.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);

	if (SUCCEEDED(hr))
	{
		// WIC ��ü�� �����ϱ� ���� CoCreateInstance �Լ���  ����.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&_WICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// fliprotator �� �����Ѵ�.
		hr = _WICFactory->CreateBitmapFlipRotator(&_flipRotator);
	}

	if (SUCCEEDED(hr))
	{
		// writeFactory ��ü ����
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(_writeFactory),
			reinterpret_cast<IUnknown**>(&_writeFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// textFomat ��ü ����
		hr = _writeFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&_textFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// pathGeometry ��ü ����
		hr = _factory->CreatePathGeometry(&_pathGeometry);
	}

	if (SUCCEEDED(hr))
	{
		// sink�� ����Ͽ� pathgeomatry�� ����Ѵ�.
		hr = _pathGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr))
	{
		pSink->SetFillMode(D2D1_FILL_MODE_ALTERNATE); // ä��� ��� Alternate�� Winding�� �ִ�.

		// sink ��ü�� Path�� �����Ѵ�.
		pSink->BeginFigure(
			D2D1::Point2F(0, 0),
			D2D1_FIGURE_BEGIN_FILLED
		);

		pSink->AddLine(D2D1::Point2F(200, 0));

		pSink->AddBezier(
			D2D1::BezierSegment(
				D2D1::Point2F(150, 50),
				D2D1::Point2F(200, 200),
				D2D1::Point2F(200, 200)
			)
		);

		pSink->AddLine(D2D1::Point2F(0, 200));

		pSink->AddBezier(
			D2D1::BezierSegment(
				D2D1::Point2F(50, 150),
				D2D1::Point2F(50, 50),
				D2D1::Point2F(0, 0))
		);

		// sink ��ü�� ����Ͽ� Path ������ �����Ѵ�.
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
	}

	// init �Ҷ� _renderTarget ����Ÿ���� �����д� ��������Ʈ��Ʈ �ҷ����°Ͷ�����... ���ٰ�� �������� ��
	if (SUCCEEDED(hr))
		CreateDeviceResources();

	SafeRelease(&pSink);
}

void JW2DEngine::BeginRender()
{
	HRESULT hr;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr) && !(_renderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		// ���� Ÿ�� ����� ��ã�ƿ�
		D2D1_SIZE_F renderTargetSize = _renderTarget->GetSize();

		_renderTarget->BeginDraw();

		_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}
}

void JW2DEngine::EndRender()
{
	HRESULT hr = _renderTarget->EndDraw();

	// �ڿ��� �����ؾ� �� ���
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
}

/// <summary>
/// ������ �ڵ��ε� ���ذ� �Ȱ���. ������ ��..
/// </summary>
void JW2DEngine::DrawTextScreen(int x, int y, int width, int height, float rotation, const char* str, ...)
{
	// SetTransform(Matrix::Rotation(rotation, { 0,0 }));		// �ٽ� �ʱ�ȭ �������.

	// ���� ���� ó��
	char* buffer;
	int len;

	va_list ap;			// ���� �а� �ִ� ������ ���
	va_start(ap, str);  // ap ������ ������ ù��° �����μ��� ����Ű���� �ʱ�ȭ

	len = _vscprintf(str, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, str, ap);
	va_end(ap);

	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// �翬�� ��Ƽ����Ʈ�� �����ڵ��� ���ڿ� ���� ���̰� �ִ�. 2����Ʈ ���� ��
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	_renderTarget->DrawTextW(
		unicodestr,
		wcslen(unicodestr),
		_textFormat,
		D2D1::RectF((float)x - (width / 2), (float)y - (height / 2), (float)(x + width / 2), (float)(y + height / 2)), // 700 40
		_blackBrush
	);

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// ���˰��� ���� ����
	delete[] buffer;
}

void JW2DEngine::DrawBackGroundScreen()
{
	D2D1_SIZE_F renderTargetSize = _renderTarget->GetSize();

	_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::BurlyWood));
}

void JW2DEngine::DrawGridScreen(int interval, float thick)
{
	D2D1_SIZE_F renderTargetSize = _renderTarget->GetSize();

	// Draw a grid background.
	int width = static_cast<int>(renderTargetSize.width);
	int height = static_cast<int>(renderTargetSize.height);

	for (int x = 0; x < width; x += interval)
	{
		_renderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), renderTargetSize.height),
			_blackBrush,
			thick
		);
	}

	for (int y = 0; y < height; y += interval)
	{
		_renderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(renderTargetSize.width, static_cast<FLOAT>(y)),
			_blackBrush,
			thick
		);
	}
}

void JW2DEngine::DrawCircleScreen(int x, int y, int radius)
{
	D2D1_ELLIPSE circle;
	circle.point.x = (float)x;
	circle.point.y = (float)y;
	circle.radiusX = (float)(radius);
	circle.radiusY = (float)(radius);

	_renderTarget->DrawEllipse(circle, _nowBrush, 2.0f);
}

void JW2DEngine::DrawFillCircleScreen(int x, int y, int radius)
{
	D2D1_ELLIPSE circle;
	circle.point.x = (float)x;
	circle.point.y = (float)y;
	circle.radiusX = (float)(radius);
	circle.radiusY = (float)(radius);

	_renderTarget->FillEllipse(circle, _nowBrush);
}

void JW2DEngine::DrawRectScreen(int x1, int y1, int x2, int y2)
{
	D2D1_RECT_F rt;
	rt.left = (float)x1;
	rt.top = (float)y1;
	rt.right = (float)x2;
	rt.bottom = (float)y2;

	_renderTarget->DrawRectangle(rt, _nowBrush, 2.0f);
}

void JW2DEngine::DrawFillRectScreen(int x1, int y1, int x2, int y2)
{
	D2D1_RECT_F rt;
	rt.left = (float)x1;
	rt.top = (float)y1;
	rt.right = (float)x2;
	rt.bottom = (float)y2;

	_renderTarget->FillRectangle(rt, _nowBrush);
}

void JW2DEngine::DrawLine(POINT point1, POINT point2)
{
	D2D1_POINT_2F pt1;
	pt1.x = (float)point1.x;
	pt1.y = (float)point1.y;
	D2D1_POINT_2F pt2;
	pt2.x = (float)point2.x;
	pt2.y = (float)point2.y;


	Matrix scaler = Matrix::Identity();
	scaler.m11 = scalerXXX;
	scaler.m22 = scalerXXX;


	// ����� ��ġ�� �ش� ���ӿ�����Ʈ�� Ʈ�������� �޾Ƽ� �����´�.
	// ��� pivot��(0.5f 0.5f) �̴�.
	SetTransform(scaler);

	_renderTarget->DrawLine(pt1, pt2, _nowBrush, 1.0f);
}

void JW2DEngine::SetTransform(Matrix transformMatrix)
{
	// ī�޶� �ִٸ�
	if (_mainCamera != nullptr)
	{
		Matrix mainCameraMat = _mainCamera->GetComponent<Transform>()->GetWorldMatrix();
		mainCameraMat.dx -= SCREEN_WIDTH / 2;
		mainCameraMat.dy -= SCREEN_HEIGHT / 2;

		transformMatrix.dx -= mainCameraMat.dx;
		transformMatrix.dy -= mainCameraMat.dy;
	}

	_renderTarget->SetTransform(transformMatrix);
}

void JW2DEngine::SetMainCamera(GameObject* mainCamera)
{
	_mainCamera = mainCamera;
	
	if(_mainCamera != nullptr)
		_mainCameraTransform = _mainCamera->GetComponent<Transform>();
}

void JW2DEngine::SetBrushColor(float r, float g, float b, float a)
{
	SafeRelease(&_nowBrush);

	_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &_nowBrush);
}

void JW2DEngine::ResizeScreen(uint32 width, uint32 height)
{
	if (_renderTarget)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;

		_renderTarget->Resize(size);
	}
}

ID2D1Bitmap* JW2DEngine::LoadSpriteSheet(wstring filePath)
{
	HRESULT _hr = S_OK;
	ID2D1Bitmap* newSheet = nullptr;

	// ���� ��θ� �о� ��Ʈ���� �ҷ��´�.

	if (_spriteSheets.find(filePath) == _spriteSheets.end())
	{
		_hr = LoadBitmapFromFile(
			_renderTarget,
			_WICFactory,
			filePath.c_str(),
			0,
			0,
			&newSheet
		);

		// �����ߴٸ� ��������Ʈ ��Ʈ�� ��Ƴ��� ���Ϳ� ����
		if (SUCCEEDED(_hr))
			_spriteSheets[filePath] = newSheet;

	}

	return _spriteSheets[filePath];
}

wchar_t* JW2DEngine::ConvertCStoWCS(const char* orig)
{
	// newsize describes the length of the
	// wchar_t string called wcstring in terms of the number
	// of wide characters, not the number of bytes.
	size_t newsize = strlen(orig) + 1;

	// The following creates a buffer large enough to contain
	// the exact number of characters in the original string
	// in the new format. If you want to add more characters
	// to the end of the string, increase the value of newsize
	// to increase the size of the buffer.
	wchar_t* wcstring = new wchar_t[newsize];

	// Convert char* string to a wchar_t* string.
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}

Sprite* JW2DEngine::LoadSpriteFromSheet(wstring sheetFilePath, Vector2 oriPos, int width, int height, Vector2 pivot, float delayFrame, float opacity)
{
	wstring key = {};
	key = sheetFilePath + L"_"  + to_wstring(oriPos.x) + L"_" + to_wstring(oriPos.y) + L"_" + to_wstring(width) + L"_" + to_wstring(height) + L"_" + to_wstring(pivot.x) + L"_" + to_wstring(pivot.y) + L"_" + to_wstring(delayFrame) + L"_" + to_wstring(opacity);

	if (sprites.find(key) == sprites.end())
	{
		sprites[key] = new Sprite(sheetFilePath, oriPos, width, height, pivot, delayFrame, opacity);
	}

	return sprites[key];
}

void JW2DEngine::DrawSprite(Sprite* sprite, Transform* transform)
{
	// ��������Ʈ�� �����߿��� ��Ʈ�� ������ �����´�.
 	ID2D1Bitmap* _sheet = LoadSpriteSheet(sprite->sheetFilePath);

	/*if (_mainCamera->GetComponent<Transform>()->GetLocalPosition().x - (SCREEN_WIDTH / 2) < transform->GetWorldPosition().x || )
	{
		return;
	}*/

	if (_sheet != NULL)
	{
		// pivot(0, 0) �� ��ġ���ѵΰ�(������) width, height�� pivot���� ���Ѱ���ŭ �����ָ� �ȴ�. 
		Matrix tmpMatrix = transform->GetWorldMatrix();
		tmpMatrix.dx -= (sprite->width / 2);
		tmpMatrix.dy -= (sprite->height / 2);
		tmpMatrix.dx += (sprite->width * sprite->pivot.x);
		tmpMatrix.dy += (sprite->height * sprite->pivot.y);
		
		Matrix scaler = Matrix::Identity();
		scaler.m11 = scalerXXX;
		scaler.m22 = scalerXXX;

		tmpMatrix = tmpMatrix * scaler;

		// ����� ��ġ�� �ش� ���ӿ�����Ʈ�� Ʈ�������� �޾Ƽ� �����´�.
		// ��� pivot��(0.5f 0.5f) �̴�.
		SetTransform(tmpMatrix);


		// Ʈ�������� ���彺���Ͽ� ���� ũ�Ⱑ �ٲ��.
		// Ʈ�������� ũ�� �ٲٸ� �翬�� �˾Ƽ� �ٲ�
		_renderTarget->DrawBitmap(_sheet,
			D2D1::RectF(
				(float)-(sprite->width / 2),
				(float)-(sprite->height / 2),
				(float)(sprite->width / 2),
				(float)(sprite->height / 2)),
			sprite->opacity,									// ������ ���� ��
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((float)sprite->oriPos.x, (float)sprite->oriPos.y, (float)(sprite->oriPos.x + sprite->oriWidth), (float)(sprite->oriPos.y + sprite->oriHeight))
		);
	}
}

void JW2DEngine::DrawTexture(wstring _filePath, Vector2 pos)
{
	ID2D1Bitmap* _sheet = LoadSpriteSheet(_filePath);
	if (_sheet != NULL)
	{
		SetTransform(D2D1::Matrix3x2F::Identity());
		_renderTarget->DrawBitmap(_sheet,
			D2D1::RectF(
				pos.x - (_sheet->GetPixelSize().width / 2),
				pos.y - (_sheet->GetPixelSize().height / 2),
				pos.x + (_sheet->GetPixelSize().width / 2),
				pos.y + (_sheet->GetPixelSize().height / 2)), 1.0f);
	}
}

/// <summary>
/// �� factory ��ü�� CreateHwndRenderTarget �޼��带 ����� _renderTarget ��ü ����
/// �� �� ��° ���ڿ�  D2D1_HWND_RENDER_TARGET_PROPERTIES ����ü�� ��ȯ�ϴ� �Լ��� �ۼ��ϰ�, 
///    �� ���ڷ� ������ �ڵ�� ������ Ŭ���̾�Ʈ ������ ũ�⸦ ����� �ִ´�.
/// �� CreateHwndRenderTarget �޼����� ������ ���ڷ� ������ HwndRenderTarget ��ü�� ���� �����͸� �����Ѵ�.
/// �� ��ȯ������ �޾ƿͼ� BeginRender���� �� �� �ֵ��� ���ش�.
/// �� D2D1_PRESENT_OPTIONS_IMMEDIATELY �� ���ϸ� NONE���ε���Ʈ�� ���µ� 60fps ������ �ȴ�.
///    Ǯ������� IMMEDIATELY�� ���ָ� �ȴ�.
/// </summary>
HRESULT JW2DEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!_renderTarget)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);	// Ŭ���̾�Ʈ ������ ��ǥ�� ��´�.

		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);

		// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target ����
		hr = _factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(_hWnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&_renderTarget
		);
		if (SUCCEEDED(hr))
		{
			// ������ �귯���� �����.
			hr = _renderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&_blackBrush
			);

			// ���� ������ �ִ°͵� ����Ʈ�� ������ ����
			hr = _renderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&_nowBrush
			);
		}

		if (SUCCEEDED(hr))
		{
			ID2D1GradientStopCollection* pGradientStops = NULL;
			// Create a linear gradient.
			static const D2D1_GRADIENT_STOP stops[] =
			{
				{   0.f,  { 0.f, 1.f, 1.f, 0.25f }  },
				{   1.f,  { 0.f, 0.f, 1.f, 1.f }  },
			};

			// LinearGradientBrush ��ü�� �����Ϸ��� GradientStopCollection�� �����ؾ� ��.
			hr = _renderTarget->CreateGradientStopCollection(
				stops,
				ARRAYSIZE(stops),
				&pGradientStops
			);

			// Brush ��ü�� �����Ǿ��ٸ� GradientStopCollection ��ü��
			// ������ �ʿ䰡 ���� ������ �ٷ� �����ص� �˴ϴ�.
			if (SUCCEEDED(hr))
			{
				hr = _renderTarget->CreateLinearGradientBrush(
					D2D1::LinearGradientBrushProperties(
						D2D1::Point2F(100, 0),
						D2D1::Point2F(100, 200)),
					D2D1::BrushProperties(),
					pGradientStops,
					&_linearGradientBrush
				);

				// Brush ��ü�� ��������� �����ߴ� Gradient Stop Collection ��ü�� �����Ѵ�. 
				pGradientStops->Release();
			}
		}
	}

	return hr;
}

void JW2DEngine::DiscardDeviceResources()
{
	SafeRelease(&_renderTarget);
	SafeRelease(&_bitmap);
	SafeRelease(&_blackBrush);
	SafeRelease(&_linearGradientBrush);
	SafeRelease(&_anotherBitmap);
}

/// <summary>
/// Resource ������ �߰��� png ������ ������ �ҷ����°ǵ�
/// ���� ������..? �ϴ� ����
/// </summary>
HRESULT JW2DEngine::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// FindResourceW ���ҽ� ��ġ�� ã�� �ڵ��� ��ȯ�Ѵ�.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// ���ҽ��� �ε��Ѵ�.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}

	// �ٽ� ����
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}

	// ����� �������
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}


	// ��Ʈ�� ��ü�� �����.
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}

	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}

	// ��Ʈ�� �������� ������ �����ϴ� ���ڴ�(Decoder) ��ü�� ����
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}

	// �ش� �׸��� �߿��� � �׸��� ����� ������ �����ؾ� ��
	// (���⼭ Frame�� ���� ���� �׸� �߿��� �׸� 1���� �ǹ�)
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	// GetFrame �Լ��� ���� �̹����� WIC ������ ��Ʈ��(IWICBitmap)�̱� ������ Direct2D������ �ٷ�
	// ����ϱ� ��ƴ�. �׷��� IWICBitmap ������ ��Ʈ���� Direct2D���� �ٷ� ����� �� �ֵ���
	// ID2D1Bitmap ������ ��Ʈ������ ��ȯ�ؾ� ��.
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	// ���ο� �ʺ� �Ǵ� ���̰� ������ ���
	// IWICBitmapScaler�� ����Ͽ� �̹��� ũ�⸦ ����
	if (SUCCEEDED(hr))
	{
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
		}
		else
		{
			// ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ �����Ѵ�.
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}

	// IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� �����Ѵ�. 
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

/// <summary>
/// ��ο� ����� png���� �ҷ���
/// </summary>
HRESULT JW2DEngine::LoadBitmapFromFile(ID2D1RenderTarget* renderTarget, IWICImagingFactory* IWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;			// ��Ʈ�� �������� ������ �����ϴ� ���ڴ��� �����.
	IWICBitmapFrameDecode* pSource = NULL;		// �� ���Ͽ� �������� �׸��� ���� �� �ֱ⿡ � �׸��� ������� �����Ѵ�.
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;		// IWICBitmap ������ ��Ʈ���� ID2D1Bitmap �������� ��ȯ�ϱ� ���� ������
	IWICBitmapScaler* pScaler = NULL;			// ���ڷ� ���� width, height�� ���� ��Ʈ���� �������� �����ϱ� ����.
	// ���� ��θ� �о� ���ڴ��� �����.
	hr = IWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// ������ �����ϴ� �̹��� �߿� ù ��° �̹����� �����Ѵ�.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// ID2D1Bitmap���� ��ȯ���� �����͸� �����.
		hr = IWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// ���ڷ� ���� destWidth, destHeight�� ���Ͽ� ��Ʈ���� �̹��� ����, ���θ� �����Ѵ�.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				// �ϳ��� 0���� ���ڰ� ���� ��� �̹��� �ڵ����� 0���� ���� �κп� ���Ͽ� �̹��� ����, ���� ������ ���缭 �߶��ش�.
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				// �����Ϸ��� �����.
				hr = _WICFactory->CreateBitmapScaler(&pScaler);

				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			// �� �� 0���� ������ �̹��� ũ�� �״�� ��ȯ�� �غ� �Ѵ�.
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		// IWICBitmap ������ �̹����� ID2D1Bitmap ��ü�� ��ȯ�Ͽ� �����Ѵ�.
		hr = renderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}
