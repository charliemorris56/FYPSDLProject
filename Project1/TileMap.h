#pragma once

#define ROWS 100
#define COLUMNS 100

enum class Tiles
{
	Empty,
	Obstacle,
	Agent
};

struct Color
{
	int r;
	int g;
	int b;
	int a;
	bool fill;
};

class TileMap
{
public:
	TileMap();

	int GetSquareSize();
	Tiles GetTileType(int pos);
	Color GetColor(Tiles tile);
	Color GetColor(int pos);

	bool ReturnsTru() { return true; }
private:
	Tiles m_grid[ROWS * COLUMNS];
	int m_squareSize;

	Color m_emptyColor;
	Color m_obstacleColor;
	Color m_agentColor;
};

