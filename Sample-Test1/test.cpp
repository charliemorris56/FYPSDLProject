#include "pch.h"
#include "TileMap.h"
#include "TileMap.cpp"
#include "AStar.h"
#include "AStar.cpp"
#include "JsonLoading.h"
#include "JumpPointSearch.h"
#include "JumpPointSearch.cpp"
#include "j1PathFinding.h"
#include "j1PathFinding.cpp"
#include "JumpPointSearchMe.h"
#include "JumpPointSearchMe.cpp"
#include "Map.h"

TEST(AStar, OneAgent10x10Diagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10, src, dest, true);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent10x10NoDiagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10, src, dest, false);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent100x100Diagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(99, 99);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map100x100, src, dest, true);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10NoDiagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map10x10, src, dest, false);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100Diagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map100x100, src, dest, true);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100NoDiagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map100x100, src, dest, false);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10Diagonal)
{
    clock_t t = clock();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map10x10, src, dest, true);

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime Taken: " << work_time;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

    EXPECT_TRUE(false) << output;
}
