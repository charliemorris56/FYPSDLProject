#pragma once
#include "TileMap.h"
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include "AStar.h"

class HPAStar
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void Search(int map[][COLUMNS], Pair src, Pair dest, bool diagonal, int hierarchicalSize);

private:
	bool IsValid(int row, int col);
	bool IsUnBlocked(int map[][COLUMNS], int row, int col);
	bool IsDestination(int row, int col, Pair dest);
	bool InitChecks(int map[][COLUMNS], Pair src, Pair dest);

	double CalculateHuristicValue(int row, int col, Pair dest);

	void TracePath(int map[][COLUMNS], Cell cellDetails[][COLUMNS], Pair dest);

	bool Successor(int map[][COLUMNS], int row, int col, Pair dest);

	void ProcessMap(int map[][COLUMNS]);

	int curRow, curCol;
	double gNew, hNew, fNew;
	bool foundDest;

	Cell cellDetails[ROWS][COLUMNS];
	bool closedList[ROWS][COLUMNS];
	std::set<pPair> openList;

	Pair startingPos;
	Pair endingPos;

	int hiSize;
};

