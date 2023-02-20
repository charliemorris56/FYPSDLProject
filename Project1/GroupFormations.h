#pragma once
#include "AStar.h"
#include <thread>

struct AgentConnections
{
	std::pair<int, int> pos;
	int id;
	int distance;

	bool operator < (const AgentConnections& str) const
	{
		return (distance < str.distance);
	}
};

class GroupFormations
{
public:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	void FixedGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize);
	void FixedGroupVirtualLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize);
	void FixedGroup(Pair src, Pair dest, bool diagonal);

	void FuzzyGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize);
	void FuzzyGroupVirtualLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize);

	void SaveMap();

	void SetThreadSize(int threadSize);
	void SetThreadPerGroup(bool threadPerGroup);

private:
	void ValidatePosition(Pair& virtualLeader, std::vector<Pair>& agents);

	void LeaderClosestToTheCenter(std::vector<Pair>& agents);

	void FuzzyGroup(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize, bool physical);

	AStar* aStar;

	std::vector<std::vector<int>> m_map;

	std::vector<Pair> startingPos;
	std::vector<Pair> startingLeaderPos;
	Pair endingPos;

	int m_iThreadSize = 1;
	bool m_bThreadPerGroup = false;
};

