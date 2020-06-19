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

void clearVisited(Graph &g);
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w);
// Set all node weights to w.

void clearMarked(Graph &g);


void initializeGraph(Graph &g,
					 Graph::vertex_descriptor &start,
					 Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties e;
	
	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;
	
	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}
	
	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i,j,e,g);
	}
	
}





void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	// get edge between u and v
	pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
	
	// make sure the edge exists
	if (checkEdge.second != true) {
		cout << "The edge does not exist!" << endl;
	}
	
	// relax
	if (g[v].weight > g[u].weight + g[checkEdge.first].weight)
	{
		g[v].weight = g[u].weight + g[checkEdge.first].weight;
		g[v].pred = u;
	}
}

bool dijkstra(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	heapV<Graph::vertex_descriptor, Graph> queue;
	queue.minHeapInsert(a_start, a_graph);
	
//	while (queue.size()>0)
//	{
//
//	}
	
	
	return true;
} // end of dijikstra


bool bellmanFord(Graph &g, Graph::vertex_descriptor s)
{
	return true;
} // end bellmanFord





int main()
{
	
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
	
}





