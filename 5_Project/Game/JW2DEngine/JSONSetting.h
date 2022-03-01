#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"		
#include "rapidjson\stringbuffer.h"	 
#include "rapidjson\prettywriter.h"	

/// <summary>
/// JSON 파일을 가져와서 Serialize, Deserialize 하기 위한 클래스 생성
/// </summary>
class JSONSetting
{
public:
	bool DeserializeFromFile(const std::string& filePath);	// JSON파일 불러오기
	bool SerializeToFile(const std::string& filePath);	// JSON파일 생성

	virtual std::string Serialize() const;	// 문자열 버퍼 생성 후 시리얼라이즈
	virtual bool Deserialize(const std::string& s);	// 리스트에 문자열 저장
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;	// 문자열을 직렬화
	virtual bool DataDeserialize(const rapidjson::Value& obj) { return false; };	// 문자열을 잘라내는 곳
	virtual bool DataSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const { return false; };	 // 키와 값으로 나누어 쓰는 곳
protected:
	bool InitDocument(const std::string& s, rapidjson::Document& doc);
};