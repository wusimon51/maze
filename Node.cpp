#include "Node.h"


Node::Node(int col, int row) {
    this->x = col;
    this->y = row;
    this->southWall = true;
    this->eastWall = true;
    this->path = false;
}