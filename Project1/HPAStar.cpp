#include "HPAStar.h"

bool HPAStar::IsValid(int row, int col)
{
	bool isInRange = (row >= 0) && (row < m_iRows) && (col >= 0) && (col < m_iCols);
	return isInRange;
}

bool HPAStar::IsUnBlocked(int row, int col)
{
	bool isCellBlocked = m_hiMap[row][col] == 1;
	return isCellBlocked;
}

bool HPAStar::IsUnBlockedOriginalMap(int row, int col)
{
	//bool isCellBlocked = m_hiMap[row][col] == 1;
	bool isCellBlocked = m_map[row][col] != 0;
	return isCellBlocked;
}

bool HPAStar::InitChecks()
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

bool HPAStar::IsDestination(int row, int col)
{
	bool isDestination = row == endingPos.first && col == endingPos.second;
	return isDestination;
}

double HPAStar::CalculateHuristicValue(int row, int col)
{
	double huristic = ((double)sqrt((row - endingPos.first) * (row - endingPos.first) + (col - endingPos.second) * (col - endingPos.second)));
	return huristic;
}

void HPAStar::TracePath()
{
	std::cout << "\nThe Path is ";

	int row = endingPos.first;
	int col = endingPos.second;


	while (!(m_cellDetails[row][col].cRow == row && m_cellDetails[row][col].cCol == col))
	{
		m_Path.push(std::make_pair(row, col));
		int temp_col = m_cellDetails[row][col].cCol;
		int temp_row = m_cellDetails[row][col].cRow;
		row = temp_row;
		col = temp_col;
	}

	m_Path.push(std::make_pair(row, col)); 
	ProcessPath();
	//while (!m_Path.empty())
	//{
	//	

	//	std::pair<int, int> p = m_Path.top();
	//	m_Path.pop();
	//	printf("-> (%d,%d) ", p.first, p.second);
	//	m_map[p.first][p.second] = 2;
	//}
}

void HPAStar::ProcessPath()
{
	AStar aStar;
	std::stack<Pair> PathCopy = m_Path;
	int rows = 0;
	int cols = 0;

	while (!PathCopy.empty())
	{
		PathCopy.pop();
		if (PathCopy.size() != 0)
		{
			PathCopy.pop();

			std::pair<int, int> p = PathCopy.top();

			rows = (hiSize * (p.first + 1) - hiSize) / 2;
			cols = (hiSize * (p.second + 1) - hiSize) / 2;

			endingPos.first = rows;
			endingPos.second = cols;

			int maxX = 0;
			int maxY = 0;
			while (!IsUnBlockedOriginalMap(endingPos.first, endingPos.second))
			{
				if (maxX + 1 != hiSize)
				{
					endingPos.first++;
					maxX++;
				}
				else if (maxY + 1 != hiSize)
				{
					endingPos.first -= maxX;
					maxX = 0;
					endingPos.second++;
					maxY++;
				}
			}
		}
		else
		{
			endingPos = endingPosCopy;
		}

		static bool firstTime = true;

		if (firstTime)
		{
			aStar.AStarSearch(m_map, startingPos, endingPos, true);
			firstTime = false;
		}
		else
		{
			aStar.AStarSearchNoMap(startingPos, endingPos, true);
		}

		startingPos = endingPos;		
	}

	aStar.GetMap(m_map);


}

bool HPAStar::Successor(int row, int col)
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

void HPAStar::ProcessMap(std::vector<std::vector<int>>& map, int hierarchicalSize, std::string name)
{
	hiSize = hierarchicalSize;
	std::vector<int> hiRow;

	m_iRows = map.size();
	m_iCols = map[0].size();

	m_iHiRows = m_iRows * 2 / hiSize - 1;
	m_iHiCols = m_iCols * 2 / hiSize - 1;

	for (int i = 0; i < m_iHiRows; i++)
	{
		hiRow.push_back(0);
	}

	for (int i = 0; i < m_iHiCols; i++)
	{
		m_hiMap.push_back(hiRow);
	}

	int hiMapRow = 0;
	int hiMapCol = 0;

	for (int i = 0; i < m_iRows; i++)
	{
		bool nextHiMapRow = i % hiSize == 0 && i != 0;
		if (nextHiMapRow)
		{
			hiMapRow += 2;
		}
		for (int j = hiSize - 1; j < m_iCols; j+=hiSize)
		{
			bool rightEdge = (j + 1) % m_iCols == 0;
			if (!rightEdge)
			{
				int temp1 = map[i][j];
				int temp2 = map[i][j + 1];
				if (map[i][j] == 1 && map[i][j + 1] == 1)
				{
					m_hiMap[hiMapRow][hiMapCol] = 1;
					m_hiMap[hiMapRow][hiMapCol + 1] = 1;
					m_hiMap[hiMapRow][hiMapCol + 2] = 1;
					hiMapCol += 2;
				}
			}
		}
		hiMapCol = 0;
	}

	hiMapRow = 0;
	hiMapCol = 0;

	for (int i = 0; i < m_iCols; i++)
	{
		bool nextHiMapCol = i % hiSize == 0 && i != 0;
		if (nextHiMapCol)
		{
			hiMapCol += 2;
		}
		for (int j = hiSize - 1; j < m_iRows; j += hiSize)
		{
			bool topEdge = (j + 1) % m_iRows == 0;
			if (!topEdge)
			{
				int temp1 = map[j][i];
				int temp2 = map[j + 1][i];
				if (map[j][i] == 1 && map[j + 1][i] == 1)
				{
					m_hiMap[hiMapRow][hiMapCol] = 1;
					m_hiMap[hiMapRow + 1][hiMapCol] = 1;
					m_hiMap[hiMapRow + 2][hiMapCol] = 1;
					hiMapRow += 2;
				}
			}
		}
		hiMapRow = 0;
	}

	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_hiMap, name);

	m_map = m_hiMap;

}

void HPAStar::HPAStarSearch(std::vector<std::vector<int>>& originalMap, std::vector<std::vector<int>>& hiMap, int hierarchicalSize, Pair src, Pair dest, bool diagonal)
{
	m_hiMap = hiMap;
	m_map = originalMap;
	hiSize = hierarchicalSize;
	m_iRows = m_hiMap.size();
	m_iCols = m_hiMap[0].size();

	endingPosCopy = dest;
	startingPos.first = src.first * 2 / hiSize;
	startingPos.second = src.second * 2 / hiSize;
	endingPos.first = dest.first * 2 / hiSize;
	endingPos.second = dest.second * 2 / hiSize;

	if (startingPos.first % 2 != 0)
	{
		startingPos.first--;
	}
	if (startingPos.second % 2 != 0)
	{
		startingPos.second--;
	}
	if (endingPos.first % 2 != 0)
	{
		endingPos.first--;
	}
	if (endingPos.second % 2 != 0)
	{
		endingPos.second--;
	}

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

void HPAStar::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}

void HPAStar::PopulateCellDetails()
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
