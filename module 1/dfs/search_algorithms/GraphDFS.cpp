#include "GraphDFS.h"

GraphDFS::GraphDFS(const std::vector<Edge> &edgeList) : edgeList(edgeList), goal(-1), solutionFound(true), solutionNotFound(true), childNodesCounter(0) {}

void GraphDFS::child_nodes() {
    childNodesCounter = 0;
    auto peekedNode = openedNodes.peekNode();

    if(peekedNode) {
        auto currentNode = peekedNode.value();
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "Current node: Node" << std::to_string(currentNode.getNumber()) << "\n" << std::endl;

        if (currentNode.getNumber() == goal) {
            std::cout << "START and END nodes are the SAME" << std::endl;
            std::cout << "[NOTE] Reached the goal -- Node" << currentNode.getNumber() << "\n" << std::endl;
            solutionNotFound = false;
            return;
        }

        for (auto &edge : edgeList) {
            std::string currentEdge = edge.show_edge();
            std::cout << "> " + currentEdge << std::endl;

            if (edge.getStartNode().getNumber() == currentNode.getNumber() && !edge.getUsageMark()) {
                if (edge.getEndNode().getNumber() == goal) {
                    solutionNotFound = false;
                    edge.markAsUsed();
                    openedNodes.pushNode(edge.getEndNode());
                    childNodesCounter++;
                    std::cout << "[NOTE] Reached the goal -- Node" << std::to_string(edge.getEndNode().getNumber()) << "\n" << std::endl;

                    if (openedNodes.stackLength() > 0) {
                        std::cout << "Current stack (OPENED NODES): " << std::endl;
                        openedNodes.show_stack(StackOutputFormat::Stack);
                    } else if (openedNodes.stackLength() == 0) {
                        std::cout << "Current stack (OPENED NODES) is empty" << std::endl;
                    }
                    break;

                } else if (std::find_if(closedNodes.begin(), closedNodes.end(), [&edge](const auto &node) { return node.getNumber() == edge.getEndNode().getNumber(); }) == closedNodes.end()) {
                    edge.markAsUsed();
                    openedNodes.pushNode(edge.getEndNode());
                    childNodesCounter++;
                    std::cout << "[NOTE] Found a child -- Node" << std::to_string(edge.getEndNode().getNumber()) << "\n" << std::endl;

                    if (openedNodes.stackLength() > 0) {
                        std::cout << "Current stack (OPENED NODES): " << std::endl;
                        openedNodes.show_stack(StackOutputFormat::Stack);
                    } else if (openedNodes.stackLength() == 0) {
                        std::cout << "Current stack (OPENED NODES) is empty" << std::endl;
                    }
                    break;
                }
            }

            std::ostringstream outputIssues;
            outputIssues << "This edge doesn't fit, because:" << std::endl;

            bool hasIssues = false;

            if (edge.getStartNode().getNumber() != currentNode.getNumber()) {
                outputIssues << "* Start node ISN'T the SAME as a current" << std::endl;
                hasIssues = true;
            }

            if (edge.getStartNode().getNumber() == currentNode.getNumber() && edge.getUsageMark()) {
                outputIssues << "* Edge is marked as USED" << std::endl;
                hasIssues = true;
            }

            if (hasIssues) {
                std::cout << outputIssues.str() << std::endl;
            }
        }

    } else {
        std::cerr << "\n[WARNING] Stack is empty!" << std::endl;
        return;
    }
}

Stack GraphDFS::realise_DFS(int start, int end) {
    openedNodes.pushNode(Node(start));
    goal = end;

    std::cout << "Finding way from " << std::to_string(start) << " to " << std::to_string(end) << "..." << std::endl;
    std::cout << "Node" << std::to_string(start) << " added to current stack (OPENED NODES)\n" << std::endl;

    while (solutionFound && solutionNotFound) {
        child_nodes();

        if (!solutionNotFound) {
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "[ANSWER] Solution was found -- check your stack" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
            break;
        } else if (childNodesCounter == 0 && openedNodes.stackLength() > 0) {
            auto poppedNode = openedNodes.popNode();

            if (poppedNode) {
                auto currentNode = poppedNode.value();
                currentNode.setClosureFlag(1);
                closedNodes.push_back(currentNode);
                std::cout << "[NOTE] Added Node" << std::to_string(currentNode.getNumber()) << " (marked as PASSED, flag=" << std::to_string(currentNode.getClosureFlag()) << ") to CLOSED NODES\n" << std::endl;

                if (openedNodes.stackLength() > 0) {
                    std::cout << "Current stack (OPENED NODES): " << std::endl;
                    openedNodes.show_stack(StackOutputFormat::Stack);
                } else if (openedNodes.stackLength() == 0) {
                    std::cout << "Current stack (OPENED NODES) is empty" << std::endl;
                }

                std::ostringstream closedNodesNums;
                for (size_t i = 0; i < closedNodes.size(); i++) {
                    closedNodesNums << "Node" + std::to_string(closedNodes[i].getNumber());

                    if (i != closedNodes.size() - 1) {
                        closedNodesNums << ", ";
                    }
                }

                std::cout << "In CLOSED NODES: " << closedNodesNums.str() << "\n" << std::endl;

            } else {
                std::cerr << "[WARNING] Stack is empty!" << std::endl;
                return Stack();
            }

        } else if (childNodesCounter == 0 && openedNodes.stackLength() == 0) {
            solutionFound = false;
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "[ANSWER] Solution wasn't found... " << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
            return Stack();
        }
    }
    return openedNodes;
}
