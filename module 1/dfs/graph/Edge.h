#ifndef LAB11_EDGE_H
#define LAB11_EDGE_H

#include "Node.h"

class Edge {
private:
    Node startNode;
    Node endNode;
    std::string ruleNumber;
    bool usageMark;

public:
    Edge(Node startNode, Node endNode, const std::string& ruleNumber);

    [[nodiscard]] Node getStartNode() const;
    [[nodiscard]] Node getEndNode() const;
    std::string getRuleNumber() const;
    [[nodiscard]] bool getUsageMark() const;

    void markAsUsed();

    std::string show_edge() const;
};

#endif //LAB11_EDGE_H
