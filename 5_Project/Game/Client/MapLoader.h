#pragma once

class CameraPrefab;

class MapLoader
{
public:
	static void LoadMap(string mapFileName, CameraPrefab* cameraObj, string savePointName = "");
};