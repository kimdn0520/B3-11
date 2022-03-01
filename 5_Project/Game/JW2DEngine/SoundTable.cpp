#include "pch.h"
#include "SoundTable.h"

SoundTable::SoundTable() : dataCount(0)
{
}

bool SoundTable::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	for (auto info = doc.MemberBegin(); info != doc.MemberEnd(); info++)
	{
		const rapidjson::Value& soundObjects = info->value;
		for (rapidjson::Value::ConstMemberIterator itr = soundObjects.MemberBegin(); itr != soundObjects.MemberEnd(); ++itr)
		{
			if (itr->name == "Name")
			{
				soundName[dataCount] = itr->value.GetString();
			}
			else if (itr->name == "FileRoot")
			{
				fileRoot[dataCount] = itr->value.GetString();
			}
			else if (itr->name == "Loop")
			{
				loop[dataCount] = itr->value.GetString();
				dataCount++;
			}
		}
	}

	return true;
}