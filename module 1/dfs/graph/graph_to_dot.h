#ifndef LAB11_GRAPH_TO_DOT_H
#define LAB11_GRAPH_TO_DOT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "Edge.h"

void write_graph_to_dot(const std::vector<Edge>& edges, const std::string& filename, int startNode, int finishNode);
void graph_to_dot_result(const std::vector<Edge>& edges, const std::string& filename, int startNode, int finishNode, const std::vector<Node>& nodesWay);

#endif //LAB11_GRAPH_TO_DOT_H
