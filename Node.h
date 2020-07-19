#ifndef MAZE_NODE_H
#define MAZE_NODE_H


class Node {
public:
    int x;
    int y;
    int fScore;

    bool southWall;
    bool eastWall;

    Node* parent;

    Node(int col, int row);
};


#endif //MAZE_NODE_H
