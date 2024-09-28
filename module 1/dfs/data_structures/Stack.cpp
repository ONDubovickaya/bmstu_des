#include "Stack.h"

Stack::Stack() {}

// кол-во эл-тов в стеке
size_t Stack::stackLength() const {
    return nodes.size();
}

// добавление нового эл-та на вершину стека
void Stack::pushNode(const Node &node) {
    // добавление эл-та конец nodes (вершина стека)
    nodes.push_back(node);
}

// извлечение эл-та из вершины стека
// (С его последующим УДАЛЕНИЕМ из стека)
std::optional<Node> Stack::popNode() {
    if (stackLength() == 0) {
        return std::nullopt;
    }
    // получаем последний эл-т вектора nodes (вершина стека)
    // чтобы потом его вернуть
    Node node = nodes.back();
    // удаляем последний эл-т из вектора nodes (вершину стека)
    // pop_back() ничего не возвращает -- просто удаляет эл-т
    nodes.pop_back();
    return node;
}

// извлечение эл-та из вершины стека
// (БЕЗ его последующего УДАЛЕНИЯ из стека)
std::optional<Node> Stack::peekNode() {
    if (stackLength() == 0) {
        return std::nullopt;
    }
    // возвращаем последний эл-т вектора nodes (вершина стека)
    return nodes.back();
}

// вывод эл-тов стека на экран
void Stack::show_stack(StackOutputFormat format) {
    // создаём временный стек
    Stack tempStack;

    while (stackLength() > 0) {
        // извлекаем эл-т из вершины основного стека (с удалением)
        auto poppedNode = popNode();

        if (poppedNode) {
            // добавляем полученный эл-т во временный стек (если основной стек был не пуст)
            // во временном стеке эл-ты основного хранятся в обратном порядке
            tempStack.pushNode(poppedNode.value());
        } else {
            std::cerr << "\n[WARNING] Stack is empty!" << std::endl;
            return;
        }
    }

    switch (format) {
        case StackOutputFormat::Stack:
            while (tempStack.stackLength() > 0) {
                // извлекаем эл-т из вершины временного стека (с удалением)
                auto node = tempStack.popNode();

                if (node) {
                    // добавляем извлечённый эл-т в основной стек, т.к. до этого мы удалили все эл-ты из него
                    // (это нужно, чтобы иметь возможность выводить стек на любом этапе программы, без потери его значений)
                    pushNode(node.value());

                    std::cout << node->to_represent();

                    if (tempStack.stackLength() > 0) {
                        std::cout << " | ";
                    }

                } else {
                    std::cerr << "\n[WARNING] Stack is empty!" << std::endl;
                    return;
                }
            }

            if (stackLength() > 0) {
                std::cout << " [TOP]" << std::endl;
            }

            std::cout << std::endl;
            break;

        case StackOutputFormat::Result:
            while (tempStack.stackLength() > 0) {
                // извлекаем эл-т из вершины временного стека (с удалением)
                auto node = tempStack.popNode();

                if (node) {
                    // добавляем извлечённый эл-т в основной стек, т.к. до этого мы удалили все эл-ты из него
                    // (это нужно, чтобы иметь возможность выводить стек на любом этапе программы, без потери его значений)
                    pushNode(node.value());

                    std::cout << node->to_represent();

                    if (tempStack.stackLength() > 0) {
                        std::cout << " -> ";
                    }

                } else {
                    std::cerr << "\n[WARNING] Stack is empty!" << std::endl;
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

std::vector<Node> Stack::stack_to_vector() const {
    std::vector<Node> vect;

    const std::size_t numElements = nodes.size();
    vect.reserve(numElements);

    for (int i = 0; i < numElements; i++) {
        vect.push_back(nodes[i]);
    }

    return vect;
}
