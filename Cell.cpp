#include "Cell.h"


Cell::Cell() {
    this->visited = false;
    this->northWall = true;
    this->southWall = true;
    this->eastWall = true;
    this->westWall = true;
    this->x = 0;
    this->y = 0;
}

