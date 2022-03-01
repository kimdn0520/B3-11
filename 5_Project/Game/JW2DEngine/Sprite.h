#pragma once

/// <summary>
/// 시트의 정보와 원본객체의 pos, 화면에 출력될 가로 세로 크기,
/// pivot 정보, 애니메이션 지연 시간, 투명도에 대한 값
/// </summary>
class Sprite
{
public:
	Sprite(wstring sheetFilePath, Vector2 oriPos, int oriWidth, int oriHeight,
		Vector2 pivot, float delayTime, float opacity);
	~Sprite();

public:
	wstring sheetFilePath;
	
	Vector2 oriPos;

	int oriWidth;

	int oriHeight;

	int width;

	int height;

	Vector2 pivot;

	float delayTime;

	float opacity;
};

