#ifndef LAB12_QUEUE_H
#define LAB12_QUEUE_H

#include <iostream>
#include <vector>
#include <optional>

#include "../graph/Node.h"

enum class QueueOutputFormat {
    Queue,
    Result
};

class Queue {
private:
    std::vector<Node> nodes;

public:
    Queue();
    size_t queueLength() const;

    void putNode(const Node& node);
    std::optional<Node> getNode();
    std::optional<Node> topNode();

    void show_queue(QueueOutputFormat format);
};

#endif //LAB12_QUEUE_H
