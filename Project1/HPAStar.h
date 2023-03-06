#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include "MapSaving.h"

class HPAStar
{
public:
	~HPAStar();
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void HPAStarSearch(std::vector<std::vector<int>>& originalMap, std::vector<std::vector<int>>& hiMap, int hierarchicalSize, Pair src, Pair dest, bool diagonal);

	void ProcessMap(std::vector<std::vector<int>>& map, int hierarchicalSize, std::string name);

	void SaveMap();

private:
	bool IsValid(int row, int col);
	bool IsUnBlocked(int row, int col);
	bool IsUnBlockedOriginalMap(int row, int col);
	bool IsDestination(int row, int col);
	bool InitChecks();

	double CalculateHuristicValue(int row, int col);

	void TracePath();
	void ProcessPath();

	bool Successor(int row, int col);

	void PopulateCellDetails();

	int curRow, curCol;
	double gNew, hNew, fNew;
	bool foundDest;

	Cell* m_cellDetails;
	int* closedList;
	std::set<pPair> openList;

	Pair startingPos;
	Pair endingPos;

	Pair endingPosCopy;

	int hiSize;

	std::vector<std::vector<int>> m_map;
	std::vector<std::vector<int>> m_hiMap;

	int m_iRows;
	int m_iCols;

	int m_iHiRows;
	int m_iHiCols;

	std::stack<Pair> m_Path;
};

