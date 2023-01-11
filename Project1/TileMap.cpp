#include "TileMap.h"

TileMap::TileMap(int width, int height)
{
	m_squareSize = (width - 10) / COLUMNS;
	Init();
}

TileMap::TileMap()
{
	m_squareSize = 8;
	Init();
}

void TileMap::Init()
{
	m_grid = new Tiles[ROWS * COLUMNS];

	for (int i = 0; i < ROWS * COLUMNS; i++)
	{
		m_grid[i] = Tiles::Empty;
	}

	m_emptyColor = { 200,50,50,255, false };
	m_obstacleColor = { 50,200,50,255, true };
	m_agentColor = { 50,50,200,255, true };

	m_grid[50] = Tiles::Obstacle;
	m_grid[51] = Tiles::Obstacle;
	m_grid[52] = Tiles::Obstacle;

	m_grid[150] = Tiles::Agent;
	m_grid[152] = Tiles::Agent;
	m_grid[153] = Tiles::Agent;
	m_grid[154] = Tiles::Agent;
	m_grid[155] = Tiles::Agent;
}

TileMap::~TileMap()
{
	delete [] m_grid;
}

int TileMap::GetSquareSize()
{
	return m_squareSize;
}

Tiles TileMap::GetTileType(int pos)
{
	return m_grid[pos];
}

Color TileMap::GetColor(Tiles tile)
{
	if (tile == Tiles::Empty)
	{
		return m_emptyColor;
	}
	if (tile == Tiles::Obstacle)
	{
		return m_obstacleColor;
	}
	if (tile == Tiles::Agent)
	{
		return m_agentColor;
	}
}

Color TileMap::GetColor(int pos)
{
	if (m_grid[pos] == Tiles::Empty)
	{
		return m_emptyColor;
	}
	if (m_grid[pos] == Tiles::Obstacle)
	{
		return m_obstacleColor;
	}
	if (m_grid[pos] == Tiles::Agent)
	{
		return m_agentColor;
	}
}