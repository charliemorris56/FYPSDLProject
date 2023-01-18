#include "JumpPointSearch.h"

JumpPointSearch::JumpPointSearch(const std::vector<std::vector<int>>& grid)
{
    original_grid_ = grid;
    n_ = original_grid_.size();
}

//Node JumpPointSearch::Jump(const Node& new_point, const Node& motion, const int id) {
//    Node next_point = new_point + motion;
//    next_point.id = n_ * next_point.row + next_point.col;
//    next_point.parentId = id;
//    next_point.heuristicCost =
//        std::abs(next_point.row - goal_.row) + std::abs(next_point.col - goal_.col);
//    if (next_point.row < 0 || next_point.col < 0 || next_point.row >= n_ ||
//        next_point.col >= n_ || grid_[next_point.row][next_point.col] != 0) {
//        // return new_point;
//        return Node(-1, -1, -1, -1, -1, -1);
//    }
//    if (pruned.find(next_point.id) != pruned.end()) {
//        pruned.insert(next_point.id);
//    }
//    if (Node::CompareCoordinates(next_point, goal_)) {
//        return next_point;
//    }
//    bool fn = false;
//    fn = HasForcedNeighbours(new_point, next_point, motion);
//    if (fn) {
//        // std::cout << "Forced neighbours found"<<'\n';
//        return next_point;
//    }
//    Node jump_node = Jump(next_point, motion, id);
//    // Prevent over shoot
//    if (jump_node.cost != -1 && jump_node.cost + jump_node.heuristicCost <=
//        next_point.cost + next_point.heuristicCost) {
//        return jump_node;
//    }
//    return next_point;
//}

bool JumpPointSearch::HasForcedNeighbours(const Node& new_point,  const Node& next_point, const Node& motion) const 
{
    int cn1x = new_point.row + motion.col;
    int cn1y = new_point.col + motion.row;

    int cn2x = new_point.row - motion.col;
    int cn2y = new_point.col - motion.row;

    int nn1x = next_point.row + motion.col;
    int nn1y = next_point.col + motion.row;

    int nn2x = next_point.row - motion.col;
    int nn2y = next_point.col - motion.row;

    bool a = !(cn1x < 0 || cn1y < 0 || cn1x >= n_ || cn1y >= n_ ||
        grid_[cn1x][cn1y] == 1);
    bool b = !(nn1x < 0 || nn1y < 0 || nn1x >= n_ || nn1y >= n_ ||
        grid_[nn1x][nn1y] == 1);
    if (a != b) {
        return true;
    }

    a = !(cn2x < 0 || cn2y < 0 || cn2x >= n_ || cn2y >= n_ ||
        grid_[cn2x][cn2y] == 1);
    b = !(nn2x < 0 || nn2y < 0 || nn2x >= n_ || nn2y >= n_ ||
        grid_[nn2x][nn2y] == 1);
    return a != b;
}
//
//std::tuple<bool, std::vector<Node>> JumpPointSearch::Plan(const Node& start, const Node& goal) 
//{
//    grid_ = original_grid_;
//    start_ = start;
//    goal_ = goal;
//    // Get possible motions
//    std::vector<Node> motion = Node::GetMotion();
//    open_list_.push(start_);
//
//    // Main loop
//    while (!open_list_.empty()) {
//        Node current = open_list_.top();
//        open_list_.pop();
//        current.id = current.row * n_ + current.col;
//        if (Node::CompareCoordinates(current, goal_)) {
//            closed_list_.push_back(current);
//            grid_[current.row][current.col] = 2;
//            return { true, closed_list_ };
//        }
//        grid_[current.row][current.col] = 2;  // Point opened
//        for (const auto& m :
//            motion) {  // auto it = motion.begin(); it!=motion.end(); ++it){
//            Node new_point;
//            new_point = current + m;
//            new_point.id = n_ * new_point.row + new_point.col;
//            new_point.parentId = current.id;
//            new_point.heuristicCost =
//                abs(new_point.row - goal_.row) + abs(new_point.col - goal_.col);
//            if (Node::CompareCoordinates(new_point, goal_)) {
//                open_list_.push(new_point);
//                break;
//            }
//            if (Node::checkOutsideBoundary(new_point, n_)) {
//                continue;  // Check boundaries
//            }
//            if (grid_[new_point.row][new_point.col] != 0) {
//                continue;  // obstacle or visited
//            }
//
//            Node jump_point = Jump(new_point, m, current.id);
//            if (jump_point.id != -1) {
//                open_list_.push(jump_point);
//                if (Node::CompareCoordinates(jump_point, goal_)) {
//                    closed_list_.push_back(current);
//                    closed_list_.push_back(jump_point);
//                    grid_[jump_point.row][jump_point.col] = 2;
//                    return { true, closed_list_ };
//                }
//            }
//            open_list_.push(new_point);
//        }
//        closed_list_.push_back(current);
//    }
//    return { false, {} };
//}