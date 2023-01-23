#include "HPAStar.h"

bool HPAStar::IsValid(int row, int col)
{
	bool isInRange = (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLUMNS);
	return isInRange;
}

bool HPAStar::IsUnBlocked(int map[][COLUMNS], int row, int col)
{
	bool isCellBlocked = map[row][col] == 1;
	return isCellBlocked;
}

bool HPAStar::InitChecks(int map[][COLUMNS], Pair src, Pair dest)
{
	if (!IsValid(src.first, src.second))
	{
		std::cout << "Source is invalid";
		return false;
	}

	if (!IsValid(dest.first, dest.second))
	{
		std::cout << "Destination is invalid";
		return false;
	}

	if (!IsUnBlocked(map, src.first, src.second)) {
		std::cout << "Source is blocked\n";
		return false;
	}

	if (!IsUnBlocked(map, dest.first, dest.second))
	{
		std::cout << "Destination is blocked\n";
		return false;
	}

	if (IsDestination(src.first, src.second, dest)) {
		std::cout << "Source = destination\n";
		return false;
	}

	return true;
}

bool HPAStar::IsDestination(int row, int col, Pair dest)
{
	bool isDestination = row == dest.first && col == dest.second;
	return isDestination;
}

double HPAStar::CalculateHuristicValue(int row, int col, Pair dest)
{
	double huristic = ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
	return huristic;
}

void HPAStar::TracePath(int map[][COLUMNS], Cell cellDetails[][COLUMNS], Pair dest)
{
	std::cout << "\nThe Path is ";

	int row = dest.first;
	int col = dest.second;

	std::stack<Pair> Path;

	while (!(cellDetails[row][col].cRow == row && cellDetails[row][col].cCol == col))
	{
		Path.push(std::make_pair(row, col));
		int temp_row = cellDetails[row][col].cRow;
		int temp_col = cellDetails[row][col].cCol;
		row = temp_row;
		col = temp_col;
	}

	Path.push(std::make_pair(row, col));
	while (!Path.empty())
	{
		std::pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
		map[p.first][p.second] = 2;
	}
}

bool HPAStar::Successor(int map[][COLUMNS], int row, int col, Pair dest)
{
	if (IsValid(curRow + row, curCol + col))
	{
		if (IsDestination(curRow + row, curCol + col, dest))
		{
			cellDetails[curRow + row][curCol + col].cRow = curRow;
			cellDetails[curRow + row][curCol + col].cCol = curCol;
			std::cout << "The destination cell is found\n";
			TracePath(map, cellDetails, dest);
			foundDest = true;
			return true;
		}
		// Seccessor already on the closed list or is blocked
		else if (!closedList[curRow + row][curCol + col] && IsUnBlocked(map, curRow + row, curCol + col))
		{
			gNew = cellDetails[curRow][curCol].g + 1.0;
			hNew = CalculateHuristicValue(curRow + row, curCol + col, dest);
			fNew = gNew + hNew;

			// Add to the open list
			if (cellDetails[curRow + row][curCol + col].f == FLT_MAX || cellDetails[curRow + row][curCol + col].f > fNew)
			{
				openList.insert(std::make_pair(fNew, std::make_pair(curRow + row, curCol + col)));

				cellDetails[curRow + row][curCol + col].f = fNew;
				cellDetails[curRow + row][curCol + col].g = gNew;
				cellDetails[curRow + row][curCol + col].h = hNew;
				cellDetails[curRow + row][curCol + col].cRow = curRow;
				cellDetails[curRow + row][curCol + col].cCol = curCol;
			}
		}
	}
	return false;
}

void HPAStar::ProcessMap(int map[][COLUMNS])
{
	std::vector<std::vector<int>> hiMap;
	std::vector<int> hiRow;

	for (int i = 0; i < ROWS * 2 / hiSize - 1; i++)
	{
		hiRow.push_back(0);
	}

	for (int i = 0; i < COLUMNS * 2 / hiSize - 1; i++)
	{
		hiMap.push_back(hiRow);
	}

	int hiMapRow = 0;
	for (int i = 0; i < ROWS; i++)
	{
		if (i % hiSize == 0 && i != 0)
		{
			hiMapRow += 2;
		}
		for (int j = hiSize - 1; j < COLUMNS; j+=hiSize)
		{
			bool rightEdge = (j + 1) % COLUMNS == 0;
			if (!rightEdge)
			{
				int temp1 = map[i][j];
				int temp2 = map[i][j + 1];
				if (map[i][j] == 1 && map[i][j + 1] == 1)
				{
					hiMap[hiMapRow][int(j / hiSize)] = 1;
					hiMap[hiMapRow][int(j / hiSize) + 1] = 1;
					hiMap[hiMapRow][int(j / hiSize) + 2] = 1;
				}
			}
		}
	}

	int hiMapCol = 0;
	for (int i = 0; i < COLUMNS; i++)
	{
		if (i % hiSize == 0 && i != 0)
		{
			hiMapCol += 2;
		}
		for (int j = hiSize - 1; j < ROWS; j += hiSize)
		{
			bool rightEdge = (j + 1) % ROWS == 0;
			if (!rightEdge)
			{
				int temp1 = map[j][i];
				int temp2 = map[j + 1][i];
				if (map[j][i] == 1 && map[j + 1][i] == 1)
				{
					hiMap[int(j / hiSize)][hiMapCol] = 1;
					hiMap[int(j / hiSize) + 1][hiMapCol] = 1;
					hiMap[int(j / hiSize) + 2][hiMapCol] = 1;
				}
			}
		}
	}

	int tmep = 5;
}

void HPAStar::Search(int map[][COLUMNS], Pair src, Pair dest, bool diagonal, int hierarchicalSize)
{
	//startingPos = src;
	//endingPos = src;
	hiSize = hierarchicalSize;

	ProcessMap(map);

	if (!InitChecks(map, src, dest))
	{
		return;
	}

	memset(closedList, false, sizeof(closedList));
	//std::vector<bool> cl(ROWS * COLUMNS, false); //This vector does the same thing, might need it

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].cRow = -1;
			cellDetails[i][j].cCol = -1;
		}
	}

	curRow = src.first;
	curCol = src.second;

	cellDetails[curRow][curCol].f = 0.0;
	cellDetails[curRow][curCol].g = 0.0;
	cellDetails[curRow][curCol].h = 0.0;
	cellDetails[curRow][curCol].cRow = curRow;
	cellDetails[curRow][curCol].cCol = curCol;

	openList.insert(std::make_pair(0.0, std::make_pair(curRow, curCol)));

	foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		curRow = p.second.first;
		curCol = p.second.second;
		closedList[curRow][curCol] = true;

		if (Successor(map, -1, 0, dest)) // North
		{
			return;
		}
		if (Successor(map, 0, 1, dest)) // South
		{
			return;
		}
		if (Successor(map, 0, -1, dest)) // East
		{
			return;
		}
		if (Successor(map, 1, 0, dest)) // West
		{
			return;
		}

		if (diagonal)
		{
			if (Successor(map, -1, 1, dest)) // North-East
			{
				return;
			}
			if (Successor(map, -1, -1, dest)) // North-West
			{
				return;
			}
			if (Successor(map, 1, 1, dest)) // South-East
			{
				return;
			}
			if (Successor(map, 1, -1, dest)) // South-West
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
