#include "JumpPointSearchMe.h"

JumpPointSearchMe::~JumpPointSearchMe()
{
	delete[] closedList;
	delete[] m_cellDetails;
}

bool JumpPointSearchMe::IsValid(int row, int col)
{
	bool isInRange = (row >= 0) && (row < m_iRows) && (col >= 0) && (col < m_iCols);
	return isInRange;
}

bool JumpPointSearchMe::IsUnBlocked(int row, int col)
{
	bool isCellBlocked = m_map[row][col] == 1;
	return isCellBlocked;
}

bool JumpPointSearchMe::InitChecks()
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

bool JumpPointSearchMe::IsDestination(int row, int col)
{
	bool isDestination = row == endingPos.first && col == endingPos.second;
	return isDestination;
}

double JumpPointSearchMe::CalculateHuristicValue(int row, int col)
{
	double huristic = ((double)sqrt((row - endingPos.first) * (row - endingPos.first) + (col - endingPos.second) * (col - endingPos.second)));
	return huristic;
}

void JumpPointSearchMe::TracePath()
{
	std::cout << "\nThe Path is ";

	int row = endingPos.first;
	int col = endingPos.second;

	std::stack<Pair> Path;

	while (!(m_cellDetails[row * m_iCols + col].cRow == row && m_cellDetails[row * m_iCols + col].cCol == col))
	{
		Path.push(std::make_pair(row, col));
		int temp_row = m_cellDetails[row * m_iCols + col].cRow;
		int temp_col = m_cellDetails[row * m_iCols + col].cCol;
		row = temp_row;
		col = temp_col;
	}

	Path.push(std::make_pair(row, col));

	//for (int i = 0; i < Path.size(); i++)
	//{
	//	std::pair<int, int> p = Path.top();
	//	Path.pop();
	//	printf("-> (%d,%d) ", p.first, p.second);
	//	m_map[p.first][p.second] = 2;
	//}
	while (!Path.empty()) //todo add if path size is one stop, will fix bug
	{
		std::pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
		m_map[p.first][p.second] = 2;
	}
}

bool JumpPointSearchMe::Successor(int row, int col)
{
	if (IsValid(curRow + row, curCol + col))
	{
		if (IsDestination(curRow + row, curCol + col))
		{
			m_cellDetails[(curRow + row) * m_iCols + curCol + col].cRow = curRow;
			m_cellDetails[(curRow + row) * m_iCols + curCol + col].cCol = curCol;
			std::cout << "The destination cell is found\n";
			TracePath();
			foundDest = true;
			return true;
		}

		while (IsValid(curRow + row, curCol + col) && !closedList[(curRow + row) * m_iCols + curCol + col] && IsUnBlocked(curRow + row, curCol + col))
		{
			gNew = m_cellDetails[curRow * m_iCols + curCol].g + 1.0;
			hNew = CalculateHuristicValue(curRow + row, curCol + col);
			fNew = gNew + hNew;
			if (row != 0 && col != 0)
				gNew += 0.42; //sqrt(2)	

			// Add to the open list
			if (m_cellDetails[(curRow + row) * m_iCols + curCol + col].f == FLT_MAX || m_cellDetails[(curRow + row) * m_iCols + curCol + col].f > fNew)
			{
				openList.insert(std::make_pair(fNew, std::make_pair(curRow + row, curCol + col)));

				m_cellDetails[(curRow + row) * m_iCols + curCol + col].f = fNew;
				m_cellDetails[(curRow + row) * m_iCols + curCol + col].g = gNew;
				m_cellDetails[(curRow + row) * m_iCols + curCol + col].h = hNew;
				m_cellDetails[(curRow + row) * m_iCols + curCol + col].cRow = curRow;
				m_cellDetails[(curRow + row) * m_iCols + curCol + col].cCol = curCol;
			}

			if (row < 0)
			{
				row--;
			}			
			if (row > 0)
			{
				row++;
			}
			if (col < 0)
			{
				col--;
			}
			if (col > 0)
			{
				col++;
			}
		}
	}
	return false;
}

void JumpPointSearchMe::JumpPointSearch(std::vector<std::vector<int>>& map, Pair src, Pair dest, bool diagonal)
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

	closedList = new int[m_iRows * m_iCols];

	for (int i = 0; i < m_iRows * m_iCols; i++)
	{
		closedList[i] = false;
	}

	PopulateCellDetails();

	openList.insert(std::make_pair(0.0, std::make_pair(curRow, curCol)));

	foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		curRow = p.second.first;
		curCol = p.second.second;
		closedList[curRow * m_iCols + curCol] = true;

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

void JumpPointSearchMe::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}

void JumpPointSearchMe::PopulateCellDetails()
{
	m_cellDetails = new Cell[m_iRows * m_iCols];

	std::vector<Cell> cellVec;

	Cell cellDetails;
	cellDetails.f = FLT_MAX;
	cellDetails.g = FLT_MAX;
	cellDetails.h = FLT_MAX;
	cellDetails.cRow = -1;
	cellDetails.cCol = -1;

	for (int i = 0; i < m_iRows * m_iCols; i++)
	{
		m_cellDetails[i] = cellDetails;
	}

	curRow = startingPos.first;
	curCol = startingPos.second;

	m_cellDetails[curRow * m_iCols + curCol].f = 0.0;
	m_cellDetails[curRow * m_iCols + curCol].g = 0.0;
	m_cellDetails[curRow * m_iCols + curCol].h = 0.0;
	m_cellDetails[curRow * m_iCols + curCol].cRow = curRow;
	m_cellDetails[curRow * m_iCols + curCol].cCol = curCol;
}
