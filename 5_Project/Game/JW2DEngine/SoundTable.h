#pragma once

#include "JSONSetting.h"

/// <summary>
/// Sound JSON ���� ����
/// </summary>
class SoundTable : public JSONSetting
{
public:
	SoundTable();
	virtual ~SoundTable() {};

	std::list<SoundTable*>& DataList() { return _datas; }	// �����͵��� ���� ����Ʈ
public:
	virtual bool Deserialize(const std::string& s);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const{ return false; };
	virtual bool DataSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const{ return false; };

private:
	std::list<SoundTable*> _datas;

public:
	string soundName[20];
	string fileRoot[20];
	string loop[20];
	int dataCount;
};

