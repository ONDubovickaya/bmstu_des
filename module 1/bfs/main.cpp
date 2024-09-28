#include <iostream>

#include "search_algorithms/GraphBFS.h"
#include "graph/graph_to_dot.h"

int main() {
    // ПРИМЕР 1
    Node node0(0);
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);

    std::vector<Edge> edges = {
            Edge(node0, node1, "101"),
            Edge(node0, node3, "103"),
            Edge(node1, node2, "102"),
            Edge(node2, node4, "109"),
            Edge(node2, node6, "108"),
            Edge(node3, node4, "104"),
            Edge(node3, node5, "105"),
            Edge(node5, node4, "107"),
            Edge(node6, node5, "106")
    };

    // ПРИМЕР 2
    /*Node node0(0);
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);
    Node node7(7);
    Node node8(8);

    std::vector<Edge> edges = {
            Edge(node0, node1, "101"),
            Edge(node0, node2, "103"),
            Edge(node2, node4, "104"),
            Edge(node2, node5, "113"),
            Edge(node1, node3, "102"),
            Edge(node3, node4, "106"),
            Edge(node4, node5, "105"),
            Edge(node4, node8, "108"),
            Edge(node8, node3, "107"),
            Edge(node8, node7, "109"),
            Edge(node7, node6, "110"),
            Edge(node6, node4, "111"),
            Edge(node6, node5, "112")
    };
    */

    // ПРИМЕР 3
    /*Node node0(0);
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);

    std::vector<Edge> edges = {
            Edge(node0, node5, "101"),
            Edge(node1, node6, "102"),
            Edge(node2, node1, "103"),
            Edge(node3, node0, "104"),
            Edge(node4, node0, "105")
    };*/

    int startHere = 0, finishHere = 4;
    // write_graph_to_dot(edges, "graph1_schema.gv", startHere, finishHere);

    GraphBFS graphBFS(edges);
    std::vector<int> result = graphBFS.realise_BFS(startHere, finishHere);

    if (!result.empty()) {
        std::cout << "\nRESULT NODES in reverse way:" << std::endl;

        int num = result.size();

        for (const int& node : result) {
            std::cout << num << ") Node" << node << std::endl;
            num--;
        }

        std::cout << "\nRESULT WAY: " << std::endl;
        graphBFS.show_result(result);

        graph_to_dot_result(edges, "graph1_result.gv", startHere, finishHere, result);
    }

    return 0;
}
