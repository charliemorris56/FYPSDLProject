#pragma once
#include "AStar.h"

class Flocking
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void FlockingPathfinding(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, float radius);

	void SaveMap();
private:
	AStar* aStar;

	std::vector<std::vector<int>> m_map;

	std::vector<Pair> startingPos;
	std::vector<Pair> startingLeaderPos;
	Pair endingPos;

	std::vector<Pair> m_flockingPath;
};

