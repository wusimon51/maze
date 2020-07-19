#include "Node.h"


Node::Node(int col, int row) {
    this->x = col;
    this->y = row;
    this->southWall = true;
    this->eastWall = true;
    this->fScore = 0;
    this->parent = this;
}