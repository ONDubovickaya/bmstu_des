#include "GraphBFS.h"

GraphBFS::GraphBFS(const std::vector<Edge> &edgeList) : edgeList(edgeList), goal(-1), solutionFound(true), solutionNotFound(true), childNodesCounter(0) {}

void GraphBFS::child_nodes() {
    childNodesCounter = 0;
    auto toppedNode = openedNodes.topNode();

    if (toppedNode) {
        auto currentNode = toppedNode.value();
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "Current node: Node" << std::to_string(currentNode.getNumber()) << "\n" << std::endl;

        if (openedNodes.queueLength() > 0) {
            std::cout << "Current queue (OPENED NODES): " << std::endl;
            openedNodes.show_queue(QueueOutputFormat::Queue);
        } else if (openedNodes.queueLength() == 0) {
            std::cout << "Current queue (OPENED NODES) is empty" << std::endl;
        }

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
                    openedNodes.putNode(edge.getEndNode());
                    resultPath[edge.getEndNode().getNumber()] = edge.getStartNode().getNumber();
                    childNodesCounter++;
                    std::cout << "[NOTE] Reached the goal -- Node" << std::to_string(edge.getEndNode().getNumber()) << "\n" << std::endl;
                    break;

                } else if (std::find_if(closedNodes.begin(), closedNodes.end(), [&edge](const auto &node) { return node.getNumber() == edge.getEndNode().getNumber(); }) == closedNodes.end()) {
                    edge.markAsUsed();
                    openedNodes.putNode(edge.getEndNode());
                    resultPath[edge.getEndNode().getNumber()] = edge.getStartNode().getNumber();
                    childNodesCounter++;
                    std::cout << "[NOTE] Found a child -- Node" << std::to_string(edge.getEndNode().getNumber()) << std::endl;
                    std::cout << "Current num of children: " << childNodesCounter << "\n" << std::endl;
                }
            }

            std::ostringstream outputIssues;
            outputIssues << "This edge doesn't fit, because:" << std::endl;

            bool hasIssues = false;

            if (edge.getStartNode().getNumber() != currentNode.getNumber()) {
                outputIssues << "* Start node ISN'T the SAME as a current" << std::endl;
                hasIssues = true;
            }

            if (hasIssues) {
                std::cout << outputIssues.str() << std::endl;
            }
        }

    } else {
        std::cerr << "\n[WARNING] Queue is empty!" << std::endl;
        return;
    }
}

std::vector<int> GraphBFS::realise_BFS(int start, int end) {
    openedNodes.putNode(Node(start));
    goal = end;

    std::cout << "Finding OPTIMAL way from " << std::to_string(start) << " to " << std::to_string(end) << "..." << std::endl;
    std::cout << "Node" << std::to_string(start) << " added to current queue (OPENED NODES)\n" << std::endl;

    while (solutionFound && solutionNotFound) {
        child_nodes();

        auto gettedNode = openedNodes.getNode();

        if (gettedNode) {
            auto currentNode = gettedNode.value();

            if (childNodesCounter > 0) {
                closedNodes.push_back(currentNode);
                currentNode.setClosureFlag(1);
                std::cout << "[NOTE] Added Node" << std::to_string(currentNode.getNumber()) << " to CLOSED NODES\n" << std::endl;

                if (openedNodes.queueLength() > 0) {
                    std::cout << "Current queue (OPENED NODES): " << std::endl;
                    openedNodes.show_queue(QueueOutputFormat::Queue);
                } else if (openedNodes.queueLength() == 0) {
                    std::cout << "Current queue (OPENED NODES) is empty" << std::endl;
                }

                std::ostringstream closedNodesNums;
                for (size_t i = 0; i < closedNodes.size(); i++) {
                    closedNodesNums << "Node" + std::to_string(closedNodes[i].getNumber());

                    if (i != closedNodes.size() - 1) {
                        closedNodesNums << ", ";
                    }
                }

                std::cout <<  "In CLOSED NODES: " << closedNodesNums.str() << "\n" << std::endl;
            }

            if (!solutionNotFound) {
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "[ANSWER] Solution was found -- check CLOSED NODES" << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
                break;

            } else if (childNodesCounter == 0 && openedNodes.queueLength() == 0) {
                solutionFound = false;
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "[ANSWER] Solution wasn't found..." << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
                return std::vector<int>();
            }
          
        } else {
            std::cerr << "[WARNING] Queue is empty!" << std::endl;
            return std::vector<int>();
        }
    }
    return get_result_path(start);
}

std::vector<int> GraphBFS::get_result_path(int start) {
    int currentNode = goal;
    std::vector<int> result;
    result.push_back(currentNode);

    while (currentNode != start) {
        currentNode = resultPath[currentNode];
        result.push_back(currentNode);
    }

    return result;
}

void GraphBFS::show_result(const std::vector<int> &res) {
    for (int i = res.size() - 1; i >= 0; --i) {
        std::cout << "Node" << res[i];

        if (i != 0) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}
