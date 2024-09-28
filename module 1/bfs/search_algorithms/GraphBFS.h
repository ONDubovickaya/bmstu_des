#ifndef LAB12_GRAPHBFS_H
#define LAB12_GRAPHBFS_H

#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "../graph/Node.h"
#include "../graph/Edge.h"
#include "../data_structures/Queue.h"

class GraphBFS {
private:
    std::vector<Edge> edgeList;
    Queue openedNodes;
    std::vector<Node> closedNodes;
    int goal;
    bool solutionFound;
    bool solutionNotFound;
    int childNodesCounter;
    std::unordered_map<int, int> resultPath;

    void child_nodes();
    std::vector<int> get_result_path(int start);

public:
    explicit GraphBFS(const std::vector<Edge> &edgeList);
    std::vector<int> realise_BFS(int start, int end);
    void show_result(const std::vector<int>& res);
};

#endif //LAB12_GRAPHBFS_H
