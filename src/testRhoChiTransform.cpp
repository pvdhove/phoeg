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

template <class Graph>
int maxDegree(const Graph & g) {
    long answer = 0;
    typedef typename boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    vertex_iter v, v_end;
    for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v) {
        answer = std::max(answer, (long) degree(*v, g));
    }
    return answer;
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
    int cnt = 0;
    /*
    for (int i = 0; i < nbTests; i++) {
        int j = rand() % 5 + 3;
        BoostUGraph g = randomGraph<BoostUGraph>(j);
        long chi = phoeg::chromaticNumber(g);
        long rhochi = phoeg::robustChromaticNumber(g);
        long chiTg = phoeg::chromaticNumber(phoeg::rhochiTransform(g));
        int m = maxDegree(g);
        if (m < chi) {
            if (chi == rhochi) {
                cnt++;
                describe(g, name);
                std::cout << "chi = " << chi << " RhoChi = " << rhochi <<
                         " chi(T(g)) = " << chiTg << "\n";
                std::cout << "**********************\n";
            }
            else {
                std::cout << "WROOONG !!!!!!!\n";
                //describe(g, name);
                std::cout << "chi = " << chi << " RhoChi = " << rhochi <<
                         " chi(T(g)) = " << chiTg << "\n";
                std::cout << "**********************\n";
            }
        }
        assert(chiTg == rhochi);
    }
    std::cout << (double) cnt/nbTests * 100 << "%\n";
    */
    int cnt2 = 0;
    int tab[15];
    for (int i = 0; i < 15; i++) {
        tab[i] = 0;
    }
    for (int i = 0; i < nbTests; i++) {
        int j = rand() % 12 + 1;
        BoostUGraph g = randomGraph<BoostUGraph>(j);
        //describe(g);
        int chi = phoeg::chromaticNumber(g);
        int rhochi = phoeg::robustChromaticNumber(g);
        BoostUGraph gC = phoeg::complement(g);
        //describe(gC);
        int chiC = phoeg::chromaticNumber(gC);
        int rhochiC = phoeg::robustChromaticNumber(gC);
        int sum = chi + rhochi + chiC + rhochiC;
        tab[sum - j]++;
        if (sum - j <= 4) {
            std::cout << sum - j;
            describe(g);
        }
        /*
        std::cout << "Size: " << j << " chi  = " << chi << " rhochi  = " << rhochi;
        std::cout << "\n        chiC = " << chiC << " rhochiC = " << rhochiC << "\n";
        std::cout << "**********************\n";
        if (chiC == rhochiC && chi == rhochi) {
            std::cout << "!!!!!!!!!!!!!!!!!!!!";
            describe(g);
            describe(gC);
            cnt++;
        } */
        
    }
    for (int i = 0; i < 15; i++) {
        std::cout << i << ": " << tab[i] << "\n";
    }
    return 0;
}
