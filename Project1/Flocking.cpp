#include "Flocking.h"

void Flocking::FlockingPathfinding(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal)
{
	m_map = map;
	endingPos = dest;

	for (int i = 0; i < agents.size(); i++)
	{
		startingPos.push_back(agents[i]);

		aStar = new AStar();
		aStar->SetIsFlocking();

		if (!m_flockingPath.empty())
		{
			ClosestFlockingPath(agents[i]);
		}
		else
		{
			endingPositons.push_back(endingPos);
		}

		if (endingPositons[i] == endingPos)
		{
			aStar->SetIsPathFlocking();
		}

		aStar->AStarSearch(m_map, agents[i], endingPositons[i], diagonal);
		aStar->GetMap(m_map);
		aStar->GetFlockingPath(m_flockingPath);

		if (endingPositons[i] == endingPos)
		{
			aStar->GetFlockingPath(m_firstFlockingPath);
		}

		delete aStar;
	}

	for (int i = 0; i < m_firstFlockingPath.size(); i++)
	{
		m_map[m_firstFlockingPath[i].first][m_firstFlockingPath[i].second] = 2;
	}

}

void Flocking::ClosestFlockingPath(Pair& agent)
{
	float closestDisanct = FLT_MAX;
	float distance = 0;
	Pair closestFlockingPath;

	for (int i = 0; i < m_flockingPath.size(); i++)
	{
		distance = pow(agent.first - m_flockingPath[i].first, 2) + pow(agent.second - m_flockingPath[i].second, 2);
		if (distance < closestDisanct)
		{
			closestDisanct = distance;
			closestFlockingPath = { m_flockingPath[i].first , m_flockingPath[i].second };
		}
	}

	distance = pow(agent.first - endingPos.first, 2) + pow(agent.second - endingPos.second, 2);
	if (distance < closestDisanct)
	{
		closestDisanct = distance;
		closestFlockingPath = { endingPos.first , endingPos.second };
	}

	endingPositons.push_back(closestFlockingPath);
}

void Flocking::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}
