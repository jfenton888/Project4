//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-14.
//

#include <iostream>
#include <queue>
#include <stack>

#include "findPath.h"

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;




// mark all nodes in g as not visited
void findPath::clearVisited(uGraph &a_graph)
{
	// get a pair containing iterators pointing the beginning and end of the list of nodes
	pair<uGraph::vertex_iterator, uGraph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (uGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].visited = false;
	}
}

// set all node weights to w
// edges, not verticies???????????????????
void findPath::setNodeWeights(uGraph &a_graph, int a_value)
{
	
	pair<uGraph::vertex_iterator, uGraph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (uGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].weight = a_value;
	}
}

// unmark all nodes
void findPath::clearMarked(uGraph &a_graph)
{
	
	pair<uGraph::vertex_iterator, uGraph::vertex_iterator> vItrRange = vertices(a_graph);
	// loop over all nodes in the graph
	for (uGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].marked = false;
	}
}

// function to clear the stack
void findPath::clearStack(stack<uGraph::vertex_descriptor> &a_path)
{
	
	while (!a_path.empty())
	{
		a_path.pop();
	}
}






// traverse function for recursive DFS
bool findPath::traverseDFSRecursive(uGraph &a_graph,
						  uGraph::vertex_descriptor a_vertex,
						  uGraph::vertex_descriptor a_goal,
						  stack<uGraph::vertex_descriptor> &a_path)
{
	// check to see if we are at the goal
	
	cout<<"("<<a_graph[a_vertex].cell.second<<", "<<a_graph[a_vertex].cell.first<<") \n";
	
	if (a_vertex == a_goal)
	{
		a_path.push(a_vertex);
		return true;
	}
	else
	{
		a_graph[a_vertex].visited = true;
		bool found = false;
		
		pair<uGraph::adjacency_iterator, uGraph::adjacency_iterator> vItrRange = adjacent_vertices(a_vertex, a_graph);
		
		for (uGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if (!a_graph[*vItr].visited) //if not yet visited, visit it
				found = traverseDFSRecursive(a_graph, *vItr, a_goal, a_path);
			if (found)
				break;
		}
		if (found)
		{
			a_path.push(a_vertex);
		}
		return found;
	}
	
}

// recursive DFS
bool findPath::findPathDFSRecursive(uGraph& a_graph,
						  uGraph::vertex_descriptor a_start,
						  uGraph::vertex_descriptor a_goal,
						  stack<uGraph::vertex_descriptor>& a_path)
{
	clearVisited(a_graph);
	
	return traverseDFSRecursive(a_graph, a_start, a_goal, a_path);
}




// DFS using stack, not recursion
bool findPath::findPathDFSStack(uGraph &a_graph,
					  uGraph::vertex_descriptor a_start,
					  uGraph::vertex_descriptor a_goal,
					  stack<uGraph::vertex_descriptor> &a_path)
{
	
	clearVisited(a_graph);
	bool found = false;
	stack<uGraph::vertex_descriptor> thisStack;
	thisStack.push(a_start);
	uGraph::vertex_descriptor currV;
	
	while (!thisStack.empty() && !found)
	{
		currV = thisStack.top();
		thisStack.pop();
		if (!a_graph[currV].visited)
		{
			if (currV == a_goal)
				found = true;
			
			a_graph[currV].visited = true;
			
			pair<uGraph::adjacency_iterator, uGraph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
			
			for (uGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
			{
				if (!a_graph[*vItr].visited)
				{
					a_graph[*vItr].pred = currV;
					thisStack.push(*vItr);
				}
			}
		}
	}
	
	if (found) //track back from end to beginning using previous
	{
		currV = a_goal;
		while (currV != a_start)
		{
			a_path.push(currV);
			currV = a_graph[currV].pred;
		}
		a_path.push(a_start);
	}
	return found;
}


// traverse function for shortest DFS
bool findPath::traverseDFSShortest(uGraph &a_graph,
						 uGraph::vertex_descriptor a_vertex,
						 uGraph::vertex_descriptor a_goal,
						 stack<uGraph::vertex_descriptor> &a_tempStack,
						 stack<uGraph::vertex_descriptor> &a_path)
{
	a_tempStack.push(a_vertex);
	
	// check if we are at the end
	if (a_vertex == a_goal)
	{
		if (a_path.empty() || a_tempStack.size() < a_path.size())
			a_path = a_tempStack;
		
		return true;
	}
	else
	{
		a_graph[a_vertex].visited = true;
		bool found = false;
		
		pair<uGraph::adjacency_iterator, uGraph::adjacency_iterator> vItrRange = adjacent_vertices(a_vertex, a_graph);
		
		for (uGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if (!a_graph[*vItr].visited)
			{
				//found = traverseDFSShortest(g, *vItr, end, path, tempStack);
				found = traverseDFSShortest(a_graph, *vItr, a_goal, a_tempStack, a_path);
				a_tempStack.pop();
			}
		}
		return found;
	}
}

// find shortest path for DFS
bool findPath::findShortestPathDFS(uGraph &a_graph,
						 uGraph::vertex_descriptor a_start,
						 uGraph::vertex_descriptor a_goal,
						 stack<uGraph::vertex_descriptor> &a_path)
{
	clearVisited(a_graph);
	stack<uGraph::vertex_descriptor> tempStack;
	return traverseDFSShortest(a_graph, a_start, a_goal, tempStack, a_path);
}

// search using BFS
bool findPath::findShortestPathBFS(uGraph &a_graph,
						 uGraph::vertex_descriptor a_start,
						 uGraph::vertex_descriptor a_goal,
						 stack<uGraph::vertex_descriptor> &a_path)
{
	
	clearVisited(a_graph);
	bool found = false;
	
	queue<uGraph::vertex_descriptor> qVertices;
	qVertices.push(a_start);
	uGraph::vertex_descriptor currV;
	
	pair<int,int> cell = a_graph[a_start].cell;
	
	
	while (!qVertices.empty() && !found)
	{
		
		currV = qVertices.front();
		
		//cout<<"("<<a_graph[currV].cell.second<<", "<<a_graph[currV].cell.first<<") \n";
		
		qVertices.pop();
		if (!a_graph[currV].visited)
		{
			a_graph[currV].visited = true;
			if (currV == a_goal)
				found = true;
			
			pair<uGraph::adjacency_iterator, uGraph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
			
			for (uGraph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
			{
				if (!a_graph[*vItr].visited)
				{
					a_graph[*vItr].pred = currV;
					qVertices.push(*vItr);
				}
			}
		}
	}
	
	if (found) //track back from end to beginning using previous
	{
		currV = a_goal;
		while (currV != a_start)
		{
			a_path.push(currV);
			currV = a_graph[currV].pred;
		}
		a_path.push(a_start);
	}
	return found;
}


