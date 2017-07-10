#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "invariants.hpp"
#include "transformations.hpp"
#include "testUtil.hpp"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
  BoostUGraph;

template <class Graph, class Vertex>
void displayTransformVertex(const Graph & g, Vertex v, const char* name) {
    Graph tg = phoeg::rhochiTransformOneVertex(g, v);
    std::cout << "***********GRAPH***********" << "\n";
    describe(g, name);
    std::cout << "***********TRANSFORMED INTO***********" << "\n";
    describe(tg, name);
}

template <class Graph>
void displayTransform(const Graph & g, const char* name) {
    Graph tg = phoeg::rhochiTransform(g);
    std::cout << "***********GRAPH***********" << "\n";
    describe(g, name);
    std::cout << "***********TRANSFORMED INTO***********" << "\n";
    describe(tg, name);
}

int main() {
    const char* name = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    //displayTransform(completeGraph<BoostUGraph>(2), name);
    //displayTransformVertex(completeGraph<BoostUGraph>(3), 0, name);
    //displayTransformVertex(lineGraph<BoostUGraph>(4), 1, name);
    //displayTransformVertex(lineGraph<BoostUGraph>(4), 0, name);
    //displayTransform(completeGraph<BoostUGraph>(5), name);
    
    int nbTests = 1000;
    srand(time(0)); // Makes the output different on each run
    
    for (int i = 0; i < nbTests; i++) {
        int j = rand() % 5 + 3;
        BoostUGraph g = randomGraph<BoostUGraph>(j);
        describe(g, name);
        long chi = phoeg::chromaticNumber(g);
        long rhochi = phoeg::robustChromaticNumber(g);
        long chiTg = phoeg::chromaticNumber(phoeg::rhochiTransform(g));
        std::cout << "chi = " << chi << " RhoChi = " << rhochi <<
                     " chi(T(g)) = " << chiTg << "\n";
        assert(chiTg == rhochi);
        std::cout << "**********************\n";
    }
    
    return 0;
}
