#pragma once

/// <summary>
/// ��Ʈ�� ������ ������ü�� pos, ȭ�鿡 ��µ� ���� ���� ũ��,
/// pivot ����, �ִϸ��̼� ���� �ð�, ������ ���� ��
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

