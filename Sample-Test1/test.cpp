#include "pch.h"
#include "TileMap.h"
#include "TileMap.cpp"

TEST(TestCaseName, TestName2) {
	EXPECT_EQ(1, 1);
	TileMap tileMap;
	bool agentOnGrid = false;
	agentOnGrid = tileMap.GetTileType(150) == Tiles::Agent;

	auto tesmp = tileMap.GetTileType(150);

	EXPECT_TRUE(agentOnGrid);
}
