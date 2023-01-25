#include "AStar.h"

bool AStar::IsValid(int row, int col)
{
	bool isInRange = (row >= 0) && (row < m_iRows) && (col >= 0) && (col < m_iCols);
	return isInRange;
}

bool AStar::IsUnBlocked(int row, int col)
{
	//bool isCellBlocked = m_map[row][col] == 1;
	bool isCellBlocked = m_map[row][col] != 0;
	return isCellBlocked;
}

bool AStar::InitChecks()
{
	if (!IsValid(startingPos.first, startingPos.second))
	{
		std::cout << "Source is invalid";
		return false;
	}

	if (!IsValid(endingPos.first, endingPos.second))
	{
		std::cout << "Destination is invalid";
		return false;
	}

	if (!IsUnBlocked(startingPos.first, startingPos.second)) {
		std::cout << "Source is blocked\n";
		return false;
	}

	if (!IsUnBlocked(endingPos.first, endingPos.second))
	{
		std::cout << "Destination is blocked\n";
		return false;
	}

	if (IsDestination(startingPos.first, startingPos.second)) {
		std::cout << "Source = destination\n";
		return false;
	}

	return true;
}

bool AStar::IsDestination(int row, int col)
{
	bool isDestination = row == endingPos.first && col == endingPos.second;
	return isDestination;
}

double AStar::CalculateHuristicValue(int row, int col)
{
	double huristic = ((double)sqrt((row - endingPos.first) * (row - endingPos.first) + (col - endingPos.second) * (col - endingPos.second)));
	return huristic;
}

void AStar::TracePath()
{
	std::cout << "\nThe Path is ";

	int row = endingPos.first;
	int col = endingPos.second;

	std::stack<Pair> Path;

	while (!(m_cellDetails[row][col].cRow == row && m_cellDetails[row][col].cCol == col))
	{
		Path.push(std::make_pair(row, col));
		int temp_col = m_cellDetails[row][col].cCol;
		int temp_row = m_cellDetails[row][col].cRow;
		row = temp_row;
		col = temp_col;
	}

	Path.push(std::make_pair(row, col));
	while (!Path.empty()) 
	{
		std::pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
		m_map[p.first][p.second] = 2;
	}
}

bool AStar::Successor(int row, int col)
{
	if (IsValid(curRow + row, curCol + col))
	{
		if (IsDestination(curRow + row, curCol + col))
		{
			m_cellDetails[curRow + row][curCol + col].cRow = curRow;
			m_cellDetails[curRow + row][curCol + col].cCol = curCol;
			std::cout << "The destination cell is found\n";
			TracePath();
			foundDest = true;
			return true;
		}
		// Seccessor already on the closed list or is blocked
		else if (!closedList[curRow + row][curCol + col] && IsUnBlocked(curRow + row, curCol + col))
		{
			gNew = m_cellDetails[curRow][curCol].g + 1.0;
			hNew = CalculateHuristicValue(curRow + row, curCol + col);
			fNew = gNew + hNew;

			// Add to the open list
			if (m_cellDetails[curRow + row][curCol + col].f == FLT_MAX || m_cellDetails[curRow + row][curCol + col].f > fNew)
			{
				openList.insert(std::make_pair(fNew, std::make_pair(curRow + row, curCol + col)));

				m_cellDetails[curRow + row][curCol + col].f = fNew;
				m_cellDetails[curRow + row][curCol + col].g = gNew;
				m_cellDetails[curRow + row][curCol + col].h = hNew;
				m_cellDetails[curRow + row][curCol + col].cRow = curRow;
				m_cellDetails[curRow + row][curCol + col].cCol = curCol;
			}
		}
	}
	return false;
}

void AStar::AStarSearch(std::vector<std::vector<int>>& map, Pair src, Pair dest, bool diagonal)
{
	m_map = map;
	m_iRows = map.size();
	m_iCols = map[0].size();

	startingPos = src;
	endingPos = dest;

	if (!InitChecks())
	{
		return;
	}

	for (int i = 0; i < m_iRows; i++)
	{
		std::vector<bool> cl(m_iCols, false);
		closedList.push_back(cl);
	}

	PopulateCellDetails();	

	openList.insert(std::make_pair(0.0, std::make_pair(curRow, curCol)));

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		curRow = p.second.first;
		curCol = p.second.second;
		closedList[curRow][curCol] = true;

		if (Successor(-1, 0)) // North
		{
			return;
		}
		if (Successor(0, 1)) // South
		{
			return;
		}
		if (Successor(0, -1)) // East
		{
			return;
		}
		if (Successor(1, 0)) // West
		{
			return;
		}

		if (diagonal)
		{
			if (Successor(-1, 1)) // North-East
			{
				return;
			}
			if (Successor(-1, -1)) // North-West
			{
				return;
			}
			if (Successor( 1, 1)) // South-East
			{
				return;
			}
			if (Successor(1, -1)) // South-West
			{
				return;
			}
		}

		if (foundDest == false)
		{
			//std::cout << "Failed to find the destination cell\n";
		}
	}
}

void AStar::AStarSearchNoMap(Pair src, Pair dest, bool diagonal)
{
	m_iRows = m_map.size();
	m_iCols = m_map[0].size();

	startingPos = src;
	endingPos = dest;

	if (!InitChecks())
	{
		return;
	}

	for (int i = 0; i < m_iRows; i++)
	{
		std::vector<bool> cl(m_iCols, false);
		closedList.push_back(cl);
	}

	PopulateCellDetails();

	openList.insert(std::make_pair(0.0, std::make_pair(curRow, curCol)));

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		curRow = p.second.first;
		curCol = p.second.second;
		closedList[curRow][curCol] = true;

		if (Successor(-1, 0)) // North
		{
			return;
		}
		if (Successor(0, 1)) // South
		{
			return;
		}
		if (Successor(0, -1)) // East
		{
			return;
		}
		if (Successor(1, 0)) // West
		{
			return;
		}

		if (diagonal)
		{
			if (Successor(-1, 1)) // North-East
			{
				return;
			}
			if (Successor(-1, -1)) // North-West
			{
				return;
			}
			if (Successor(1, 1)) // South-East
			{
				return;
			}
			if (Successor(1, -1)) // South-West
			{
				return;
			}
		}

		if (foundDest == false)
		{
			//std::cout << "Failed to find the destination cell\n";
		}
	}
}

void AStar::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}

void AStar::GetMap(std::vector<std::vector<int>>& map)
{
	map = m_map;
}

void AStar::PopulateCellDetails()
{
	for (int i = 0; i < m_iRows; i++)
	{
		std::vector<Cell> cellVec;

		Cell cellDetails;
		cellDetails.f = FLT_MAX;
		cellDetails.g = FLT_MAX;
		cellDetails.h = FLT_MAX;
		cellDetails.cRow = -1;
		cellDetails.cCol = -1;

		for (int j = 0; j < m_iCols; j++)
		{
			cellVec.push_back(cellDetails);
		}
		m_cellDetails.push_back(cellVec);
	}

	curRow = startingPos.first;
	curCol = startingPos.second;

	m_cellDetails[curRow][curCol].f = 0.0;
	m_cellDetails[curRow][curCol].g = 0.0;
	m_cellDetails[curRow][curCol].h = 0.0;
	m_cellDetails[curRow][curCol].cRow = curRow;
	m_cellDetails[curRow][curCol].cCol = curCol;
}
