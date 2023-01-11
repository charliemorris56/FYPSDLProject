#include "pch.h"
#include "TileMap.h"
#include "TileMap.cpp"

TEST(TestCaseName, TestName) 
{
	EXPECT_EQ(1, 1);
	TileMap tileMap;
	bool agentOnGrid = false;
	agentOnGrid = tileMap.GetTileType(150) == Tiles::Agent;

	EXPECT_TRUE(agentOnGrid);
}

TEST(TestCaseName, TestName2) 
{
	EXPECT_TRUE(true);
}
