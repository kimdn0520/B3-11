#include "pch.h"
#include "MapDataTable.h"
#include "prefab.h"
#include "B3_11Prefab.h"
#include "ItemPrefab.h"
#include "HurdlePrefab.h"
#include "SpritePrefab.h"
#include "MovableTilePrefab.h"
#include "GetThroughTilePrefab.h"
#include "BrokenWallPrefab.h"
#include "TilePrefab.h"
#include "CameraPrefab.h"
#include "SavePointPrefab.h"

#include "MapLoader.h"
#include "Utility.h"

using namespace Utility;

void MapLoader::LoadMap(string mapFileName, CameraPrefab* cameraObj, string savePointName)
{
	//MAP
	MapDataTable* mapData = new MapDataTable();
	mapData->DeserializeFromFile(mapFileName);
	mapData->CheckStaticTile();
	mapData->CheckMovableTile();
	mapData->CheckPassTile();
	cameraObj->GetScriptComponent<CameraController>()->SetMapSize(mapData->mapSize);

	// StaticTile Render
	for (int i = 0; i < mapData->staticTileCount; i++)
	{
		if (mapData->staticTileType[i] == 'A')
		{
			SpritePrefab* staticTileSprite = new SpritePrefab("staticTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Type A (128_128).png", mapData->staticTilePoint[i].x * 128.f + 64.f, mapData->staticTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
		else if (mapData->staticTileType[i] == 'B')
		{
			SpritePrefab* staticTileSprite = new SpritePrefab("staticTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Type B (128_128).png", mapData->staticTilePoint[i].x * 128.f + 64.f, mapData->staticTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
		else if (mapData->staticTileType[i] == 'C')
		{
			SpritePrefab* staticTileSprite = new SpritePrefab("staticTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Type C (128_128).png", mapData->staticTilePoint[i].x * 128.f + 64.f, mapData->staticTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
		else if (mapData->staticTileType[i] == 'D')
		{
			SpritePrefab* staticTileSprite = new SpritePrefab("staticTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Type D (128_128).png", mapData->staticTilePoint[i].x * 128.f + 64.f, mapData->staticTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
		else if (mapData->staticTileType[i] == 'W')
		{
			SpritePrefab* staticTileSprite = new SpritePrefab("staticTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Type W (128_128).png", mapData->staticTilePoint[i].x * 128.f + 64.f, mapData->staticTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
	}
	// StaticTile Collider
	for (int i = 0; i < mapData->tileColliderCount; i++)
	{
		TilePrefab* staticTileObj = new TilePrefab("groundCollider", ((mapData->staticTileColliderPoint[i].x * 128.f) + (mapData->staticLinkedCount[i].x * 128.f) / 2), ((mapData->staticTileColliderPoint[i].y * 128.f) + (mapData->staticLinkedCount[i].y * 128.f) / 2), (mapData->staticLinkedCount[i].x * 128.f), (mapData->staticLinkedCount[i].y * 128.f));
	}

	// MovableTile
	for (int i = 0; i < mapData->movableTileCount; i++)
	{
		MovableTilePrefab* movableTileObj = new MovableTilePrefab("movableGround", mapData->movableTilePoint[i].x * 128.f + 64.f, mapData->movableTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
	}

	// PassTile Collider
	for (int i = 0; i < mapData->passtileColliderCount; i++)
	{
		GetThroughTilePrefab* passTileObj = new GetThroughTilePrefab("passTile", ((mapData->passTileColliderPoint[i].x * 128.f) + (mapData->passLinkedCount[i].x * 128.f) / 2), ((mapData->passTileColliderPoint[i].y * 128.f) + (mapData->passLinkedCount[i].y * 128.f) / 2 - 44.f), mapData->passLinkedCount[i].x * 128.f, mapData->passLinkedCount[i].y * 40.f);
	}
	// PassTile Render
	for (int i = 0; i < mapData->passTileCount; i++)
	{
		if (mapData->passTileType[i] == 'A')
		{
			SpritePrefab* possTileSprite = new SpritePrefab("passTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Pass_Type A (128_128).png", mapData->passTilePoint[i].x * 128.f + 64.f, mapData->passTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
		else if (mapData->passTileType[i] == 'W')
		{
			SpritePrefab* possTileSprite = new SpritePrefab("passTile", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Platform_Pass_Type W (128_128).png", mapData->passTilePoint[i].x * 128.f + 64.f, mapData->passTilePoint[i].y * 128.f + 64.f, 128, 128);
		}
	}

	// BrokenWall
	for (int i = 0; i < mapData->brokenTileCount; i++)
	{
		if (mapData->brokenTileType[i] == "Nor")
		{
			BrokenWallPrefab* brokenWallObj = new BrokenWallPrefab("normalGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
			//SpritePrefab* brokenWallSprite = new SpritePrefab("normalGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
		}
		else if (mapData->brokenTileType[i] == "Peng")
		{
			BrokenWallPrefab* penguinTubeObj = new BrokenWallPrefab("penguinGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Penguin (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
			//SpritePrefab* penguinTubeSprite = new SpritePrefab("normalGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Penguin (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
		}
		else if (mapData->brokenTileType[i] == "Sha")
		{
			BrokenWallPrefab* sharkTubeObj = new BrokenWallPrefab("sharkGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Shark (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
			//SpritePrefab* sharkTubeSprite = new SpritePrefab("normalGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Shark (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
		}
		else if (mapData->brokenTileType[i] == "Tur")
		{
			BrokenWallPrefab* turtleTubeObj = new BrokenWallPrefab("turtleGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Turtle (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
			//SpritePrefab* turtleTubeSprite = new SpritePrefab("normalGlass", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Glass_Tube_Turtle (128_256).png", mapData->brokenTilePoint[i].x * 128.f + 64.f, mapData->brokenTilePoint[i].y * 128.f, 128.f, 256.f);
		}
	}

	// Hurdle
	for (int i = 0; i < mapData->hurdleTileCount; i++)
	{
		if (mapData->hurdleTileType[i] == "Saw")
		{
			HurdlePrefab* sawobj = new HurdlePrefab("Saw", "Saw", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			/*SpritePrefab* sawSprite = new SpritePrefab("Saw", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Circular_Saw (128_128).png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f, true);*/
		}
		else if (mapData->hurdleTileType[i] == "LazerL")
		{
			//SpritePrefab* lazerLSprite = new SpritePrefab("LazerL", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_L (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerLobj = new HurdlePrefab("Laser_H_L", "Laser_H_L", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerM")
		{
			HurdlePrefab* lazerMobj = new HurdlePrefab("Laser_H_M", "Laser_H_M", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			//SpritePrefab* lazerMSprite = new SpritePrefab("LazerM", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_M (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerR")
		{
			//SpritePrefab* lazerRSprite = new SpritePrefab("LazerR", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_R (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerRobj = new HurdlePrefab("Laser_H_R", "Laser_H_R", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerHRL")
		{
			//SpritePrefab* lazerLSprite = new SpritePrefab("LazerL", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_L (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerLobj = new HurdlePrefab("Laser_HR_L", "Laser_HR_L", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerHRM")
		{
			HurdlePrefab* lazerMobj = new HurdlePrefab("Laser_HR_M", "Laser_HR_M", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			//SpritePrefab* lazerMSprite = new SpritePrefab("LazerM", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_M (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerHRR")
		{
			//SpritePrefab* lazerRSprite = new SpritePrefab("LazerR", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type H_Off_R (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerRobj = new HurdlePrefab("Laser_HR_R", "Laser_HR_R", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerVB")
		{
			//SpritePrefab* lazerLSprite = new SpritePrefab("LazerVB", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type V_Off_B (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerLobj = new HurdlePrefab("Laser_V_B", "Laser_V_B", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerVM")
		{
			HurdlePrefab* lazerMobj = new HurdlePrefab("Laser_V_M", "Laser_V_M", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			//SpritePrefab* lazerMSprite = new SpritePrefab("LazerVM", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type V_Off_M (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->hurdleTileType[i] == "LazerVT")
		{
			//SpritePrefab* lazerRSprite = new SpritePrefab("LazerVT", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Laser_Trap_Type V_Off_T (128_128) 12fps.png", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
			HurdlePrefab* lazerRobj = new HurdlePrefab("Laser_V_T", "Laser_V_T", mapData->hurdleTilePoint[i].x * 128.f + 64.f, mapData->hurdleTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
	}

	// BackGround
	for (int i = 0; i < mapData->backGroundTileCount; i++)
	{
		if (mapData->backGroundTileType[i] == "Box")
		{
			SpritePrefab* boxSprite = new SpritePrefab("Box", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Box (128_128).png", mapData->backGroundTilePoint[i].x * 128.f + 64.f, mapData->backGroundTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->backGroundTileType[i] == "Desk")
		{
			SpritePrefab* boxSprite = new SpritePrefab("Desk", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Desk (256_128).png", mapData->backGroundTilePoint[i].x * 128.f + 128.f, mapData->backGroundTilePoint[i].y * 128.f + 64.f, 256.f, 128.f);
		}
		else if (mapData->backGroundTileType[i] == "Moniter")
		{
			SpritePrefab* boxSprite = new SpritePrefab("Moniter", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\holographic_monitor (128_128).png", mapData->backGroundTilePoint[i].x * 128.f + 64.f, mapData->backGroundTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->backGroundTileType[i] == "Light")
		{
			SpritePrefab* boxSprite = new SpritePrefab("Moniter", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Light_Type A (128_128).png", mapData->backGroundTilePoint[i].x * 128.f + 64.f, mapData->backGroundTilePoint[i].y * 128.f + 64.f, 128.f, 128.f);
		}
		else if (mapData->backGroundTileType[i] == "SavePoint")
		{
			SavePointPrefab* savePoint = new SavePointPrefab("SavePoint", mapData->backGroundTilePoint[i].x * 128.f + 128.f, mapData->backGroundTilePoint[i].y * 128.f, 256.f, 256.f, savePointName);
			//SpritePrefab* boxSprite = new SpritePrefab("SavePoint", L"..\\..\\4_Resources\\ProjectSheet\\BackgroundSheet\\Save_Point_Open (256_256).png", mapData->backGroundTilePoint[i].x * 128.f + 128.f, mapData->backGroundTilePoint[i].y * 128.f, 256.f, 256.f);
		}

	}
}
