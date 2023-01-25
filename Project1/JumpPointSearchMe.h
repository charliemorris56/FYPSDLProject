#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include "AStar.h"

class JumpPointSearchMe
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void JumpPointSearch(std::vector<std::vector<int>>& map, Pair src, Pair dest, bool diagonal);

	void SaveMap();

private:
	bool IsValid(int row, int col);
	bool IsUnBlocked(int row, int col);
	bool IsDestination(int row, int col);
	bool InitChecks();

	double CalculateHuristicValue(int row, int col);

	void TracePath();

	bool Successor(int row, int col);

	void PopulateCellDetails();

	int curRow, curCol;
	double gNew, hNew, fNew;
	bool foundDest;

	std::vector<std::vector<Cell>> m_cellDetails;
	std::vector<std::vector<bool>> closedList;
	std::set<pPair> openList;

	Pair startingPos;
	Pair endingPos;

	std::vector<std::vector<int>> m_map;

	int m_iRows;
	int m_iCols;
};

