#include <iostream>
#include <vector>

#include "Node.h"


int main() {
    int width, height;
    std::cout << "How wide is the maze? " << std::flush;
    std::cin >> width;
    std::cout << "How tall is the maze? " << std::flush;
    std::cin >> height;

    std::vector<std::vector<Node>> nodeGrid;
    std::vector<std::vector<Node*>> edges;
    std::vector<std::vector<Node*>> usedEdges;

    //initialize grid
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            nodeGrid[row].push_back(Node(col, row));
        }
    }

    //initialize vector of edges as pointer pairs and forest
//    for (int row = 0; row < height; row++) {
//        for (int col = 0; col < width; col++) {
//            if (nodeGrid[row][col].x < width - 1) {
//                edges.push_back({&nodeGrid[row][col], &nodeGrid[row][col + 1]});
//            }
//
//            if (nodeGrid[row][col].y < height - 1) {
//                edges.push_back({&nodeGrid[row][col], &nodeGrid[row + 1][col]});
//            }
//        }
//    }

    std::cout << nodeGrid.size();
}