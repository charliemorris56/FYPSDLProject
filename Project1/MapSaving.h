#pragma once
#include "JsonLoading.h"
#include "TileMap.h"
#include "AStar.h"

class MapSaving
{
public:
	void SaveMapToJson(std::vector<std::vector<int>>& map, std::string name);
	void SaveMapToJson(std::vector<std::vector<int>>& map, std::pair<int, int> src, std::pair<int, int> dest);
	void SaveMapToJson(std::vector<std::vector<int>>& map, std::vector<std::pair<int, int>> src, std::vector<std::pair<int, int>> srcLeader, std::pair<int, int> dest);

	void LoadMapFromJson(std::vector<std::vector<int>>& map, std::string name);
	void LoadMapFromJson(std::vector<std::vector<int>>& map, std::pair<int, int> src, std::pair<int, int> dest);
private:
	Map mapVector;
};

