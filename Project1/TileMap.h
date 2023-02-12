#pragma once
#include <iostream>
#include "JsonLoading.h"

enum class Tiles
{
	Obstacle,
	Empty,
	Path,
	Agent,
	Start,
	End,
	AgentLeader,
	PathAgentGroup,
	PathFlocking
};

struct Color
{
	int r;
	int g;
	int b;
	int a;
	bool fill;
};

struct Map
{
	std::vector<int> tile;
	int rows;
	int cols;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Map, tile, rows, cols)

class TileMap
{
public:
	TileMap(int width, int height);
	TileMap();
	~TileMap();

	void Init();

	int GetSquareSize();
	Tiles GetTileType(int pos);
	Color GetColor(Tiles tile);
	Color GetColor(int pos);

	int GetRows();
	int GetCols();
private:
	std::vector<Tiles> m_grid;
	int m_squareSize;

	Color m_emptyColor;
	Color m_obstacleColor;
	Color m_agentColor;
	Color m_pathColor;
	Color m_startColor;
	Color m_endColor;
	Color m_agentLeaderColor;
	Color m_pathAgentLeaderColor;
	Color m_pathFlockingColor;

	int m_iBoarder = 10;

	int m_iRows;
	int m_iCols;

	int m_iWidth;
	int m_iHeight;
};

