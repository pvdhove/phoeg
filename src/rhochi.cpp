#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "graph.hpp"
#include "graph6.hpp"
#include "transformations.hpp"
#include "invariants.hpp"
#include "testUtil.hpp"

using namespace std;

template <class Graph>
void describe(const Graph& g, const char* name) {
  cout << "vertex set: ";
  print_vertices(g, name);
  cout << endl;

  cout << "edge set: ";
  print_edges(g, name);
  cout << endl;

  cout << "incident edges: " << endl;
  print_graph(g, name);
  cout << endl;

  cout << "NumCol: " << phoeg::numCol(g) << endl;
}

int main(int, char*[]) {
  const char* name = "petersen";

  phoeg::Graph g = phoeg::convertFromGraph6("IsP@OkWHG");

  describe(g, name);

  int k = 3;
  //bool krho = phoeg::detail::is_k_colorable(g, k, true);
  //cout << "Is " << k << " robust-colorable: " << krho << endl;
  //cout << "Its numcol-" << k << " is:" << phoeg::numColK(g, k) << endl;

  phoeg::Graph k4 = completeGraph<phoeg::Graph>(4);
  cout << phoeg::chromaticNumber(k4);
  return 0;
}
