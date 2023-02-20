#include "GroupFormations.h"

void GroupFormations::FixedGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize)
{
	m_map = map;
	endingPos = dest;

	int leader = 0;
	int groups = ceil(float(agents.size()) / float(groupSize));

	for (int i = 0; i < agents.size(); i++)
	{
		bool groupLeader = i % groupSize == 0;
		if (groupLeader)
		{
			leader = i;
			startingLeaderPos.push_back(agents[leader]);
		}
		else
		{
			aStar = new AStar();
			aStar->AStarSearch(m_map, agents[i], agents[leader], diagonal);
			aStar->GetMap(m_map);
			delete aStar;

			startingPos.push_back(agents[i]);
		}
	}

	GroupPathing(groups, startingLeaderPos, dest, diagonal);
}

void GroupFormations::FixedGroupVirtualLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize)
{
	m_map = map;
	endingPos = dest;

	std::vector<Pair> agentsInGroup;
	std::vector<Pair> virtualLeadersPos;
	Pair virtualLeaderPos = { 0,0 };

	int groups = ceil(float(agents.size()) / float(groupSize));

	for (int i = 0; i < agents.size(); i++)
	{
		virtualLeaderPos.first += agents[i].first;
		virtualLeaderPos.second += agents[i].second;

		agentsInGroup.push_back(agents[i]);

		bool groupLeader = ((i + 1) % groupSize == 0) || (i == agents.size() - 1);
		if (groupLeader)
		{
			int currentGroupSize = (i + 1) % groupSize;
			virtualLeaderPos.first /= (groupSize - currentGroupSize);
			virtualLeaderPos.second /= (groupSize - currentGroupSize);

			ValidatePosition(virtualLeaderPos, agentsInGroup);

			virtualLeadersPos.push_back(virtualLeaderPos);
			virtualLeaderPos = { 0,0 };

			agentsInGroup.clear();
		}
	}

	int leader = -1;

	for (int i = 0; i < agents.size(); i++)
	{
		bool groupLeader = i % groupSize == 0;
		if (groupLeader)
		{
			leader++;
			startingLeaderPos.push_back(virtualLeadersPos[leader]);
		}

		aStar = new AStar();
		aStar->AStarSearch(m_map, agents[i], virtualLeadersPos[leader], diagonal);
		aStar->GetMap(m_map);
		delete aStar;

		startingPos.push_back(agents[i]);
	}

	GroupPathing(groups, virtualLeadersPos, dest, diagonal);
}

void GroupFormations::GroupPathing(int groups, std::vector<Pair> src, Pair dest, bool diagonal)
{
	if (m_bThreadPerGroup)
	{
		std::vector<std::thread> threadVec;
		for (int i = 0; i < groups; i++)
		{
			vecAStar.push_back(new AStar());
			std::vector<Pair> path;
			m_path.push_back(path);

			threadVec.push_back(std::thread(&GroupFormations::FixedGroupThread, this, src[i], dest, diagonal, i));
		}
		for (int i = 0; i < groups; i++)
		{
			threadVec[i].join();
			for (int j = 0; j < m_path[i].size(); j++)
			{
				m_map[m_path[i][j].first][m_path[i][j].second] = 7;
			}
		}
	}
	else
	{
		for (int i = 0; i < groups; i++)
		{
			FixedGroup(src[i], dest, diagonal);
		}
	}
}

void GroupFormations::FixedGroup(Pair src, Pair dest, bool diagonal)
{
	aStar = new AStar();
	aStar->AStarSearch(m_map, src, dest, diagonal, true);
	aStar->GetMap(m_map);
	delete aStar;
}

void GroupFormations::FixedGroupThread(Pair src, Pair dest, bool diagonal, int num)
{
	vecAStar[num]->AStarSearch(m_map, src, dest, diagonal, true);
	m_path[num] = vecAStar[num]->GetFlockingPath();
}

void GroupFormations::FuzzyGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize)
{
	FuzzyGroup(map, agents, dest, diagonal, groupSize, true);

	FixedGroupFixedLeader(map, agents, dest, diagonal, groupSize);
}

void GroupFormations::FuzzyGroupVirtualLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize)
{
	FuzzyGroup(map, agents, dest, diagonal, groupSize, false);

	FixedGroupVirtualLeader(map, agents, dest, diagonal, groupSize);
}

void GroupFormations::FuzzyGroup(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize, bool physical)
{
	std::vector<Pair> newAgentsGroup;
	std::vector<AgentConnections> connections;
	std::vector<int> usedIds;

	for (int i = 0; i < agents.size(); i++)
	{
		if (std::find(usedIds.begin(), usedIds.end(), i) == usedIds.end())
		{
			for (int j = i + 1; j < agents.size(); j++)
			{
				AgentConnections connection;
				connection.distance = pow(agents[i].first - agents[j].first, 2) + pow(agents[i].second - agents[j].second, 2);
				connection.id = j;
				connection.pos = agents[j];
				connections.push_back(connection);
			}

			std::sort(connections.begin(), connections.end());

			for (int j = 0; j < groupSize - 1; j++)
			{
				if (j == 0)
				{
					newAgentsGroup.push_back(agents[i]);
				}
				if (j < connections.size())
				{
					newAgentsGroup.push_back(agents[connections[j].id]);
					usedIds.push_back(connections[j].id);
				}
			}

			if (physical)
			{
				LeaderClosestToTheCenter(newAgentsGroup);
			}

			connections.clear();
		}
	}

	agents = newAgentsGroup;
}

void GroupFormations::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, startingLeaderPos, endingPos);
}

void GroupFormations::SetThreadSize(int threadSize)
{
	m_iThreadSize = threadSize;
}

void GroupFormations::SetThreadPerGroup(bool threadPerGroup)
{
	m_bThreadPerGroup = threadPerGroup;
}

void GroupFormations::ValidatePosition(Pair& virtualLeader, std::vector<Pair>& agents)
{
	bool isCellBlocked = m_map[virtualLeader.first][virtualLeader.second] != 0;

	if (isCellBlocked)
	{
		return;
	}

	int distance = INT_MAX;
	int closestAgent = 0;

	for (int i = 0; i < agents.size(); i++)
	{
		int distanceTemp = pow(virtualLeader.first - agents[i].first, 2) + pow(virtualLeader.second - agents[i].second, 2);
		if (distanceTemp < distance)
		{
			distance = distanceTemp;
			closestAgent = i;
		}
	}

	while (!isCellBlocked)
	{
		if (agents[closestAgent].first > virtualLeader.first)
		{
			virtualLeader.first++;
		}
		else if (agents[closestAgent].first < virtualLeader.first)
		{
			virtualLeader.first--;
		}

		if (agents[closestAgent].second > virtualLeader.second)
		{
			virtualLeader.second++;
		}
		else if (agents[closestAgent].second < virtualLeader.second)
		{
			virtualLeader.second--;
		}

		isCellBlocked = m_map[virtualLeader.first][virtualLeader.second] != 0;
	}
}

void GroupFormations::LeaderClosestToTheCenter(std::vector<Pair>& agents)
{
	Pair center = {0, 0};

	for (int i = 0; i < agents.size(); i++)
	{
		center.first += agents[i].first;
		center.second += agents[i].second;
	}

	center.first /= agents.size();
	center.second /= agents.size();

	int distance = INT_MAX;
	int closestAgent = 0;

	for (int i = 0; i < agents.size(); i++)
	{
		int distanceTemp = pow(center.first - agents[i].first, 2) + pow(center.second - agents[i].second, 2);
		if (distanceTemp < distance)
		{
			distance = distanceTemp;
			closestAgent = i;
		}
	}

	std::iter_swap(agents.begin() + closestAgent, agents.begin());

}
