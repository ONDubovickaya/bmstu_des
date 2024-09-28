#include "Node.h"

Node::Node(int number) : number(number), closureFlag(0) {}

int Node::getNumber() const {
    return number;
}

int Node::getClosureFlag() const {
    return closureFlag;
}

void Node::setClosureFlag(int value) {
    closureFlag = value;
}

std::string Node::to_represent() const {
    return "Node" + std::to_string(number);
}
