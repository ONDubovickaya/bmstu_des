#include "graph_to_dot.h"

void write_graph_to_dot(const std::vector<Edge>& edges, const std::string& filename, int startNode, int finishNode) {
    std::ofstream dotFile(filename);

    if (!dotFile.is_open()) {
        std::cerr << "ERROR with opening file" << std::endl;
        return;
    }

    dotFile << "digraph G {\nrankdir = LR;" << std::endl;

    for (const auto& edge : edges) {
        dotFile << "    " << std::to_string(edge.getStartNode().getNumber()) << " -> " << std::to_string(edge.getEndNode().getNumber())
                << " [label=\"" << edge.getRuleNumber() << "\"];" << std::endl;
    }

    if (startNode == finishNode) {
        dotFile << "    " << startNode << " [shape=doublecircle, style=filled, fillcolor=lightgreen, color=lightcoral];" << std::endl;
    } else {
        dotFile << "    " << startNode << " [shape=circle, style=filled, fillcolor=lightgreen];" << std::endl;
        dotFile << "    " << finishNode << " [shape=circle, style=filled, fillcolor=lightcoral];" << std::endl;
    }
    dotFile << "}" << std::endl;

    dotFile.close();

    std::cout << "Graph was saved in file: '" << filename << "'\n" << std::endl;

    std::string png_file = filename.substr(0, filename.find_last_of('.')) + ".png";
    std::string svg_file = filename.substr(0, filename.find_last_of('.')) + ".svg";

    std::string command_png = "dot -Tpng " + filename + " -o " + png_file;
    std::string command_svg = "dot -Tsvg " + filename + " -o " + svg_file;

    system(command_png.c_str());
    system(command_svg.c_str());

    system(("explorer " + svg_file).c_str());
    // system(("explorer " + png_file).c_str());
}

void graph_to_dot_result(const std::vector<Edge>& edges, const std::string& filename, int startNode, int finishNode, const std::vector<Node>& nodesWay) {
    std::ofstream dotFile(filename);

    if (!dotFile.is_open()) {
        std::cerr << "ERROR with opening file" << std::endl;
        return;
    }

    std::unordered_map<int, int> coloredWay;

    for (size_t i = 1; i < nodesWay.size(); i++) {
        int currentNode = nodesWay[i-1].getNumber();
        coloredWay[currentNode] = nodesWay[i].getNumber();
    }

    dotFile << "digraph G {\nrankdir = LR;" << std::endl;

    for (const auto& edge : edges) {
        int start = edge.getStartNode().getNumber();
        int end = edge.getEndNode().getNumber();

        if (coloredWay.find(start) != coloredWay.end() && coloredWay[start] == end) {
            dotFile << "    " << std::to_string(start) << " -> " << std::to_string(end)
                    << " [label=\"" << edge.getRuleNumber() << "\", color=lightcoral];" << std::endl;
        } else {
            dotFile << "    " << std::to_string(start) << " -> " << std::to_string(end)
                    << " [label=\"" << edge.getRuleNumber() << "\"];" << std::endl;
        }
    }

    if (startNode == finishNode) {
        dotFile << "    " << startNode << " [shape=doublecircle, style=filled, fillcolor=lightgreen, color=lightcoral];" << std::endl;
    } else {
        dotFile << "    " << startNode << " [shape=circle, style=filled, fillcolor=lightgreen];" << std::endl;
        dotFile << "    " << finishNode << " [shape=circle, style=filled, fillcolor=lightcoral];" << std::endl;
    }
    dotFile << "}" << std::endl;

    dotFile.close();

    std::cout << "\nResult was saved in file: '" << filename << "'\n" << std::endl;

    std::string png_file = filename.substr(0, filename.find_last_of('.')) + ".png";
    std::string svg_file = filename.substr(0, filename.find_last_of('.')) + ".svg";

    std::string command_png = "dot -Tpng " + filename + " -o " + png_file;
    std::string command_svg = "dot -Tsvg " + filename + " -o " + svg_file;

    system(command_png.c_str());
    system(command_svg.c_str());

    system(("explorer " + svg_file).c_str());
    // system(("explorer " + png_file).c_str());
}
