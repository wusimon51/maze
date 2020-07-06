#ifndef MAZE_CELL_H
#define MAZE_CELL_H


class Cell {
public:
    Cell();

    bool visited;
    bool northWall;
    bool southWall;
    bool eastWall;
    bool westWall;

    int x;
    int y;
};


#endif //MAZE_CELL_H
