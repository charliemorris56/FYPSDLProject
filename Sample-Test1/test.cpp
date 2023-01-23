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
#include <chrono>

TEST(AStar, OneAgent10x10Diagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent10x10NoDiagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(8, 0);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map10x10, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

	EXPECT_TRUE(false) << output;
}

TEST(AStar, OneAgent100x100Diagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    AStar aStar;

    AStar::Pair src = std::make_pair(99, 99);
    AStar::Pair dest = std::make_pair(0, 0);
    aStar.AStarSearch(map100x100, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10NoDiagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map10x10, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100Diagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map100x100, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent100x100NoDiagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(99, 99);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map100x100, src, dest, false);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map100x100, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(JumpPointSearch, OneAgent10x10Diagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    JumpPointSearchMe jumpPointSearchMe;

    JumpPointSearchMe::Pair src = std::make_pair(8, 0);
    JumpPointSearchMe::Pair dest = std::make_pair(0, 0);
    jumpPointSearchMe.AStarSearch(map10x10, src, dest, true);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

    EXPECT_TRUE(false) << output;
}

TEST(HPAStar, OneAgent10x10Diagonal)
{
    auto start = std::chrono::steady_clock::now();
    testing::internal::CaptureStdout();
    HPAStar hPAStar;

    HPAStar::Pair src = std::make_pair(8, 0);
    HPAStar::Pair dest = std::make_pair(0, 0);
    hPAStar.Search(map10x10, src, dest, true, 5);

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    std::cout << "\nTime Taken: " << elapsed_seconds;

    std::string output = testing::internal::GetCapturedStdout();

    pch pchClass;
    pchClass.SaveMapToJson(map10x10, src, dest);

    EXPECT_TRUE(false) << output;
}
