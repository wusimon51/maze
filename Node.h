#ifndef MAZE_NODE_H
#define MAZE_NODE_H


class Node {
public:
    int x;
    int y;

    bool southWall;
    bool eastWall;

    Node(int col, int row);
};


#endif //MAZE_NODE_H
