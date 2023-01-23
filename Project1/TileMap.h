#pragma once
#include <iostream>
#include "JsonLoading.h"

#define ROWS 10
#define COLUMNS 10

enum class Tiles
{
	Obstacle,
	Empty,
	Path,
	Agent,
	Start,
	End
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
	int tile;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Map, tile)

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

	bool ReturnsTru() { return true; }
private:
	Tiles* m_grid;
	int m_squareSize;

	Color m_emptyColor;
	Color m_obstacleColor;
	Color m_agentColor;
	Color m_pathColor;
	Color m_startColor;
	Color m_endColor;

	int m_iBoarder = 10;
};

