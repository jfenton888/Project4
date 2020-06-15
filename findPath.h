//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-14.
//

#ifndef PROJECT4_FINDPATH_H
#define PROJECT4_FINDPATH_H

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;

class findPath
{

public:
	void clearVisited(Graph &a_graph);
	void setNodeWeights(Graph &a_graph, int a_value);
	void clearMarked(Graph &a_graph);
	void clearStack(stack<Graph::vertex_descriptor> &a_path);
	
	bool traverseDFSRecursive(Graph &a_graph,
							  Graph::vertex_descriptor a_vertex,
							  Graph::vertex_descriptor a_goal,
							  stack<Graph::vertex_descriptor> &a_path);
	
	bool findPathDFSRecursive(Graph& a_graph,
							  Graph::vertex_descriptor a_start,
							  Graph::vertex_descriptor a_goal,
							  stack<Graph::vertex_descriptor>& a_path);
	
	bool findPathDFSStack(Graph &a_graph,
						  Graph::vertex_descriptor a_start,
						  Graph::vertex_descriptor a_goal,
						  stack<Graph::vertex_descriptor> &a_path);
	
	bool traverseDFSShortest(Graph &a_graph,
							 Graph::vertex_descriptor a_vertex,
							 Graph::vertex_descriptor a_goal,
							 stack<Graph::vertex_descriptor> &a_tempStack,
							 stack<Graph::vertex_descriptor> &a_path);
	
	bool findShortestPathDFS(Graph &a_graph,
							 Graph::vertex_descriptor a_start,
							 Graph::vertex_descriptor a_goal,
							 stack<Graph::vertex_descriptor> &a_path);
	
	bool findShortestPathBFS(Graph &a_graph,
							 Graph::vertex_descriptor a_start,
							 Graph::vertex_descriptor a_goal,
							 stack<Graph::vertex_descriptor> &a_path);
	
	
	
	
};


#endif //PROJECT4_FINDPATH_H
