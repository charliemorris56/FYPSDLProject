#pragma once
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include "Node.h"

struct compare_cost
{
    bool operator()(const Node& p1, const Node& p2) const;
};

class JumpPointSearch
{
public:
    JumpPointSearch(const std::vector<std::vector<int>>& grid);

    std::tuple<bool, std::vector<Node>> Plan(const Node& start, const Node& goal);

    bool HasForcedNeighbours(const Node& new_point, const Node& next_point, const Node& motion) const;

    Node Jump(const Node& new_point, const Node& motion, const int id);

private:
    std::priority_queue<Node, std::vector<Node>, compare_cost> open_list_;
    std::vector<Node> closed_list_;
    std::unordered_set<int> pruned;
    Node start_, goal_;

    std::vector<std::vector<int>> grid_ = {};
    std::vector<std::vector<int>> original_grid_;
    int n_;
};
