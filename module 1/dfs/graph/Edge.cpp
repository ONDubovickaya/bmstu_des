#include "Edge.h"

Edge::Edge(Node startNode, Node endNode, const std::string &ruleNumber) : startNode(startNode), endNode(endNode), ruleNumber(ruleNumber), usageMark(false) {}

Node Edge::getStartNode() const {
    return startNode;
}

Node Edge::getEndNode() const {
    return endNode;
}

std::string Edge::getRuleNumber() const {
    return ruleNumber;
}

bool Edge::getUsageMark() const {
    return usageMark;
}

void Edge::markAsUsed() {
    usageMark = true;
}

std::string Edge::show_edge() const {
    std::string markString = usageMark ? "[passed]" : "[opened]";
    return "Edge: " + std::to_string(startNode.getNumber()) + " --> " + std::to_string(endNode.getNumber()) + " " + markString;
}
