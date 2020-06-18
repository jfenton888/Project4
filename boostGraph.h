//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-13.
//

#ifndef TEST_BOOSTGRAPH_H
#define TEST_BOOSTGRAPH_H


#include <boost/graph/adjacency_list.hpp>
using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, undirectedS, DVertexProperties, EdgeProperties> uGraph;

typedef adjacency_list<vecS, vecS, directedS, DVertexProperties, EdgeProperties> dGraph;


struct DVertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	dGraph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

struct UVertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	uGraph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};



#endif //TEST_BOOSTGRAPH_H
