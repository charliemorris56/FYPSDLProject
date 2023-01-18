#pragma once

#include "gtest/gtest.h"
#include "JsonLoading.h"
#include "TileMap.h"
#include "AStar.h"

class pch
{
public:
	pch();
	~pch();

	void SaveMapToJson(int map[][COLUMNS], AStar::Pair src, AStar::Pair dest);
private:
	std::vector<Map> mapVector;
};
