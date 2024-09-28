#ifndef LAB11_GRAPHDFS_H
#define LAB11_GRAPHDFS_H

#include <algorithm>
#include <sstream>

#include "../graph/Node.h"
#include "../graph/Edge.h"
#include "../data_structures/Stack.h"

class GraphDFS {
private:
    std::vector<Edge> edgeList;
    Stack openedNodes;
    std::vector<Node> closedNodes;
    int goal;
    bool solutionFound;
    bool solutionNotFound;
    int childNodesCounter;

    void child_nodes();

public:
    explicit GraphDFS(const std::vector<Edge> &edgeList);
    Stack realise_DFS(int start, int end);
};

#endif //LAB11_GRAPHDFS_H
