//
// Project by Jack Fenton
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-18.
//

#ifndef PROJECT4_GLOBAL_H
#define PROJECT4_GLOBAL_H

#include <iostream>
#include <stack>

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;

void clearVisited(Graph &a_graph);

void setNodeWeights(Graph &a_graph, int a_value);

void clearMarked(Graph &a_graph);

void clearStack(stack<Graph::vertex_descriptor> &a_path);

template <typename T>
void StackDebug(stack<T> s)
{
	vector<T> debugVector = vector<T>();
	while (!s.empty( ) )
	{
		T t = s.top( );
		debugVector.push_back(t);
		s.pop( );
	}
	
	// stack, read from top down, is reversed relative to its creation (from bot to top)
	reverse(debugVector.begin(), debugVector.end());
	for(const auto& it : debugVector)
	{
		cout << it << " ";
	}
}



#endif //PROJECT4_GLOBAL_H
