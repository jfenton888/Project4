//
// Project by Jack Fenton
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-18.
//

#include "global.h"

#include <iostream>
#include <stack>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;

// mark all nodes in g as not visited
void clearVisited(Graph &a_graph)
{
	// get a pair containing iterators pointing the beginning and end of the list of nodes
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].visited = false;
	}
}

// set all node weights to w
// edges, not verticies???????????????????
void setNodeWeights(Graph &a_graph, int a_value)
{
	
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].weight = a_value;
	}
}

// unmark all nodes
void clearMarked(Graph &a_graph)
{
	
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].marked = false;
	}
}


// function to clear the stack
void clearStack(stack<Graph::vertex_descriptor> &a_path)
{
	
	while (!a_path.empty())
	{
		a_path.pop();
	}
}





