#ifndef LAB11_STACK_H
#define LAB11_STACK_H

#include <iostream>
#include <vector>
#include <optional>

#include "../graph/Node.h"

enum class StackOutputFormat {
    Stack,
    Result
};

class Stack {
private:
    std::vector<Node> nodes;

public:
    Stack();
    size_t stackLength() const;

    void pushNode(const Node& node);
    std::optional<Node> popNode();
    std::optional<Node> peekNode();

    void show_stack(StackOutputFormat format);
    std::vector<Node> stack_to_vector() const;
};

#endif //LAB11_STACK_H
