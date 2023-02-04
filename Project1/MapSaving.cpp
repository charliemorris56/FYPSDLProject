#include "MapSaving.h"

void MapSaving::SaveMapToJson(std::vector<std::vector<int>>& map, std::string name)
{
    mapVector.rows = map.size();
    mapVector.cols = map[0].size();

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            mapVector.tile.push_back(map[i][j]);
        }
    }

    name += ".json";
    JsonLoading::SaveJson(mapVector, name);
}

void MapSaving::SaveMapToJson(std::vector<std::vector<int>>& map, AStar::Pair src, AStar::Pair dest)
{
    map[src.first][src.second] = 4;
    map[dest.first][dest.second] = 5;

    mapVector.rows = map.size();
    mapVector.cols = map[0].size();

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            mapVector.tile.push_back(map[i][j]);
        }
    }

    JsonLoading::SaveJson(mapVector, "map.json");
}

void MapSaving::SaveMapToJson(std::vector<std::vector<int>>& map, std::vector<std::pair<int, int>> src, std::pair<int, int> dest)
{
    map[src[0].first][src[0].second] = 6;

    for (int i = 1; i < src.size(); i++)
    {
        map[src[i].first][src[i].second] = 4;
    }

    map[dest.first][dest.second] = 5;

    mapVector.rows = map.size();
    mapVector.cols = map[0].size();

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            mapVector.tile.push_back(map[i][j]);
        }
    }

    JsonLoading::SaveJson(mapVector, "map.json");
}

void MapSaving::LoadMapFromJson(std::vector<std::vector<int>>& map, std::string name)
{
    Map mapVector;
    std::string filePath = "C:\\Users\\charl\\source\\repos\\Project1\\x64\\Debug\\" + name + ".json";
    JsonLoading::LoadJson(mapVector, filePath);

    for (int i = 0; i < mapVector.rows; i++)
    {
        std::vector<int> mapRow;
        for (int j = 0; j < mapVector.cols; j++)
        {
            mapRow.push_back(mapVector.tile[i * mapVector.rows + j]);
        }
        map.push_back(mapRow);
        mapRow.clear();
    }
}
