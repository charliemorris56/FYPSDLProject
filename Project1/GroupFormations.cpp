#include "GroupFormations.h"

void GroupFormations::FormFixedGroupFixedLeader(std::vector<std::vector<int>>& map, std::vector<Pair>& agents, Pair dest, bool diagonal, int groupSize)
{
	m_map = map;
	endingPos = dest;

	for (int i = 1; i < groupSize; i++)
	{
		aStar = new AStar();
		aStar->AStarSearch(m_map, agents[i], agents[0], diagonal);
		aStar->GetMap(m_map);
		delete aStar;
	}
	
	aStar = new AStar();
	aStar->AStarSearch(m_map, agents[0], dest, diagonal, true);
	aStar->GetMap(m_map);
	delete aStar;

	for (int i = 0; i < groupSize; i++)
	{
		startingPos.push_back(agents[i]);
	}
}

void GroupFormations::SaveMap()
{
	MapSaving mapSaving;
	mapSaving.SaveMapToJson(m_map, startingPos, endingPos);
}
