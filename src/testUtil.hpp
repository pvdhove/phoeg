#include <iostream>
#include <cstdlib>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "invariants.hpp"

template <class Graph>
void describe(Graph & g, const char* name = "0123456789") {
    std::cout << "vertex set: ";
    print_vertices(g, name);
    std::cout << "\n";

    std::cout << "edge set: ";
    print_edges(g, name);
    std::cout << "\n";

    std::cout << "incident edges: " << "\n";
    print_graph(g, name);
    std::cout << "\n";
}

/* Returns the undirected complete graph with n vertices. */
template <class Graph>
Graph completeGraph(int n) {
    Graph g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            add_edge(i, j, g);
        }
    }
    return g;
}

template <class Graph>
Graph cycleGraph(int n) {
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        add_edge(i, i + 1, g);
    }
    add_edge(n - 1, 0, g);
    return g;
}

template <class Graph>
Graph lineGraph(int n) {
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        add_edge(i, i + 1, g);
    }
    return g;
}

template <class Graph>
Graph randomGraph(int n) {
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2) {
                add_edge(i, j, g);
            }
        }
    }
    return g;
}
