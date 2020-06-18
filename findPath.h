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
	void clearVisited(uGraph &a_graph);
	void setNodeWeights(uGraph &a_graph, int a_value);
	void clearMarked(uGraph &a_graph);
	void clearStack(stack<uGraph::vertex_descriptor> &a_path);
	
	bool traverseDFSRecursive(uGraph &a_graph,
							  uGraph::vertex_descriptor a_vertex,
							  uGraph::vertex_descriptor a_goal,
							  stack<uGraph::vertex_descriptor> &a_path);
	
	bool findPathDFSRecursive(uGraph& a_graph,
							  uGraph::vertex_descriptor a_start,
							  uGraph::vertex_descriptor a_goal,
							  stack<uGraph::vertex_descriptor>& a_path);
	
	bool findPathDFSStack(uGraph &a_graph,
						  uGraph::vertex_descriptor a_start,
						  uGraph::vertex_descriptor a_goal,
						  stack<uGraph::vertex_descriptor> &a_path);
	
	bool traverseDFSShortest(uGraph &a_graph,
							 uGraph::vertex_descriptor a_vertex,
							 uGraph::vertex_descriptor a_goal,
							 stack<uGraph::vertex_descriptor> &a_tempStack,
							 stack<uGraph::vertex_descriptor> &a_path);
	
	bool findShortestPathDFS(uGraph &a_graph,
							 uGraph::vertex_descriptor a_start,
							 uGraph::vertex_descriptor a_goal,
							 stack<uGraph::vertex_descriptor> &a_path);
	
	bool findShortestPathBFS(uGraph &a_graph,
							 uGraph::vertex_descriptor a_start,
							 uGraph::vertex_descriptor a_goal,
							 stack<uGraph::vertex_descriptor> &a_path);
	
	
	
	
};


#endif //PROJECT4_FINDPATH_H
