#include "pch.h"
#include <fstream>
#include <sstream>
#include "Sprite.h"
#include "JSONSetting.h"
#include "AnimationClip.h"
#include "AnimClipLoader.h"
#include "Utility.h"

AnimationClip* AnimClipLoader::LoadClip(string filePath)
{
	AnimationClip* ret = new AnimationClip();


	std::ifstream f(filePath);
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();

	//todo : sprite에 sheetFilePath 추가

	rapidjson::Document jsonDoc;

	assert(!jsonDoc.Parse(buffer.str().c_str()).HasParseError());
	//이어서 데이터 넣기


	for (auto frame = jsonDoc.MemberBegin(); frame != jsonDoc.MemberEnd(); frame++)
	{
		Sprite* sprite = new Sprite(L"", { 0,0 }, 0, 0, { 0,0 },0.0f,1.0f);
		for (auto info = frame->value.MemberBegin(); info != frame->value.MemberEnd(); info++)
		{
			if (info->name == "sheetFilePath")
				sprite->sheetFilePath = Utility::ToWstring(info->value.GetString());
			else if (info->name == "oriPos")
			{
				sprite->oriPos.x = info->value.GetArray()[0].GetFloat();
				sprite->oriPos.y = info->value.GetArray()[1].GetFloat();
			}
			else if (info->name == "oriSize")
			{
				sprite->oriWidth = info->value.GetArray()[0].GetInt();
				sprite->oriHeight = info->value.GetArray()[1].GetInt();
			}
			else if (info->name == "size")
			{
				sprite->width = info->value.GetArray()[0].GetInt();
				sprite->height = info->value.GetArray()[1].GetInt();
			}
			else if (info->name == "pivot")
			{
				sprite->pivot.x = info->value.GetArray()[0].GetFloat();
				sprite->pivot.y = info->value.GetArray()[1].GetFloat();
			}
			else if (info->name == "delayTime")
				sprite->delayTime = info->value.GetFloat();
			else if (info->name == "opacity")
				sprite->opacity = info->value.GetFloat();
		}

		ret->SetSpriteAnimData(sprite);
	}

	return ret;
}
