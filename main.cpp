#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "Node.h"


int main() {
    int width, height;
    std::cout << "How wide is the maze? " << std::flush;
    std::cin >> width;
    std::cout << "How tall is the maze? " << std::flush;
    std::cin >> height;

    std::vector<std::vector<Node>> nodeGrid(width * height);
    std::vector<std::vector<Node*>> edges;
    std::vector<std::vector<Node*>> usedEdges;
    std::vector<std::vector<Node*>> forest;

    //initialize grid
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            nodeGrid[row].push_back(Node(col, row));
        }
    }

    //initialize vector of edges as pointer pairs and forest as pointer vectors
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            forest.push_back({&nodeGrid[row][col]});

            if (nodeGrid[row][col].x < width - 1) {
                edges.push_back({&nodeGrid[row][col], &nodeGrid[row][col + 1]});
            }

            if (nodeGrid[row][col].y < height - 1) {
                edges.push_back({&nodeGrid[row][col], &nodeGrid[row + 1][col]});
            }
        }
    }

    //create number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    //algorithm loop
    while (forest.size() > 1) {
        std::uniform_int_distribution<int> distribution(0, edges.size() - 1);
        int index = distribution(generator);
        auto edge = edges[index];
        int tree1, tree2;
        for (int i = 0; i < forest.size(); i++) {
            if (std::find(forest[i].begin(), forest[i].end(), edge[0]) != forest[i].end()) {
                tree1 = i;
            }

            if (std::find(forest[i].begin(), forest[i].end(), edge[1]) != forest[i].end()) {
                tree2 = i;
            }
        }

        if (tree1 == tree2) {
            edges.erase(edges.begin() + index);
        } else {
            for (auto node : forest[tree2]) {
                forest[tree1].push_back(node);
            }
            forest.erase(forest.begin() + tree2);
            usedEdges.push_back(edge);
        }
    }

}