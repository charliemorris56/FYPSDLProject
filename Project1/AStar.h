#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include "MapSaving.h"

struct Cell {
	int cRow, cCol;
	double f, g, h;
};

class AStar
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void AStarSearch(std::vector<std::vector<int>> &map, Pair src, Pair dest, bool diagonal, bool groupSearch = false);
	void AStarSearchNoMap(Pair src, Pair dest, bool diagonal);

	void SaveMap();

	void GetMap(std::vector<std::vector<int>>& map);

	void SetRadius(float radius);

	void GetFlockingPath(std::vector<Pair>& flockingPath);
	void SetFlockingPath(std::vector<Pair>& flockingPath);

private:
	bool IsValid(int row, int col);
	bool IsUnBlocked(int row, int col);
	bool IsDestination(int row, int col);
	bool InitChecks();

	double CalculateHuristicValue(int row, int col);

	void TracePath();

	bool Successor(int row, int col);

	void PopulateCellDetails();

	bool FlockingRadiusCheck(int row, int col);

	int curRow, curCol;
	double gNew, hNew, fNew;
	bool foundDest = false;

	bool m_bGroupSearch;

	std::vector<std::vector<Cell>> m_cellDetails;
	std::vector<std::vector<bool>> closedList;
	std::set<pPair> openList;

	Pair startingPos;
	Pair endingPos;

	std::vector<std::vector<int>> m_map;

	std::vector<Pair> m_flockingPath;

	int m_iRows;
	int m_iCols;

	float m_fRadius = 0;
	bool m_bRadius = false;
	bool m_bSecondyLine = false;
};
