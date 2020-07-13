#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <string>


template <class generic>
auto find (std::vector<generic>& vec, generic val) { //added macro for find
    return std::find(vec.begin(), vec.end(), val);
}

void get_trees(int cell1, int cell2, int* cell1_tree, int* cell2_tree, std::vector<std::vector<int>>& forest) {
    for (int i = 0; i < forest.size(); i++) { //iterate through every vector<int> tree in forest
        auto end = forest[i].end(); //end is the last element of the tree at the index
        if (find(forest[i], cell1) != end) { //if the location of cell1 in the tree is not the end, meaning it was not found
            *cell1_tree = i; //the pointer to the cell tree becomes the index
        }
        if (find(forest[i], cell2) != end) { //if the location of cell2 in the tree is not the end, meaning it was not found
            *cell2_tree = i; //the pointer to the cell tree becomes the index
        }
    }
}

void merge_trees(int index1, int index2, std::vector<std::vector<int>>& forest) {
    for (int i : forest[index2]) { //iterate through every int in the index2 tree of the forest
        forest[index1].push_back(i); //put the int value in the index1 tree of the forest
    }
    forest.erase(forest.begin() + index2); //erase the index2 tree in the forest
}

bool check (int cell1, int cell2, std::vector<std::vector<int>>& forest) {
    int cell1_tree = -1, cell2_tree = -2; //assign values for the trees, subject to change
    get_trees(cell1, cell2, &cell1_tree, &cell2_tree, forest); //iterate through every tree in forest, assign index to cell tree variables
    if (cell1_tree != -1) { //if cell1_tree changes to actual index in forest
        if (cell2_tree == -2) { //if cell2_tree remains the same
            forest[cell1_tree].push_back(cell2); //place cell2 in cell1_tree
        } else if (cell1_tree != cell2_tree) { //else if both trees exist and are not the same
            merge_trees(cell1_tree, cell2_tree, forest); //merge cell2_tree into cell1_tree
        }
    } else if (cell2_tree != -2) { //else if cell2_tree changes to existing tree index in forest, so cell1_tree does not exist
        forest[cell2_tree].push_back(cell1); //place cell1 in cell2_tree
    } else {
        std::vector<int> new_tree = {cell1, cell2}; //create new tree containing cell1 and cell2
        forest.push_back(new_tree); //add new tree to forest
    }
    return cell1_tree != cell2_tree; //return whether the trees are the same
}

int main() {
    int height, width;
    std::cout << "Enter a height: ";
    std::cin >> height;
    if (height < 1) {
        std::cout << "Invalid value.";
        abort();
    }
    std::cout << "Enter a width: ";
    std::cin >> width;
    if (width < 1) {
        std::cout << "Invalid value.";
        abort();
    }
    std::cout << "Generating a " << height << " by " << width << " maze" << std::endl;

    const int area = height * width; //number of nodes in the maze
    const int h_offset = height * (width - 1); //area - height, is vertical bound of maze, also number of vertical edges
    std::vector<std::vector<int>> mst; //vector of vectors of ints called minimum spanning tree
    std::vector<int> destroyed_walls; //vector of ints
    std::vector<int> walls(2 * area - height - width); //vector of ints allocated to total number of beginning walls
    std::iota(walls.begin(), walls.end(), 0); //fill walls vector with increasing values from 0 up to the last value

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); //rng seed
    std::default_random_engine engine(seed); //initialize rng engine with seed
    while(destroyed_walls.size() < height * width - 1) { //while the number of destroyed walls is less than the number of edges in the mst, also # nodes - 1 edges in a tree
        std::uniform_int_distribution<int> distribution(0, walls.size()-1); //generator for 0 to last value of walls, also the index
        int index = distribution(engine); //assign random number from distribution to index
        int wall = walls[index]; //select random wall from index
        if (wall < h_offset) { //if wall is within bounds of the maze
            int left = wall + wall / (width - 1); //left is wall to the left of horizontal edge
            if (check(left, left + 1, mst)) { //join trees if they are not part of the same tree, if not return false
                destroyed_walls.push_back(wall); //add wall to destroyed walls
            }
        } else {
            int above = wall - h_offset; //vertical wall
            if (check(above, above + width, mst)) { //join trees if they are not part of the same tree, if not return false
                destroyed_walls.push_back(wall); //add wall to destroyed walls
            }
        }
        walls.erase(walls.begin() + index); //remove the destroyed wall
    }

    std::vector<std::string> maze;

    std::string horizontals;
    for (int i = 0; i < width; i++) {
        horizontals += "+---";
    }
    horizontals += "+\n";

    std::string verticals;
    for (int i = 0; i < width; i++) {
        verticals += "|   ";
    }
    verticals += "|\n";

    for (int i = 0; i < 2 * height + 1; i++) {
        if (i % 2 == 0) {
            maze.push_back(horizontals);
        } else {
            maze.push_back(verticals);
        }
    }

    for (int wall : destroyed_walls) {
        if (wall < h_offset) {
            int start = 4 + wall % (width - 1) * 4;
            maze[wall / (width - 1) * 2 + 1].replace(start, 1, " ");
        } else {
            int start = 1 + (wall - h_offset) % width * 4;
            maze[(wall - h_offset) / width * 2 + 2].replace(start, 3, "   ");
        }
    }

    maze[1].replace(0, 1, " ");
    maze[2 * height - 1].replace(4 * width, 1, " ");

    for (auto& row : maze) {
        std::cout << row;
    }
}