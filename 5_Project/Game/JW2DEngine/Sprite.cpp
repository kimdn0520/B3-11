#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(wstring sheetFilePath, Vector2 oriPos, int oriWidth, int oriHeight, Vector2 pivot, float delayTime, float opacity)
	: 
	sheetFilePath(sheetFilePath),
	oriPos(oriPos),
	oriWidth(oriWidth),
	oriHeight(oriHeight),
	pivot(pivot),
	delayTime(delayTime),
	opacity(opacity),
	width(oriWidth),				// ����Ʈ�� ������ �ϴ� ���󰣴�.
	height(oriHeight)				// ����Ʈ�� ������ �ϴ� ���󰣴�.
{}

Sprite::~Sprite()
{}
