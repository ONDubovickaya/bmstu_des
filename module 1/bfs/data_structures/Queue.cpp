#include "Queue.h"

Queue::Queue() {}

// кол-во эл-тов в очереди
size_t Queue::queueLength() const {
    return nodes.size();
}

// добавление нового эл-та в хвост очереди
void Queue::putNode(const Node &node) {
    // добавление эл-та в конец nodes (хвост очереди)
    nodes.push_back(node);
}

// извлечение эл-та из головы очереди
// (С его последующим УДАЛЕНИЕМ из очереди)
std::optional<Node> Queue::getNode() {
    if (queueLength() == 0) {
        return std::nullopt;
    }
    // получаем первый эл-т вектора nodes (голова очереди)
    // чтобы потом его вернуть
    Node node = nodes.front();
    // удаляем первый эл-т из вектора nodes (головы очереди)
    nodes.erase(nodes.begin());
    return node;
}

// извлечение эл-та из головы очереди
// (БЕЗ его последующего УДАЛЕНИЯ из очереди)
std::optional<Node> Queue::topNode() {
    if (queueLength() == 0) {
        return std::nullopt;
    }
    // возвращаем первый эл-т вектора nodes (голова очереди)
    return nodes.front();
}

// вывод эл-тов очереди на экран
void Queue::show_queue(QueueOutputFormat format) {
    // создаём временную очередь
    Queue tempQueue;

    while (queueLength() > 0) {
        // извлекаем эл-т из головы основной очереди (с удалением)
        auto gettedNode = getNode();

        if (gettedNode) {
            // добавляем полученный эл-т во временную очередь (если основная очередь была не пуста)
            tempQueue.putNode(gettedNode.value());
        } else {
            std::cerr << "\n[WARNING] Queue is empty!" << std::endl;
            return;
        }
    }

    switch (format) {
        case QueueOutputFormat::Queue:
            if (tempQueue.queueLength() > 0) {
                std::cout << "[HEAD] ";
            }

            while (tempQueue.queueLength() > 0) {
                // извлекаем эл-т из головы временной очереди (с удалением)
                auto node = tempQueue.getNode();

                if (node) {
                    // добавляем извлечённый эл-т в хвост основной очереди
                    putNode(node.value());

                    std::cout << node->to_represent();

                    if (tempQueue.queueLength() > 0) {
                        std::cout << " | ";
                    }
                } else {
                    std::cerr << "\n[WARNING] Queue is empty!" << std::endl;
                    return;
                }
            }

            if (queueLength() > 0) {
                std::cout << " [TAIL]" << std::endl;
            }

            std::cout << std::endl;
            break;

        case QueueOutputFormat::Result:
            while (tempQueue.queueLength() > 0) {
                // извлекаем эл-т из головы временной очереди (с удалением)
                auto node = tempQueue.getNode();
            
                if (node) {
                    // добавляем извлечённый эл-т в хвост основной очереди
                    putNode(node.value());

                    std::cout << node->to_represent();

                    if (tempQueue.queueLength() > 0) {
                        std::cout << " <- ";
                    }
                } else {
                    std::cerr << "\n[WARNING] Queue is empty!" << std::endl;
                    return;
                }
            }

            std::cout << std::endl;
            break;

        default:
            std::cerr << "[ERROR] Unknown Output Format" << std::endl;
            break;
    }
}
