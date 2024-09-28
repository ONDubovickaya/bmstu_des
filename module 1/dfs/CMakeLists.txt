cmake_minimum_required(VERSION 3.27)
project(lab11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(
    HEADERS
        graph/Node.h
        graph/Edge.h
        graph/graph_to_dot.h
        data_structures/Stack.h
        search_algorithms/GraphDFS.h
)

set(
    SOURCES
        graph/Node.cpp
        graph/Edge.cpp
        graph/graph_to_dot.cpp
        data_structures/Stack.cpp
        search_algorithms/GraphDFS.cpp
)

add_executable(lab11 ${HEADERS} ${SOURCES} main.cpp)
