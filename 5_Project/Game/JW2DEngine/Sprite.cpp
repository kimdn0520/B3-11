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
	width(oriWidth),				// 디폴트로 원본을 일단 따라간다.
	height(oriHeight)				// 디폴트로 원본을 일단 따라간다.
{}

Sprite::~Sprite()
{}
