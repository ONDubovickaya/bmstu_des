cmake_minimum_required(VERSION 3.27)
project(lab12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(
    HEADERS
        graph/Node.h
        graph/Edge.h
        graph/graph_to_dot.h
        data_structures/Queue.h
        search_algorithms/GraphBFS.h
)

set(
    SOURCES
        graph/Node.cpp
        graph/Edge.cpp
        graph/graph_to_dot.cpp
        data_structures/Queue.cpp
        search_algorithms/GraphBFS.cpp
)

add_executable(lab12 ${HEADERS} ${SOURCES} main.cpp)
