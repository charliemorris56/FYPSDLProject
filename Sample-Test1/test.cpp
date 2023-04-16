#include "pch.h"
#include "TileMap.h"
#include "TileMap.cpp"
#include "AStar.h"
#include "AStar.cpp"
#include "JsonLoading.h"
#include "JumpPointSearchMe.h"
#include "JumpPointSearchMe.cpp"
#include "HPAStar.h"
#include "HPAStar.cpp"
#include "Map.h"
#include "MapSaving.h"
#include "MapSaving.cpp"
#include "GroupFormations.h"
#include "GroupFormations.cpp"
#include "Flocking.h"
#include "Flocking.cpp"
#include <chrono>

TEST(AStar, OneAgent10x10Diagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;
    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10v, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent10x10CupDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(9, 9);
    aStar.AStarSearch(map10x10Cupv, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent10x10CupNoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(9, 9);
    aStar.AStarSearch(map10x10Cupv, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent10x10NoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;

    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10v, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent100x100Diagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;

    AStar::Pair src = std::make_pair(99, 99);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map100x100v, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent100x100NoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;
    AStar::Pair src = std::make_pair(99, 99);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map100x100v, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent100x100ClearNoDiagonal)
{
    MapSaving mapSaving;
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    AStar aStar;
    AStar::Pair src = std::make_pair(99, 99);
    AStar::Pair dest = std::make_pair(0, 0);
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(map, "100x100Clear");
    aStar.AStarSearch(map, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent512x512Diagonal)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(510, 510);
    //mapSaving.LoadMapFromJson(map, "512x512");
    //mapSaving.LoadMapFromJson(map, "512x512_2");
    mapSaving.LoadMapFromJson(map, "512x512_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    aStar.AStarSearch(map, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent128x128MazeDiagonal)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(127, 127);
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    aStar.AStarSearch(map, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent128x128MazeNoDiagonal)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(127, 127);
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    aStar.AStarSearch(map, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    aStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10NoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.JumpPointSearch(map10x10v, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100Diagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(0, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(99, 99);
    jumpPointSearchMe.JumpPointSearch(map100x100v, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100NoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.JumpPointSearch(map100x100v, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100ClearNoDiagonal)
{
    MapSaving mapSaving;
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(map, "100x100Clear");
    jumpPointSearchMe.JumpPointSearch(map, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10Diagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.JumpPointSearch(map10x10v, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10DiagonalCup)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    JumpPointSearchMe jumpPointSearchMe;
    JumpPointSearchMe::Pair src = std::make_pair(0, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(9, 9);
    jumpPointSearchMe.JumpPointSearch(map10x10Cupv, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent128x128MazeDiagonal)
{
    MapSaving mapSaving;
    JumpPointSearchMe jumpPointSearchMe;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(127, 127);
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    jumpPointSearchMe.JumpPointSearch(map, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent128x128MazeNoDiagonal)
{
    MapSaving mapSaving;
    JumpPointSearchMe jumpPointSearchMe;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(127, 127);
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    jumpPointSearchMe.JumpPointSearch(map, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent512x512Diagonal)
{
    MapSaving mapSaving;
    JumpPointSearchMe jumpPointSearchMe;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(1, 1);
    AStar::Pair dest = std::make_pair(510, 510);
    //mapSaving.LoadMapFromJson(map, "512x512_2");
    //mapSaving.LoadMapFromJson(map, "512x512_clear");
    mapSaving.LoadMapFromJson(map, "512x512_maze");

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    jumpPointSearchMe.JumpPointSearch(map, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10CupDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(9, 9);
    jumpPointSearchMe.JumpPointSearch(map10x10Cupv, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10CupNoDiagonal)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    JumpPointSearchMe jumpPointSearchMe;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(9, 9);
    jumpPointSearchMe.JumpPointSearch(map10x10Cupv, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    jumpPointSearchMe.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, Pre_Processing10x10)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    HPAStar hPAStar;
    int hiSize = 5;
    std::string name = "10x10vPre-Processing" + std::to_string(hiSize);
    hPAStar.ProcessMap(map10x10v, hiSize, name);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, Pre_Processing100x100)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    HPAStar hPAStar;
    int hiSize = 10;
    std::string name = "100x100vPre-Processing" + std::to_string(hiSize);
    hPAStar.ProcessMap(map100x100v, hiSize, name);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, map100x100BottomBlocked)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    HPAStar hPAStar;
    int hiSize = 10;
    std::string name = "map100x100BottomBlocked" + std::to_string(hiSize);
    hPAStar.ProcessMap(map100x100BottomBlocked, hiSize, name);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, Pre_Processing100x100Clear)
{
    std::vector<std::vector<int>> map;
    MapSaving mapSaving;
    mapSaving.LoadMapFromJson(map, "100x100Clear");

    HPAStar hPAStar;
    int hiSize = 5;
    std::string name = "100x100ClearPre-Processing" + std::to_string(hiSize);

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    hPAStar.ProcessMap(map, hiSize, name);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, 100x100)
{
    MapSaving mapSaving;
    HPAStar hPAStar;

    std::vector<std::vector<int>> hiMap;
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(hiMap, "100x100ClearPre-Processing5");
    mapSaving.LoadMapFromJson(map, "100x100Clear");
    int hiSize = 5;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(99, 99);

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    hPAStar.HPAStarSearch(map, hiMap, hiSize, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, 100x100_2)
{
    MapSaving mapSaving;
    HPAStar hPAStar;

    std::vector<std::vector<int>> hiMap;
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(hiMap, "100x100vPre-Processing");
    mapSaving.LoadMapFromJson(map, "100x100Clear");
    int hiSize = 5;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(98, 98);

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    hPAStar.HPAStarSearch(map, hiMap, hiSize, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    hPAStar.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(MapGenerator, 512x512)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(500, 500);

    for (int i = 0; i < 512; i++)
    {
        std::vector<int> mapRow;
        for (int j = 0; j < 512; j++)
        {
            mapRow.push_back(rand() % 3);
        }
        map.push_back(mapRow);
        mapRow.clear();
    }

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    mapSaving.SaveMapToJson(map, "512x512_2");

    EXPECT_TRUE(false) << output;
}

TEST(MapGenerator, 512x512_maze)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;
    AStar::Pair src = std::make_pair(0, 0);
    AStar::Pair dest = std::make_pair(500, 500);

    for (int i = 0; i < 512; i++)
    {
        std::vector<int> mapRow;
        for (int j = 0; j < 512; j++)
        {
            if (j % 9 == 0)
            {
                if ((j % 2 == 0 && i == 500) || (j % 2 != 0 && i == 50))
                {
                    mapRow.push_back(1);
                }
                else
                {
                    mapRow.push_back(0);
                }
            }
            else
            {
                mapRow.push_back(1);
            }
        }
        map.push_back(mapRow);
        mapRow.clear();
    }

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    mapSaving.SaveMapToJson(map, "512x512_maze");

    EXPECT_TRUE(false) << output;
}

TEST(MapGenerator, 128x128_maze)
{
    MapSaving mapSaving;
    AStar aStar;

    std::vector<std::vector<int>> map;

    for (int i = 0; i < 128; i++)
    {
        std::vector<int> mapRow;
        for (int j = 0; j < 128; j++)
        {
            if (j % 9 == 0)
            {
                if ((j % 2 == 0 && i == 100) || (j % 2 != 0 && i == 10))
                {
                    mapRow.push_back(1);
                }
                else
                {
                    mapRow.push_back(0);
                }
            }
            else
            {
                mapRow.push_back(1);
            }
        }
        map.push_back(mapRow);
        mapRow.clear();
    }

    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    mapSaving.SaveMapToJson(map, "128x128_maze");

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize5PhysicalLeaderAgents5)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 2;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 2));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));
    
    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FixedGroupFixedLeader(map10x10Cupv, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize5PhysicalLeaderAgents5_2)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 3;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 1));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FixedGroupFixedLeader(map10x10Clear, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize5PhysicalLeaderAgents5_100x100)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(10, 0));
    agents.push_back(std::make_pair(20, 0));
    agents.push_back(std::make_pair(30, 0));
    agents.push_back(std::make_pair(40, 0));

    AStar::Pair dest = std::make_pair(99, 99);

    groupFormations.FixedGroupFixedLeader(map100x100v, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize5PhysicalLeaderAgents5_128x128Maze)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 5;
    agents.push_back(std::make_pair(0, 1));
    agents.push_back(std::make_pair(10, 1));
    agents.push_back(std::make_pair(20, 1));
    agents.push_back(std::make_pair(30, 1));
    agents.push_back(std::make_pair(40, 1));

    AStar::Pair dest = std::make_pair(127, 127);

    MapSaving mapSaving;
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    groupFormations.FixedGroupFixedLeader(map, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize1PhysicalLeaderAgents5_2)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 1));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FixedGroupFixedLeader(map10x10Clear, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize5VirtualLeaderAgents5_10x10Clear)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 5;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 2));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FixedGroupVirtualLeader(map10x10Clear, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FixedGroupSize2VirtualLeaderAgents5_10x10Cup)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 2));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FixedGroupVirtualLeader(map10x10Cupv, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FuzzyGroupSize5PhysicalLeaderAgents5_10x10Cup)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 5;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 2));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FuzzyGroupFixedLeader(map10x10Cupv, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(GroupFormation, FuzzyGroupSize5VirtualLeaderAgents5_10x10Cup)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 2;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 2));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);

    groupFormations.FuzzyGroupVirtualLeader(map10x10Cupv, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(Flocking, Flocking_10x10Cup)
{
    testing::internal::CaptureStdout();
    auto start = std::chrono::steady_clock::now();

    Flocking flocking;
    std::vector<AStar::Pair> agents;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(0, 6));
    agents.push_back(std::make_pair(3, 7));
    agents.push_back(std::make_pair(4, 3));
    agents.push_back(std::make_pair(7, 0));
    agents.push_back(std::make_pair(8, 3));
    agents.push_back(std::make_pair(9, 9));

    AStar::Pair dest = std::make_pair(8, 8);

    flocking.FlockingPathfinding(map10x10Cupv, agents, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    flocking.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(Threading, FixedGroupSize5PhysicalLeaderAgents5_2)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(2, 0));
    agents.push_back(std::make_pair(4, 1));
    agents.push_back(std::make_pair(6, 2));
    agents.push_back(std::make_pair(8, 3));

    AStar::Pair dest = std::make_pair(8, 8);
    groupFormations.SetThreadPerGroup(true);

    groupFormations.FixedGroupFixedLeader(map10x10Clear, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(Threading, FixedGroupSize5PhysicalLeaderAgents5_100x100)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 0));
    agents.push_back(std::make_pair(10, 0));
    agents.push_back(std::make_pair(20, 0));
    agents.push_back(std::make_pair(30, 0));
    agents.push_back(std::make_pair(40, 0));

    AStar::Pair dest = std::make_pair(99, 99);
    groupFormations.SetThreadPerGroup(true);

    groupFormations.FixedGroupFixedLeader(map100x100v, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}

TEST(Threading, FixedGroupSize5PhysicalLeaderAgents5_128x128Maze)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();

    GroupFormations groupFormations;
    std::vector<AStar::Pair> agents;
    int groupSize = 1;
    agents.push_back(std::make_pair(0, 1));
    agents.push_back(std::make_pair(10, 1));
    agents.push_back(std::make_pair(20, 1));
    agents.push_back(std::make_pair(30, 1));
    agents.push_back(std::make_pair(40, 1));

    AStar::Pair dest = std::make_pair(127, 127);
    groupFormations.SetThreadPerGroup(true);

    MapSaving mapSaving;
    std::vector<std::vector<int>> map;
    mapSaving.LoadMapFromJson(map, "128x128_maze");

    groupFormations.FixedGroupFixedLeader(map, agents, dest, true, groupSize);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    groupFormations.SaveMap();

    EXPECT_TRUE(false) << output;
}
