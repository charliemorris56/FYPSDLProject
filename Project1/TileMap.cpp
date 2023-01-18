#include "TileMap.h"

TileMap::TileMap(int width, int height)
{
	m_squareSize = (width - m_iBoarder) / COLUMNS;
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
	m_pathColor = { 20,30,200,255, true };
	m_startColor = { 255,255,255,255, true };
	m_endColor = { 150,150,150,255, true };

	std::vector<Map> mapVector;
	JsonLoading::LoadJson(mapVector, "C:\\Users\\charl\\source\\repos\\Project1\\x64\\Debug\\map.json");

	for (int i = 0; i < ROWS * COLUMNS; i++)
	{
		if (mapVector[i].tile == 0)
		{
			m_grid[i] = Tiles::Obstacle;
		}
		else if (mapVector[i].tile == 1)
		{
			m_grid[i] = Tiles::Empty;
		}
		else if (mapVector[i].tile == 2)
		{
			m_grid[i] = Tiles::Path;
		}
		else if (mapVector[i].tile == 3)
		{
			m_grid[i] = Tiles::Agent;
		}
		else if (mapVector[i].tile == 4)
		{
			m_grid[i] = Tiles::Start;
		}
		else if (mapVector[i].tile == 5)
		{
			m_grid[i] = Tiles::End;
		}
	}
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
	if (tile == Tiles::Path)
	{
		return m_pathColor;
	}
	if (tile == Tiles::Start)
	{
		return m_startColor;
	}
	if (tile == Tiles::End)
	{
		return m_endColor;
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
	if (m_grid[pos] == Tiles::Path)
	{
		return m_pathColor;
	}
	if (m_grid[pos] == Tiles::Start)
	{
		return m_startColor;
	}
	if (m_grid[pos] == Tiles::End)
	{
		return m_endColor;
	}
}