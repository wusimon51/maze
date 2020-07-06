#include "Cell.h"

#include <iostream>
#include <stack>
#include <algorithm>
#include <chrono>
#include <random>
#include <array>


int width = 0;
int height = 0;

void addPath(Cell arr[][10], std::stack<Cell*> &stackRef, std::default_random_engine &engine) {
    Cell* currentCellPtr = stackRef.top();
    stackRef.pop();

    //shuffle array of cardinal directions
    std::array<char, 4> directions = {'N', 'S', 'E', 'W'};
    std::shuffle(directions.begin(), directions.end(), engine);

    //ask neighbors based on shuffled array
    for (int i = 0; i < 4; i++) {
        switch (directions[i]) {
            case 'N':
                if (currentCellPtr->y > 0) {
                    if (!arr[currentCellPtr->y - 1][currentCellPtr->x].visited) {
                        stackRef.push(currentCellPtr);
                        currentCellPtr->northWall = false;
                        arr[currentCellPtr->y - 1][currentCellPtr->x].southWall = false;
                        arr[currentCellPtr->y - 1][currentCellPtr->x].visited = true;
                        stackRef.push(&arr[currentCellPtr->y - 1][currentCellPtr->x]);

                        break;
                    }
                }

            case 'S':
                if (currentCellPtr->y < height - 1) {
                    if (!arr[currentCellPtr->y + 1][currentCellPtr->x].visited) {
                        stackRef.push(currentCellPtr);
                        currentCellPtr->southWall = false;
                        arr[currentCellPtr->y + 1][currentCellPtr->x].northWall = false;
                        arr[currentCellPtr->y + 1][currentCellPtr->x].visited = true;
                        stackRef.push(&arr[currentCellPtr->y + 1][currentCellPtr->x]);

                        break;
                    }
                }

            case 'E':
                if (currentCellPtr->x < width - 1) {
                    if (!arr[currentCellPtr->y][currentCellPtr->x + 1].visited) {
                        stackRef.push(currentCellPtr);
                        currentCellPtr->eastWall = false;
                        arr[currentCellPtr->y][currentCellPtr->x + 1].westWall = false;
                        arr[currentCellPtr->y][currentCellPtr->x + 1].visited = true;
                        stackRef.push(&arr[currentCellPtr->y][currentCellPtr->x + 1]);

                        break;
                    }
                }

            case 'W':
                if (currentCellPtr->x > 0) {
                    if (!arr[currentCellPtr->y][currentCellPtr->x - 1].visited) {
                        stackRef.push(currentCellPtr);
                        currentCellPtr->westWall = false;
                        arr[currentCellPtr->y][currentCellPtr->x - 1].eastWall = false;
                        arr[currentCellPtr->y][currentCellPtr->x - 1].visited = true;
                        stackRef.push(&arr[currentCellPtr->y][currentCellPtr->x - 1]);

                        break;
                    }
                }
        }
    }
}

void printMaze(Cell arr[][10]) {
    std::string roof = " ";
    for (int i = 0; i < width * 2 - 1; i++) {
        roof += "_";
    }
    std::cout << roof << std::endl;

    std::string rowString;
    for (int row = 0; row < height; row++) {
        rowString += "|";
        for (int col = 0; col < width; col++) {
            arr[row][col].southWall ? rowString += "_" : rowString += " ";
            if (arr[row][col].eastWall) {
                rowString += "|";
            } else {
                arr[row][col].southWall && arr[row][col + 1].southWall ? rowString += "_" : rowString += " ";
            }
        }

        std::cout << rowString << std::endl;
        rowString = "";
    }
}

int main() {
    std::cout << "How wide is the maze? " << std::flush;
    std::cin >> width;
    std::cout << "How tall is the maze? " << std::flush;
    std::cin >> height;

    //initialize containers
    Cell cellGrid[height][10];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            cellGrid[row][col].x = col;
            cellGrid[row][col].y = row;
        }
    }

    std::stack<Cell*> cellPtrStack;
    cellPtrStack.push(&cellGrid[0][0]); //starter cell
    cellGrid[0][0].visited = true;

    //initialize random number engine
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);

    //run backtracking algorithm
    while (!cellPtrStack.empty()) {
        addPath(cellGrid, cellPtrStack, engine);
    }

    printMaze(cellGrid);
}
