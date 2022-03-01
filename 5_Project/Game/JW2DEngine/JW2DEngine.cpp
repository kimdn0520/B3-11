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

	//SAFE_RELEASE 임시방편으로 고침... 한 프로세스에서 객체 2개를 생성했을 때 wicFactory를 공유해서 소멸자 2번 불려서 에러 뜬 것을 고쳐줌,
	//재할당하고 다시 release하는 방향으로...
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
	_hWnd = info.hWnd;		// 핸들을 받아준다.


	HRESULT hr = S_OK;
	static const WCHAR msc_fontName[] = L"궁서";
	static const FLOAT msc_fontSize = 20;
	ID2D1GeometrySink* pSink = NULL;

	// 싱글 스레드로 factory 객체를 생성한다.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);

	if (SUCCEEDED(hr))
	{
		// WIC 객체를 생성하기 위해 CoCreateInstance 함수를  쓴다.
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
		// fliprotator 를 생성한다.
		hr = _WICFactory->CreateBitmapFlipRotator(&_flipRotator);
	}

	if (SUCCEEDED(hr))
	{
		// writeFactory 객체 생성
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(_writeFactory),
			reinterpret_cast<IUnknown**>(&_writeFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// textFomat 객체 생성
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

		// pathGeometry 객체 생성
		hr = _factory->CreatePathGeometry(&_pathGeometry);
	}

	if (SUCCEEDED(hr))
	{
		// sink를 사용하여 pathgeomatry에 기록한다.
		hr = _pathGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr))
	{
		pSink->SetFillMode(D2D1_FILL_MODE_ALTERNATE); // 채우기 모드 Alternate와 Winding이 있다.

		// sink 객체에 Path를 구성한다.
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

		// sink 객체를 사용하여 Path 구성을 종료한다.
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
	}

	// init 할때 _renderTarget 렌더타겟을 만들어둔다 스프라이트시트 불러오는것때문에... 없다고ㅠ 오류나서 ㅠ
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
		// 렌더 타겟 사이즈를 되찾아옴
		D2D1_SIZE_F renderTargetSize = _renderTarget->GetSize();

		_renderTarget->BeginDraw();

		_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}
}

void JW2DEngine::EndRender()
{
	HRESULT hr = _renderTarget->EndDraw();

	// 자원을 복구해야 할 경우
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
}

/// <summary>
/// 교수님 코드인데 이해가 안간다. 정리할 것..
/// </summary>
void JW2DEngine::DrawTextScreen(int x, int y, int width, int height, float rotation, const char* str, ...)
{
	// SetTransform(Matrix::Rotation(rotation, { 0,0 }));		// 다시 초기화 해줘야함.

	// 가변 인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, str);  // ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(str, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, str, ap);
	va_end(ap);

	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
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

	// 포맷관련 버퍼 삭제
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


	// 출력할 위치를 해당 게임오브젝트의 트랜스폼을 받아서 가져온다.
	// 가운데 pivot은(0.5f 0.5f) 이다.
	SetTransform(scaler);

	_renderTarget->DrawLine(pt1, pt2, _nowBrush, 1.0f);
}

void JW2DEngine::SetTransform(Matrix transformMatrix)
{
	// 카메라가 있다면
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

	// 파일 경로를 읽어 비트맵을 불러온다.

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

		// 성공했다면 스프라이트 시트를 모아놓은 벡터에 저장
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
	// 스프라이트의 정보중에서 시트의 정보를 가져온다.
 	ID2D1Bitmap* _sheet = LoadSpriteSheet(sprite->sheetFilePath);

	/*if (_mainCamera->GetComponent<Transform>()->GetLocalPosition().x - (SCREEN_WIDTH / 2) < transform->GetWorldPosition().x || )
	{
		return;
	}*/

	if (_sheet != NULL)
	{
		// pivot(0, 0) 에 위치시켜두고(왼쪽위) width, height를 pivot으로 곱한값만큼 더해주면 된다. 
		Matrix tmpMatrix = transform->GetWorldMatrix();
		tmpMatrix.dx -= (sprite->width / 2);
		tmpMatrix.dy -= (sprite->height / 2);
		tmpMatrix.dx += (sprite->width * sprite->pivot.x);
		tmpMatrix.dy += (sprite->height * sprite->pivot.y);
		
		Matrix scaler = Matrix::Identity();
		scaler.m11 = scalerXXX;
		scaler.m22 = scalerXXX;

		tmpMatrix = tmpMatrix * scaler;

		// 출력할 위치를 해당 게임오브젝트의 트랜스폼을 받아서 가져온다.
		// 가운데 pivot은(0.5f 0.5f) 이다.
		SetTransform(tmpMatrix);


		// 트랜스폼의 월드스케일에 따라서 크기가 바뀐다.
		// 트랜스폼의 크기 바꾸면 당연히 알아서 바뀜
		_renderTarget->DrawBitmap(_sheet,
			D2D1::RectF(
				(float)-(sprite->width / 2),
				(float)-(sprite->height / 2),
				(float)(sprite->width / 2),
				(float)(sprite->height / 2)),
			sprite->opacity,									// 투명도에 대한 값
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
/// ■ factory 객체의 CreateHwndRenderTarget 메서드를 사용해 _renderTarget 객체 생성
/// ■ 두 번째 인자에  D2D1_HWND_RENDER_TARGET_PROPERTIES 구조체를 반환하는 함수를 작성하고, 
///    그 인자로 윈도우 핸들과 윈도우 클라이언트 영역의 크기를 계산해 넣는다.
/// ■ CreateHwndRenderTarget 메서드의 마지막 인자로 생성된 HwndRenderTarget 객체를 담을 포인터를 전달한다.
/// ■ 반환형으로 받아와서 BeginRender에서 쓸 수 있도록 해준다.
/// ※ D2D1_PRESENT_OPTIONS_IMMEDIATELY 를 안하면 NONE으로디폴트로 들어가는데 60fps 고정이 된다.
///    풀고싶으면 IMMEDIATELY를 써주면 된다.
/// </summary>
HRESULT JW2DEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!_renderTarget)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);	// 클라이언트 영역의 좌표를 얻는다.

		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);

		// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target 생성
		hr = _factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(_hWnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&_renderTarget
		);
		if (SUCCEEDED(hr))
		{
			// 검은색 브러쉬를 만든다.
			hr = _renderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&_blackBrush
			);

			// 현재 가지고 있는것도 디폴트로 검정색 하자
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

			// LinearGradientBrush 객체를 생성하려면 GradientStopCollection을 생성해야 함.
			hr = _renderTarget->CreateGradientStopCollection(
				stops,
				ARRAYSIZE(stops),
				&pGradientStops
			);

			// Brush 객체가 생성되었다면 GradientStopCollection 객체는
			// 유지할 필요가 없기 때문에 바로 제거해도 됩니다.
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

				// Brush 객체를 만들기위해 생성했던 Gradient Stop Collection 객체를 제거한다. 
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
/// Resource 영역에 추가된 png 파일의 정보를 불러오는건데
/// 굳이 쓰려나..? 일단 두자
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

	// FindResourceW 리소스 위치를 찾아 핸들을 반환한다.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// 리소스를 로드한다.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}

	// 다시 닫음
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}

	// 사이즈를 계산해줌
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}


	// 스트림 객체를 만든다.
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

	// 비트맵 형식으로 압축을 해제하는 디코더(Decoder) 객체를 생성
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

	// 해당 그림들 중에서 어떤 그림을 사용할 것인지 선택해야 함
	// (여기서 Frame은 여러 개의 그림 중에서 그림 1개를 의미)
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	// GetFrame 함수로 얻은 이미지는 WIC 형식의 비트맵(IWICBitmap)이기 때문에 Direct2D에서는 바로
	// 사용하기 어렵다. 그래서 IWICBitmap 형식의 비트맵을 Direct2D에서 바로 사용할 수 있도록
	// ID2D1Bitmap 형식의 비트맵으로 변환해야 함.
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	// 새로운 너비 또는 높이가 지정된 경우
	// IWICBitmapScaler를 사용하여 이미지 크기를 조정
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
			// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정한다.
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

	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성한다. 
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
/// 경로에 저장된 png파일 불러옴
/// </summary>
HRESULT JW2DEngine::LoadBitmapFromFile(ID2D1RenderTarget* renderTarget, IWICImagingFactory* IWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;			// 비트맵 형식으로 압축을 해제하는 디코더를 만든다.
	IWICBitmapFrameDecode* pSource = NULL;		// 한 파일에 여러개의 그림이 있을 수 있기에 어떤 그림을 사용할지 선택한다.
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;		// IWICBitmap 형식의 비트맵을 ID2D1Bitmap 형식으로 변환하기 위한 컨버터
	IWICBitmapScaler* pScaler = NULL;			// 인자로 받은 width, height를 비교해 비트맵의 스케일을 조정하기 위함.
	// 파일 경로를 읽어 디코더를 만든다.
	hr = IWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// 파일을 구성하는 이미지 중에 첫 번째 이미지를 선택한다.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// ID2D1Bitmap으로 변환해줄 컨버터를 만든다.
		hr = IWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// 인자로 들어온 destWidth, destHeight를 비교하여 비트맵의 이미지 가로, 세로를 조절한다.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				// 하나만 0으로 인자가 들어온 경우 이미지 자동으로 0으로 들어온 부분에 대하여 이미지 가로, 세로 비율을 맞춰서 잘라준다.
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

				// 스케일러를 만든다.
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
			// 둘 다 0으로 들어오면 이미지 크기 그대로 변환할 준비를 한다.
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
		// IWICBitmap 형식의 이미지를 ID2D1Bitmap 객체로 변환하여 생성한다.
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
