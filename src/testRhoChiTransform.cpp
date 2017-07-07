#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "invariants.hpp"
#include "transformations.hpp"
#include "testUtil.hpp"

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
  BoostUGraph;

template <class Graph, class Vertex>
void displayTransformVertex(const Graph & g, Vertex v, const char* name) {
    Graph tg = phoeg::rhochiTransformOneVertex(g, v);
    cout << "***********GRAPH***********" << "\n";
    describe(g, name);
    cout << "***********TRANSFORMED INTO***********" << "\n";
    describe(tg, name);
}

template <class Graph>
void displayTransform(const Graph & g, const char* name) {
    Graph tg = phoeg::rhochiTransform(g);
    cout << "***********GRAPH***********" << "\n";
    describe(g, name);
    cout << "***********TRANSFORMED INTO***********" << "\n";
    describe(tg, name);
}

int main() {
    const char* name = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    displayTransform(completeGraph<BoostUGraph>(2), name);
    displayTransformVertex(completeGraph<BoostUGraph>(3), 0, name);
    displayTransformVertex(lineGraph<BoostUGraph>(4), 1, name);
    displayTransformVertex(lineGraph<BoostUGraph>(4), 0, name);
    displayTransform(completeGraph<BoostUGraph>(5), name);
    
    return 0;
}
