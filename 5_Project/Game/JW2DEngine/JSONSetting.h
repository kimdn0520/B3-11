#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"		
#include "rapidjson\stringbuffer.h"	 
#include "rapidjson\prettywriter.h"	

/// <summary>
/// JSON ������ �����ͼ� Serialize, Deserialize �ϱ� ���� Ŭ���� ����
/// </summary>
class JSONSetting
{
public:
	bool DeserializeFromFile(const std::string& filePath);	// JSON���� �ҷ�����
	bool SerializeToFile(const std::string& filePath);	// JSON���� ����

	virtual std::string Serialize() const;	// ���ڿ� ���� ���� �� �ø��������
	virtual bool Deserialize(const std::string& s);	// ����Ʈ�� ���ڿ� ����
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;	// ���ڿ��� ����ȭ
	virtual bool DataDeserialize(const rapidjson::Value& obj) { return false; };	// ���ڿ��� �߶󳻴� ��
	virtual bool DataSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const { return false; };	 // Ű�� ������ ������ ���� ��
protected:
	bool InitDocument(const std::string& s, rapidjson::Document& doc);
};