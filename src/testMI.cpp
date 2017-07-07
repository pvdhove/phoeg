#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "invariants.hpp"
#include "minimalIncluded.hpp"
#include "transformations.hpp"
#include "testUtil.hpp"

using namespace phoeg;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
  BoostUGraph;

int main(int, char*[]) {
    const char* name = "0123456789ABCDEFGHIJKLMNOP";

    BoostUGraph g2(2);
    describe(g2, name);

    BoostUGraph p2 = lineGraph<BoostUGraph>(2);
    describe(p2, name);

    BoostUGraph g21(p2);
    add_vertex(g21);
    describe(g21, name);

    BoostUGraph k3 = completeGraph<BoostUGraph>(3);
    describe(k3, name);

    BoostUGraph p3 = lineGraph<BoostUGraph>(3);
    describe(p3, name);

    BoostUGraph p4 = lineGraph<BoostUGraph>(4);
    describe(p4, name);

    BoostUGraph c4 = cycleGraph<BoostUGraph>(4);
    describe(c4, name);

    cout << "***********MINIMAL INCLUDED GRAPHS***********" << "\n";
    bool iso = true;
    std::vector<BoostUGraph> V;
    V.push_back(g21);
    for (int i = 5; i <= 50; i++) {
        V.push_back(completeGraph<BoostUGraph>(i));
        V.push_back(lineGraph<BoostUGraph>(i));
        V.push_back(cycleGraph<BoostUGraph>(i));
    }
    auto MIV = minimalIncluded<BoostUGraph>(V, iso);
    for (auto it: MIV) {
        describe(it, name);
    }
    
    return 0;
}
