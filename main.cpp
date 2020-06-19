//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <iterator>
#include <algorithm>

#include "heapV.h"
#include "heapV.cpp"
#include "maze.h"
#include "findPath.h"
#include "global.h"

#include <boost/graph/adjacency_list.hpp>

#include "boostGraph.h"

using namespace boost;
using namespace std;


#define LargeValue 99999999



void initializeGraph(
					 Graph &a_graph,
					 Graph::vertex_descriptor &a_start,
					 Graph::vertex_descriptor &a_goal,
					 ifstream &a_fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties edge;
	
	int n, i, j;
	int startId, goalId;
	a_fin >> n;
	a_fin >> startId >> goalId;
	Graph::vertex_descriptor v;
	
	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(a_graph);
		if (i == startId)
			a_start = v;
		if (i == goalId)
			a_goal = v;
	}
	
	while (a_fin.peek() != '.')
	{
		a_fin >> i >> j >> edge.weight;
		add_edge(i, j, edge, a_graph);
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


bool dijkstra(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	heapV<Graph::vertex_descriptor, Graph> queue;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	Graph::vertex_descriptor currV;
	
	initializeSingleSource(a_graph, a_start);
	
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		queue.minHeapInsert(a_start, a_graph);
	
	clearVisited(a_graph);
	while (queue.size()>0)
	{
		currV=queue.extractMinHeapMinimum(a_graph);
		a_graph[currV].visited=true;
		
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vAdjItrRange = adjacent_vertices(currV, a_graph);
		for (Graph::adjacency_iterator vAdjItr= vAdjItrRange.first; vAdjItr != vAdjItrRange.second; ++vAdjItr)
		{
			if(!a_graph[*vAdjItr].visited)
			{
				relax(a_graph, currV, *vAdjItr);
				queue.minHeapDecreaseKey(*vAdjItr, a_graph);
			}
		}
	}
	
	
	return true;
} // end of dijikstra



bool bellmanFord(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(a_graph);
	
	initializeSingleSource(a_graph, a_start);
	
	for (int itr=1;itr<num_vertices(a_graph);itr++)
	{
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
		{
			relax(a_graph, source(*eItr,a_graph), target(*eItr,a_graph));
		}
	}
	Graph::vertex_descriptor edgeSource, edgeTarget;
	pair<Graph::edge_descriptor, bool> checkEdge;
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		
		edgeSource = source(*eItr,a_graph);
		edgeTarget = target(*eItr,a_graph);
		checkEdge = edge(edgeSource, edgeTarget, a_graph);
		if(a_graph[edgeTarget].weight > a_graph[edgeSource].weight + a_graph[checkEdge.first].weight)
			return false;
	}
	
	return true;
} // end bellmanFord


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


int main()
{
/*
	ifstream fin;
	
	// Read the maze from the file.
	string fileName = "maze-files/maze13.txt";
	
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}
	
	maze myMaze(fin);
	fin.close();
	
	Graph graph;
	myMaze.mapMazeToGraph(graph);
	
	stack<Graph::vertex_descriptor> bestPath;
	
	Graph::vertex_descriptor startNode, endNode;
	startNode = myMaze.getVertex(0, 0);
	endNode = myMaze.getVertex(myMaze.numRows() - 1, myMaze.numCols() - 1);
	
	myMaze.solve.findShortestPathDFS(graph, startNode, endNode, bestPath);
	
	myMaze.printPath(graph, endNode, bestPath);
*/


	Graph graph;
	Graph::vertex_descriptor startNode, goalNode;
	stack<Graph::vertex_descriptor> bestPath;
	
	ifstream fin;
	
	// Read the maze from the file.
	string fileName = "graph/graph1.txt";
	
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}
	initializeGraph(graph, startNode, goalNode, fin);
	
	
	if(bellmanFord(graph, startNode))
	{
		generateStack(graph, startNode, goalNode, bestPath);
		
		StackDebug(bestPath);
	}

}




