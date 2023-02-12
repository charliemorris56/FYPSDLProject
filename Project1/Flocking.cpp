#include "Flocking.h"

void Flocking::FlockingPathfinding(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, float radius)
{
	m_map = map;
	endingPos = dest;

	for (int i = 0; i < agents.size(); i++)
	{
		startingPos.push_back(agents[i]);

		aStar = new AStar();
		aStar->SetRadius(radius);

		if (!m_flockingPath.empty())
		{
			aStar->SetFlockingPath(m_flockingPath);
		}

		aStar->AStarSearch(m_map, agents[i], dest, diagonal);
		aStar->GetMap(m_map);
		aStar->GetFlockingPath(m_flockingPath);

		delete aStar;
	}

}

void Flocking::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}
