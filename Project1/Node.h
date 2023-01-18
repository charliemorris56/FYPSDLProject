#pragma once
#include <vector>

class Node
{
public:
    Node(const int x = 0, const int y = 0, const double costIn = 0,
        const double h_cost = 0, const int idIn = 0, const int pid = 0) :
        row(x), col(y), cost(costIn), heuristicCost(h_cost), id(idIn), parentId(pid) {}

    int row;
    int col;
    double cost;
    double heuristicCost;
    int id;
    int parentId;

    Node operator+(const Node& p) const;
    Node operator-(const Node& p) const;
    bool operator==(const Node& p) const;
    void PrintStatus() const;

    static bool CompareCoordinates(const Node& p1, const Node& p2) { return p1.row == p2.row && p1.col == p2.col; };

    static std::vector<Node> GetMotion() {
        return {
          Node(0, 1, 1, 0, 0, 0),
          Node(1, 0, 1, 0, 0, 0),
          Node(0, -1, 1, 0, 0, 0),
          Node(-1, 0, 1, 0, 0, 0)
          // Node(1, 1, sqrt(2), 0, 0, 0),
          // Node(1, -1, sqrt(2), 0, 0, 0),
          // Node(-1, 1, sqrt(2), 0, 0, 0),
          // Node(-1, -1, sqrt(2), 0, 0, 0)
        };
    };

    static bool checkOutsideBoundary(const Node& node, const int n) {
        return (node.row < 0 || node.col < 0
            || node.row >= n || node.col >= n);
    }
};

