#ifndef LAB12_NODE_H
#define LAB12_NODE_H

#include <string>

class Node {
private:
    int number;
    int closureFlag;

public:
    explicit Node(int number);

    [[nodiscard]] int getNumber() const;
    [[nodiscard]] int getClosureFlag() const;

    void setClosureFlag(int value);

    std::string to_represent() const;
};


#endif //LAB12_NODE_H
