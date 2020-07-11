#include <iostream>
#include <vector>
#include <set>

#include "Node.h"
#include "Tree.h"


int main() {
    int width;
    int height;
    std::cout << "How wide is the maze? " << std::flush;
    std::cin >> width;
    std::cout << "How tall is the maze? " << std::flush;
    std::cin >> height;

    std::vector<std::vector<Node>> nodeGrid(width * height);
    std::vector<std::vector<Node*>> edges(2 * width * height - width - height);
    std::vector<std::vector<Node*>> forest;

    //initialize node grid
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            nodeGrid[row].push_back(Node(col, row));
        }
    }

    //initialize edge and forest vectors
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            std::cout << &nodeGrid[row][col] << " " << nodeGrid[row][col].x << " " << nodeGrid[row][col].y << std::endl;
            std::vector<Node*> edgePair;

            if (col + 1 < width) {
                edgePair.push_back(&nodeGrid[row][col]);
                edgePair.push_back(&nodeGrid[row][col + 1]);
                edges.push_back(edgePair);
//                edgePair.clear();
            }

            if (row + 1 < height) {
                edgePair.push_back(&nodeGrid[row][col]);
                edgePair.push_back(&nodeGrid[row + 1][col]);
                edges.push_back(edgePair);
//                edgePair.clear();
            }

            edges.push_back(edgePair);
//            edgePair.clear();

            std::vector<Node*> tree;
            tree.push_back(&nodeGrid[row][col]);
            forest.push_back(tree);
            tree.clear();
        }
    }

    std::cout << edges.size() << std::endl;
    std::cout << forest.size() << std::endl;

    for (auto &edgePair : edges) {
        std::cout << edgePair[0] << " " << edgePair[1] << std::endl;
    }

    /* vector of nodes with x and y coordinates
    * vector of all edges, iterate through every node and push pairs with neighbors from east and south directions
    * vector of trees as vectors, push every node's address as its own vector
    * while size of edges vector > area - 1:
     * choose one random edge
     * iterate over tree vector for second node, if it is present in vector with second node:
     *     add to first node's vector
     *     erase second node's vector
     * else:
     *     erase vector
     * use remaining edges to create walls
     */
}