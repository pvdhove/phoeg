#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "invariants.hpp"
#include "transformations.hpp"
#include "testUtil.hpp"

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
  BoostUGraph;
  
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
    //displayTransform(completeGraph<BoostUGraph>(3), name);
    //displayTransform(lineGraph<BoostUGraph>(4), name);
    
    return 0;
}
