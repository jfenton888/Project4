//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-14.
//

#include "findPath.h"

#include <iostream>
#include <queue>
#include <stack>

#include "global.h"

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;



// traverse function for recursive DFS
bool findPath::traverseDFSRecursive(Graph &a_graph,
						  Graph::vertex_descriptor a_vertex,
						  Graph::vertex_descriptor a_goal,
						  stack<Graph::vertex_descriptor> &a_path,
						  int a_remainingDepth)
{
	// check to see if we are at the goal
	
	//cout<<"("<<a_graph[a_vertex].cell.second<<", "<<a_graph[a_vertex].cell.first<<") \n";
	
	if (a_remainingDepth<=0)
		return false;
	
	if (a_vertex == a_goal)
	{
		a_path.push(a_vertex);
		return true;
	}
	else
	{
		a_graph[a_vertex].visited = true;
		bool found = false;
		
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(a_vertex, a_graph);
		
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if (!a_graph[*vItr].visited) //if not yet visited, visit it
				found = traverseDFSRecursive(a_graph, *vItr, a_goal, a_path, --a_remainingDepth);
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
bool findPath::findPathDFSRecursive(Graph& a_graph,
						  Graph::vertex_descriptor a_start,
						  Graph::vertex_descriptor a_goal,
						  stack<Graph::vertex_descriptor>& a_path,
						  int a_maxDepth)
{
	clearVisited(a_graph);
	
	return traverseDFSRecursive(a_graph, a_start, a_goal, a_path, a_maxDepth);
}




// DFS using stack, not recursion
bool findPath::findPathDFSStack(Graph &a_graph,
					  Graph::vertex_descriptor a_start,
					  Graph::vertex_descriptor a_goal,
					  stack<Graph::vertex_descriptor> &a_path)
{
	
	clearVisited(a_graph);
	bool found = false;
	stack<Graph::vertex_descriptor> thisStack;
	thisStack.push(a_start);
	Graph::vertex_descriptor currV;
	
	while (!thisStack.empty() && !found)
	{
		currV = thisStack.top();
		thisStack.pop();
		if (!a_graph[currV].visited)
		{
			if (currV == a_goal)
				found = true;
			
			a_graph[currV].visited = true;
			
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
			
			for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
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



// find shortest path for DFS
bool findPath::findShortestPathDFS(Graph &a_graph,
						 Graph::vertex_descriptor a_start,
						 Graph::vertex_descriptor a_goal,
						 stack<Graph::vertex_descriptor> &a_path)
{
	clearVisited(a_graph);
	
	for(int depth=1; depth<num_vertices(a_graph);depth++)
		if(findPathDFSRecursive(a_graph,a_start,a_goal,a_path,depth))
			return true;
		
	return false;


}

// search using BFS
bool findPath::findShortestPathBFS(Graph &a_graph,
						 Graph::vertex_descriptor a_start,
						 Graph::vertex_descriptor a_goal,
						 stack<Graph::vertex_descriptor> &a_path)
{
	
	clearVisited(a_graph);
	bool found = false;
	
	queue<Graph::vertex_descriptor> qVertices;
	qVertices.push(a_start);
	Graph::vertex_descriptor currV;
	
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
			
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
			
			for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
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


