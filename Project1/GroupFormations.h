#pragma once
#include "AStar.h"

class GroupFormations
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void FormFixedGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize);

	void SaveMap();

private:
	AStar* aStar;

	std::vector<std::vector<int>> m_map;

	std::vector<Pair> startingPos;
	Pair endingPos;
};

