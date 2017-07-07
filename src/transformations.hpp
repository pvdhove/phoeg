#ifndef PHOEG_TRANSFORMATIONS_H
#define PHOEG_TRANSFORMATIONS_H

#include <boost/graph/graph_traits.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>
#include <boost/graph/graph_utility.hpp>
#include <map>

namespace phoeg {

    //template <class Graph>
    //Graph contract(
    //typename graph_traits<Graph>::vertex_descriptor i,
    //typename graph_traits<Graph>::vertex_descriptor j,
    //const Graph& g)
    //{
    //BOOST_STATIC_ASSERT_MSG(boost::is_same<
    //typename graph_traits<Graph>::directed_category,
    //undirected_tag>::value,
    //"input graph must be undirected.");
    ////BOOST_CONCEPT_ASSERT((VertexListGraphConcept<Graph>));
    ////BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept<Graph>));

    //typedef typename graph_traits<Graph>::vertex_descriptor vertex;

    //Graph gc(num_vertices(g) - 1);

    //[> For all edge (u, v) of G. <]
    //for (auto uit = vertices(gc); uit.first != uit.second; ++uit.first) {
    //for (auto vit = vertices(gc); vit.first != uit.first; ++vit.first) {
    //vertex u = *uit.first;
    //vertex v = *vit.first;
    //if (edge(u, v, g).second) {
    //[> If (u, v) has j as an endpoint, we change it to i
    //(since i is the label for the contracted node).
    //Having i as endpoint doesn't change anything. */
    //if (v == j && u != i)
    //[> Test for u != i to avoid adding self-loops. <]
    //add_edge(u, i, gc);
    //else if (u == j)
    //[> Beware the relabelling of v > j. <]
    //add_edge(i, v - 1, gc);
    //else if (u > j)
    //add_edge(u - 1, v - 1, gc);
    //else if (v > j)
    //add_edge(u, v - 1, gc);
    //else
    //add_edge(u, v, gc);
    //}
    //}
    //}

    //return gc;
    //}

    template <class Graph>
    Graph contract(
        typename boost::graph_traits<Graph>::vertex_descriptor i,
        typename boost::graph_traits<Graph>::vertex_descriptor j,
        const Graph& g)
    {
        BOOST_STATIC_ASSERT_MSG(boost::is_same<
                        typename boost::graph_traits<Graph>::directed_category,
                        boost::undirected_tag>::value,
                        "input graph must be undirected.");
        //BOOST_CONCEPT_ASSERT((VertexListGraphConcept<Graph>));
        //BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept<Graph>));

        typedef typename boost::graph_traits<Graph>::vertex_descriptor
        vertex;
        typedef typename boost::graph_traits<Graph>::vertex_iterator
        vertex_iterator;

        Graph gc(num_vertices(g) - 1);
        std::map<vertex, vertex> m;
        std::pair<vertex_iterator, vertex_iterator> git = vertices(gc);
        std::pair<vertex_iterator, vertex_iterator> uit = vertices(g);
        ++git.first;
        for (; uit.first != uit.second; ++uit.first) {
            if (*uit.first == j || *uit.first == i) {
                m[*uit.first] = *vertices(gc).first;
            } else {
                m[*uit.first] = *git.first;
                ++git.first;
            }
        }
        for (std::pair<vertex_iterator, vertex_iterator> uit = vertices(g);
                uit.first != uit.second; ++uit.first) {
            for (std::pair<vertex_iterator, vertex_iterator> vit = vertices(g);
                    vit.first != vit.second; ++vit.first) {
                if (edge(*uit.first,*vit.first,g).second) {
                    add_edge(m[*uit.first], m[*vit.first], gc);
                }
            }
        }
        return gc;
    }

    /* For undirected graphs.+++
       TODO: Rajouter les boost:: et tester avec adjacency_matrix et adjacency_
             list. */
    template <class Graph>
    Graph rhochiTransform(const Graph & g)
    {
        Graph tg(g); // tg is a copy of g
        typedef typename boost::graph_traits<Graph>::vertex_iterator vertex_iter;
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::adjacency_iterator adj_iter;
        vertex_iter v, v_end;
        adj_iter uit, uit_end, wit, wit_end;
        Vertex vp, up;
        std::map<Vertex, Vertex> copyof;
        for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v) {
            vp = add_vertex(tg);
            add_edge(vp, *v, tg); // Edge vv'
            boost::tie(uit, uit_end) = adjacent_vertices(*v, g);
            copyof.clear();
            for (; uit != uit_end; ++uit) {
                up = add_vertex(tg);
                copyof[*uit] = up;
                add_edge(vp, up, tg); // Edge v'u' for u in N(v)
                boost::tie(wit, wit_end) = adjacent_vertices(*uit, g);
                for (; wit != wit_end; ++wit) {
                    if (!edge(*v, *wit, g).second && *wit != *v) {
                        // Edge u'w for u in N(v), w in N(u) \ (N(v) U {v})
                        add_edge(up, *wit, tg);
                    } else if (copyof.count(*wit)) {
                        // Edge u'w' for u, w in N(v), uw in E
                        add_edge(up, copyof[*wit], tg);
                    }
                }
            }
        }
        
        return tg;
    }

}

#endif

// vim:sw=2:
