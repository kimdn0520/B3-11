#include "pch.h"
#include "MapDataTable.h"

MapDataTable::MapDataTable() : _id(0), _tileCountX(1), _tileCountY(1), movableTileColliderCount(0), tileColliderCount(0), isLinkedX(false), staticTileCount(0), backGroundTileCount(0), passTileCount(0), brokenTileCount(0), hurdleTileCount(0), movableTileCount(0), passtileColliderCount(0), _bgTileCount(0), _bTileCount(0), _pTileCount(0), _sTileCount(0), _hTileCount(0)
{
}

void MapDataTable::CheckStaticTile()
{
	bool isCheck[2000] = { false };
	for (int nowCheckPoint = 0;nowCheckPoint < 2000;nowCheckPoint++)
	{
		_tileCountX = 1;
		_tileCountY = 1;
		if (!isCheck[nowCheckPoint] && (staticTilePoint[nowCheckPoint].x != 0 || staticTilePoint[nowCheckPoint].y != 0))
		{
			for (int nextCheckPoint = nowCheckPoint + 1;nextCheckPoint < 1999;nextCheckPoint++)
			{
				if (staticTilePoint[nextCheckPoint].x == staticTilePoint[nowCheckPoint].x && staticTilePoint[nextCheckPoint].y == (staticTilePoint[nowCheckPoint].y + _tileCountY) && _tileCountX == 1)
				{
					_tileCountY++;
					isLinkedX = false;
					isCheck[nextCheckPoint] = true;
				}
				else if (staticTilePoint[nextCheckPoint].x == (staticTilePoint[nowCheckPoint].x + _tileCountX) && staticTilePoint[nextCheckPoint].y == staticTilePoint[nowCheckPoint].y && _tileCountY == 1)
				{
					_tileCountX++;
					isLinkedX = true;
					isCheck[nextCheckPoint] = true;
				}
			}
			staticTileColliderPoint[tileColliderCount].x = staticTilePoint[nowCheckPoint].x;
			staticTileColliderPoint[tileColliderCount].y = staticTilePoint[nowCheckPoint].y;
			if (isLinkedX)
			{
				staticLinkedCount[tileColliderCount].x = _tileCountX;
				staticLinkedCount[tileColliderCount].y = 1;
			}
			else if (!isLinkedX)
			{
				staticLinkedCount[tileColliderCount].x = 1;
				staticLinkedCount[tileColliderCount].y = _tileCountY;
			}
			tileColliderCount++;
		}
	}
}

void MapDataTable::CheckMovableTile()
{
	bool isCheck[100] = { false };
	for (int nowCheckPoint = 0;nowCheckPoint < 50;nowCheckPoint++)
	{
		_tileCountX = 1;
		_tileCountY = 1;
		if (!isCheck[nowCheckPoint] && (movableTilePoint[nowCheckPoint].x != 0 && movableTilePoint[nowCheckPoint].y != 0))
		{
			for (int nextCheckPoint = nowCheckPoint + 1;nextCheckPoint < 49;nextCheckPoint++)
			{
				if (movableTilePoint[nextCheckPoint].x == movableTilePoint[nowCheckPoint].x && movableTilePoint[nextCheckPoint].y == (movableTilePoint[nowCheckPoint].y + _tileCountY) && _tileCountX == 1)
				{
					_tileCountY++;
					isLinkedX = false;
					isCheck[nextCheckPoint] = true;
				}
				else if (movableTilePoint[nextCheckPoint].x == (movableTilePoint[nowCheckPoint].x + _tileCountX) && movableTilePoint[nextCheckPoint].y == movableTilePoint[nowCheckPoint].y && _tileCountY == 1)
				{
					_tileCountX++;
					isLinkedX = true;
					isCheck[nextCheckPoint] = true;
				}
			}
			movableTileColliderPoint[movableTileColliderCount].x = movableTilePoint[nowCheckPoint].x;
			movableTileColliderPoint[movableTileColliderCount].y = movableTilePoint[nowCheckPoint].y;
			if (isLinkedX)
			{
				movableLinkedCount[movableTileColliderCount].x = _tileCountX;
				movableLinkedCount[movableTileColliderCount].y = 1;
			}
			else if (!isLinkedX)
			{
				movableLinkedCount[movableTileColliderCount].x = 1;
				movableLinkedCount[movableTileColliderCount].y = _tileCountY;
			}
			movableTileColliderCount++;
		}
	}
}

void MapDataTable::CheckPassTile()
{
	bool isCheck[200] = { false };
	for (int nowCheckPoint = 0;nowCheckPoint < 200;nowCheckPoint++)
	{
		_tileCountX = 1;
		_tileCountY = 1;
		if (!isCheck[nowCheckPoint] && (passTilePoint[nowCheckPoint].x != 0 && passTilePoint[nowCheckPoint].y != 0))
		{
			for (int nextCheckPoint = nowCheckPoint + 1;nextCheckPoint < 199;nextCheckPoint++)
			{
				if (passTilePoint[nextCheckPoint].x == passTilePoint[nowCheckPoint].x && passTilePoint[nextCheckPoint].y == (passTilePoint[nowCheckPoint].y + _tileCountY) && _tileCountX == 1)
				{
					_tileCountY++;
					isLinkedX = false;
					isCheck[nextCheckPoint] = true;
				}
				else if (passTilePoint[nextCheckPoint].x == (passTilePoint[nowCheckPoint].x + _tileCountX) && passTilePoint[nextCheckPoint].y == passTilePoint[nowCheckPoint].y && _tileCountY == 1)
				{
					_tileCountX++;
					isLinkedX = true;
					isCheck[nextCheckPoint] = true;
				}
			}
			passTileColliderPoint[passtileColliderCount].x = passTilePoint[nowCheckPoint].x;
			passTileColliderPoint[passtileColliderCount].y = passTilePoint[nowCheckPoint].y;
			if (isLinkedX)
			{
				passLinkedCount[passtileColliderCount].x = _tileCountX;
				passLinkedCount[passtileColliderCount].y = 1;
			}
			else if (!isLinkedX)
			{
				passLinkedCount[passtileColliderCount].x = 1;
				passLinkedCount[passtileColliderCount].y = _tileCountY;
			}
			passtileColliderCount++;
		}
	}
}

bool MapDataTable::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	const rapidjson::Value& _mapSize = doc["mapSize"].GetArray();
	mapSize.x = _mapSize[rapidjson::SizeType(0)].GetInt();
	mapSize.y = _mapSize[rapidjson::SizeType(1)].GetInt();

	const rapidjson::Value& gameObjects = doc["gameObjects"];

	for (rapidjson::Value::ConstMemberIterator itr = gameObjects.MemberBegin(); itr != gameObjects.MemberEnd(); ++itr)
	{
		if (itr->name == "Resource\\BackGroundSheet\\Box (128_128).png")
		{
			const rapidjson::Value& backGroundPos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < backGroundPos1.Size(); i++)
			{
				const rapidjson::Value& posXY = backGroundPos1[i].GetArray();
				backGroundTilePoint[i + _bgTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				backGroundTilePoint[i + _bgTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				backGroundTileType[i + _bgTileCount] = "Box";
				backGroundTileCount++;
			}
			_bgTileCount = backGroundTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Desk (256_128).png")
		{
			const rapidjson::Value& backGroundPos2 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < backGroundPos2.Size(); i++)
			{
				const rapidjson::Value& posXY = backGroundPos2[i].GetArray();
				backGroundTilePoint[i + _bgTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				backGroundTilePoint[i + _bgTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				backGroundTileType[i + _bgTileCount] = "Desk";
				backGroundTileCount++;
			}
			_bgTileCount = backGroundTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\holographic_monitor (128_128).png")
		{
			const rapidjson::Value& backGroundPos3 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < backGroundPos3.Size(); i++)
			{
				const rapidjson::Value& posXY = backGroundPos3[i].GetArray();
				backGroundTilePoint[i + _bgTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				backGroundTilePoint[i + _bgTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				backGroundTileType[i + _bgTileCount] = "Moniter";
				backGroundTileCount++;
			}
			_bgTileCount = backGroundTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Save_Point_Open (256_256).png")
		{
			const rapidjson::Value& backGroundPos3 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < backGroundPos3.Size(); i++)
			{
				const rapidjson::Value& posXY = backGroundPos3[i].GetArray();
				backGroundTilePoint[i + _bgTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				backGroundTilePoint[i + _bgTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				backGroundTileType[i + _bgTileCount] = "SavePoint";
				backGroundTileCount++;
			}
			_bgTileCount = backGroundTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Light_Type A (128_128).png")
		{
			const rapidjson::Value& backGroundPos3 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < backGroundPos3.Size(); i++)
			{
				const rapidjson::Value& posXY = backGroundPos3[i].GetArray();
				backGroundTilePoint[i + _bgTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				backGroundTilePoint[i + _bgTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				backGroundTileType[i + _bgTileCount] = "Light";
				backGroundTileCount++;
			}
			_bgTileCount = backGroundTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Floating_Type A (128_128).png")
		{
			const rapidjson::Value& movablePos = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < movablePos.Size(); i++)
			{
				const rapidjson::Value& posXY = movablePos[i].GetArray();
				movableTilePoint[i].x = posXY[rapidjson::SizeType(0)].GetInt();
				movableTilePoint[i].y = posXY[rapidjson::SizeType(1)].GetInt();
				movableTileCount++;
			}
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Glass_Tube (128_256).png")
		{
			const rapidjson::Value& brokenPos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < brokenPos1.Size(); i++)
			{
				const rapidjson::Value& posXY = brokenPos1[i].GetArray();
				brokenTilePoint[i + _bTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				brokenTilePoint[i + _bTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				brokenTileType[i + _bTileCount] = "Nor";
				brokenTileCount++;
			}
			_bTileCount = brokenTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Glass_Tube_Penguin (128_256).png")
		{
			const rapidjson::Value& brokenPos2 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < brokenPos2.Size(); i++)
			{
				const rapidjson::Value& posXY = brokenPos2[i].GetArray();
				brokenTilePoint[i + _bTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				brokenTilePoint[i + _bTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				brokenTileType[i + _bTileCount] = "Peng";
				brokenTileCount++;
			}
			_bTileCount = brokenTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Glass_Tube_Shark (128_256).png")
		{
			const rapidjson::Value& brokenPos3 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < brokenPos3.Size(); i++)
			{
				const rapidjson::Value& posXY = brokenPos3[i].GetArray();
				brokenTilePoint[i + _bTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				brokenTilePoint[i + _bTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				brokenTileType[i + _bTileCount] = "Sha";
				brokenTileCount++;
			}
			_bTileCount = brokenTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Glass_Tube_Turtle (128_256).png")
		{
			const rapidjson::Value& brokenPos4 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < brokenPos4.Size(); i++)
			{
				const rapidjson::Value& posXY = brokenPos4[i].GetArray();
				brokenTilePoint[i + _bTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				brokenTilePoint[i + _bTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				brokenTileType[i + _bTileCount] = "Tur";
				brokenTileCount++;
			}
			_bTileCount = brokenTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Pass_Type A (128_128).png")
		{
			const rapidjson::Value& passPos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < passPos1.Size(); i++)
			{
				const rapidjson::Value& posXY = passPos1[i].GetArray();
				passTilePoint[i + _pTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				passTilePoint[i + _pTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				passTileType[i + _pTileCount] = 'A';
				passTileCount++;
			}
			_pTileCount = passTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Pass_Type W (128_128).png")
		{
			const rapidjson::Value& passPos2 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < passPos2.Size(); i++)
			{
				const rapidjson::Value& posXY = passPos2[i].GetArray();
				passTilePoint[i + _pTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				passTilePoint[i + _pTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				passTileType[i + _pTileCount] = 'W';
				passTileCount++;
			}
			_pTileCount = passTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Type W (128_128).png")
		{
			const rapidjson::Value& staticPos5 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < staticPos5.Size(); i++)
			{
				const rapidjson::Value& posXY = staticPos5[i].GetArray();
				staticTilePoint[i + _sTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				staticTilePoint[i + _sTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				staticTileType[i + _sTileCount] = 'W';
				staticTileCount++;
			}
			_sTileCount = staticTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Type A (128_128).png")
		{
			const rapidjson::Value& staticPos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < staticPos1.Size(); i++)
			{
				const rapidjson::Value& posXY = staticPos1[i].GetArray();
				staticTilePoint[i + _sTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				staticTilePoint[i + _sTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				staticTileType[i + _sTileCount] = 'A';
				staticTileCount++;
			}
			_sTileCount = staticTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Type D (128_128).png")
		{
			const rapidjson::Value& staticPos4 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < staticPos4.Size(); i++)
			{
				const rapidjson::Value& posXY = staticPos4[i].GetArray();
				staticTilePoint[i + _sTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				staticTilePoint[i + _sTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				staticTileType[i + _sTileCount] = 'D';
				staticTileCount++;
			}
			_sTileCount = staticTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Type C (128_128).png")
		{
			const rapidjson::Value& staticPos3 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < staticPos3.Size(); i++)
			{
				const rapidjson::Value& posXY = staticPos3[i].GetArray();
				staticTilePoint[i + _sTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				staticTilePoint[i + _sTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				staticTileType[i + _sTileCount] = 'C';
				staticTileCount++;
			}
			_sTileCount = staticTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Platform_Type B (128_128).png")
		{
			const rapidjson::Value& staticPos2 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < staticPos2.Size(); i++)
			{
				const rapidjson::Value& posXY = staticPos2[i].GetArray();
				staticTilePoint[i + _sTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				staticTilePoint[i + _sTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				staticTileType[i + _sTileCount] = 'B';
				staticTileCount++;
			}
			_sTileCount = staticTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Circular_Saw (128_128).png")
		{
			const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
			{
				const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
				hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				hurdleTileType[i + _hTileCount] = "Saw";
				hurdleTileCount++;
			}
			_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type H_Off_L (128_128) 12fps.png")
		{
			const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
			{
				const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
				hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				hurdleTileType[i + _hTileCount] = "LazerL";
				hurdleTileCount++;
			}
			_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type H_Off_M (128_128) 12fps.png")
		{
			const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
			for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
			{
				const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
				hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
				hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
				hurdleTileType[i + _hTileCount] = "LazerM";
				hurdleTileCount++;
			}
			_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type H_Off_R (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerR";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type HR_Off_L (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerHRL";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type HR_Off_M (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerHRM";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type HR_Off_R (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerHRR";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type V_Off_B (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerVB";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type V_Off_M (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerVM";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
		else if (itr->name == "Resource\\BackGroundSheet\\Laser_Trap_Type V_Off_T (128_128) 12fps.png")
		{
		const rapidjson::Value& hurdlePos1 = itr->value["pos"].GetArray();
		for (rapidjson::SizeType i = 0; i < hurdlePos1.Size(); i++)
		{
			const rapidjson::Value& posXY = hurdlePos1[i].GetArray();
			hurdleTilePoint[i + _hTileCount].x = posXY[rapidjson::SizeType(0)].GetInt();
			hurdleTilePoint[i + _hTileCount].y = posXY[rapidjson::SizeType(1)].GetInt();
			hurdleTileType[i + _hTileCount] = "LazerVT";
			hurdleTileCount++;
		}
		_hTileCount = hurdleTileCount;
		}
	}

	return true;
}
