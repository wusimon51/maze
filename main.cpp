#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <stack>

#include "Node.h"


void generateMaze(int &width, int &height, std::vector<std::vector<Node>> &nodeGrid) {
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

    //maze printing
    for (auto edge : usedEdges) {
        if (edge[0]->x == edge[1]->x) {
            if (edge[0]->y > edge[1]->y) {
                edge[1]->southWall = false;
            } else {
                edge[0]->southWall = false;
            }
        } else {
            if (edge[0]->x > edge[1]->x) {
                edge[1]->eastWall = false;
            } else {
                edge[0]->eastWall = false;
            }
        }
    }

    std::string roof = " ";
    for (int i = 0; i < width * 2 - 1; i++) {
        roof += "_";
    }
    std::cout << roof << std::endl;

    std::string rowString;
    for (int row = 0; row < height; row++) {
        rowString += "|";
        for (int col = 0; col < width; col++) {
            if (nodeGrid[row][col].southWall) {
                rowString += "_";
            } else rowString += " ";

            if (nodeGrid[row][col].eastWall) {
                rowString += "|";
            } else {
                if (nodeGrid[row][col].southWall && nodeGrid[row][col + 1].southWall) {
                    rowString += "_";
                } else rowString += " ";
            }
        }

        std::cout << rowString << std::endl;
        rowString = "";
    }
}

int main() {
    int width, height;
    std::cout << "How wide is the maze? " << std::flush;
    std::cin >> width;
    std::cout << "How tall is the maze? " << std::flush;
    std::cin >> height;

    std::vector<std::vector<Node>> nodeGrid(width * height);
    generateMaze(width, height, nodeGrid);

    std::stack<Node*> stack;
}