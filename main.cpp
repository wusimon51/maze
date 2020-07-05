#include <iostream>
#include <stack>

#include "Cell.h"


void addPath(Cell* &cellPtr) {

}

int main() {
    Cell cellGrid[10][10];
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            cellGrid[row][col].x = col;
            cellGrid[row][col].y = row;
        }
    }

    std::stack<Cell*> cellPtrStack;
    cellPtrStack.push(&cellGrid[0][0]); //starter cell

    while (!cellPtrStack.empty()) {
        addPath(cellPtrStack.top());
        cellPtrStack.pop();
    }
}