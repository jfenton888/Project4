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

typedef adjacency_list<vecS, vecS, directedS, VertexProperties, EdgeProperties> Graph;


struct VertexProperties
{
	pair<int,int> cell; // maze cell (y,x) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked; //used for denoting if already queued
};


// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};



#endif //TEST_BOOSTGRAPH_H
