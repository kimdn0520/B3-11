#include "pch.h"
#include "JSONSetting.h"

#include <fstream>
#include <sstream>


std::string JSONSetting::Serialize() const
{
	rapidjson::StringBuffer ss;
	rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
	if (Serialize(&writer))
		return ss.GetString();
	return "";
}

bool JSONSetting::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	DataDeserialize(doc);

	return true;
}

bool JSONSetting::DeserializeFromFile(const std::string& filePath)
{
	std::ifstream f(filePath);
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return Deserialize(buffer.str());
}

bool JSONSetting::SerializeToFile(const std::string& filePath)
{
	std::ofstream f(filePath);
	std::string s = Serialize();
	f << s;
	f.flush();
	f.close();

	return true;
}

bool JSONSetting::InitDocument(const std::string& s, rapidjson::Document& doc)
{
	if (s.empty())
		return false;

	//std::string validJson(s);

	return !doc.Parse(s.c_str()).HasParseError() ? true : false;
}
