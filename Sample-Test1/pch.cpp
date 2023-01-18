#include "pch.h"

pch::pch()
{
}

pch::~pch()
{
}

void pch::SaveMapToJson(int map[][COLUMNS], AStar::Pair src, AStar::Pair dest)
{
    map[src.first][src.second] = 4;
    map[dest.first][dest.second] = 5;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            Map mMap;
            mMap.tile = map[i][j];
            mapVector.push_back(mMap);
        }
    }
    JsonLoading::SaveJson(mapVector, "map.json");
}
