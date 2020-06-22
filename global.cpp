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

#define LargeValue 99999999

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


void relax(Graph &a_graph,
		   Graph::vertex_descriptor a_source,
		   Graph::vertex_descriptor a_target)
{
	// get edge between u and v
	pair<Graph::edge_descriptor, bool> checkEdge = edge(a_source, a_target, a_graph);
	
	// make sure the edge exists
	if (checkEdge.second != true) {
		cout << "The edge does not exist!" << endl;
	}
	
	// relax
	if (a_graph[a_target].weight > a_graph[a_source].weight + a_graph[checkEdge.first].weight)
	{
		a_graph[a_target].weight = a_graph[a_source].weight + a_graph[checkEdge.first].weight;
		a_graph[a_target].pred = a_source;
	}
}


void initializeSingleSource(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		a_graph[*vItr].weight=LargeValue;
		//a_graph[*vItr].pred= NIL; //need to figure out the null pointer for this
	}
	a_graph[a_start].weight=0;
}


void generateStack(Graph &a_graph,
				   Graph::vertex_descriptor a_start,
				   Graph::vertex_descriptor a_goal,
				   stack<Graph::vertex_descriptor> &a_path)
{
	Graph::vertex_descriptor currV;
	
	currV = a_goal;
	
	while (currV != a_start)
	{
		
		a_path.push(currV);
		currV = a_graph[currV].pred;
	}
	a_path.push(a_start);
}


int isInt(string a_prompt, int a_min, int a_max)
{
	int input=NULL;
	while((input<a_min) || (input>a_max))
	{
		cout << a_prompt;
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		else break;
	}
	return input;
}