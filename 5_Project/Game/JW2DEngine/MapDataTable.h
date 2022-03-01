#pragma once
#include "JSONSetting.h"

/// <summary>
/// MapData JSON ���� ����
/// </summary>
using namespace rapidjson;

class MapDataTable : public JSONSetting
{
public:
	MapDataTable();
	virtual ~MapDataTable() {};

public:
	virtual bool Deserialize(const std::string& s);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const{ return false; };
	virtual bool DataSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const{ return false; };
	void CheckStaticTile();
	void CheckMovableTile();
	void CheckPassTile();

private:
	std::list<MapDataTable*>& DataList() { return _datas; }	// �����͵��� ���� ����Ʈ
	int Id() const { return _id; }
	void Id(int id) { _id = id; }

private:
	std::list<MapDataTable*> _datas;
	int _id;
	int _tileCountX;
	int _tileCountY;
	bool isLinkedX;
	
	int _bgTileCount;
	int _bTileCount;
	int _pTileCount;
	int _sTileCount;
	int _hTileCount;


public:
	Vector2 staticTileColliderPoint[2000];	// ����� Ÿ���� ���������� ���� �迭
	Vector2 staticLinkedCount[2000];	// ����� Ÿ�ϵ��� ��	
	Vector2 movableTileColliderPoint[50];
	Vector2 movableLinkedCount[50];
	Vector2 passTileColliderPoint[200];
	Vector2 passLinkedCount[200];

	Vector2 staticTilePoint[2000];	// JSON���Ͽ��� �ҷ��� ������ Ÿ�ϵ��� X, Y ��
	char staticTileType[2000];
	int staticTileCount;

	Vector2 backGroundTilePoint[100];
	string backGroundTileType[100];
	int backGroundTileCount;

	Vector2 passTilePoint[200];
	char passTileType[200];
	int passTileCount;

	Vector2 brokenTilePoint[30];
	string brokenTileType[30];
	int brokenTileCount;

	Vector2 hurdleTilePoint[200];
	string hurdleTileType[200];
	int hurdleTileCount;

	Vector2 movableTilePoint[100];
	int movableTileCount;

	int tileColliderCount;
	int movableTileColliderCount;
	int passtileColliderCount;

	Vector2 mapSize;
};

