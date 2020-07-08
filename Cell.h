#ifndef MAZE_CELL_H
#define MAZE_CELL_H


#include <stack>
#include <random>


class Cell {
public:
    bool visited;
    bool northWall;
    bool southWall;
    bool eastWall;
    bool westWall;

    int x;
    int y;

    Cell();
    void addPath(Cell arr[][10], std::stack<Cell*> &stackRef, std::default_random_engine &engine);
    void printMaze(Cell arr[][10]);
    void run();
};


#endif //MAZE_CELL_H
