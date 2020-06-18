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
#include "maze.h"
#include "findPath.h"

#include <boost/graph/adjacency_list.hpp>

#include "boostGraph.h"

using namespace boost;
using namespace std;


#define LargeValue 99999999

void clearVisited(uGraph &g);
// Mark all nodes in g as not visited.

void setNodeWeights(uGraph &g, int w);
// Set all node weights to w.

void clearMarked(uGraph &g);


void initializeGraph(dGraph &g,
					 dGraph::vertex_descriptor &start,
					 dGraph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
	EdgeProperties e;
	
	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	dGraph::vertex_descriptor v;
	
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





void relax(uGraph &g, uGraph::vertex_descriptor u, uGraph::vertex_descriptor v)
{
	// get edge between u and v
	pair<uGraph::edge_descriptor, bool> checkEdge = edge(u, v, g);
	
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

bool dijkstra(dGraph &a_graph, dGraph::vertex_descriptor a_start)
{
	heapV<dGraph::vertex_descriptor, dGraph> queue;
	queue.minHeapInsert(a_start, a_graph);
	
//	while (queue.size()>0)
//	{
//
//	}
	
	
	return true;
} // end of dijikstra


bool bellmanFord(dGraph &g, dGraph::vertex_descriptor s)
{
	return true;
} // end bellmanFord


template <typename T>
void StackDebug(std::stack<T> s)
{
	std::vector<T> debugVector = std::vector<T>();
	while (!s.empty( ) )
	{
		T t = s.top( );
		debugVector.push_back(t);
		s.pop( );
	}
	
	// stack, read from top down, is reversed relative to its creation (from bot to top)
	std::reverse(debugVector.begin(), debugVector.end());
	for(const auto& it : debugVector)
	{
		std::cout << it << " ";
	}
}




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
	
	maze m(fin);
	fin.close();
	
	//m.print(m.numRows() - 1, m.numCols() - 1, 0, 0);
	
	
	uGraph graph;
	m.mapMazeToGraph(graph);
	
	//m.printGraphProperties(graph);
	
	findPath solver;
	stack<uGraph::vertex_descriptor> bestPath;
	
	uGraph::vertex_descriptor startGraph, endGraph;
	
	startGraph = m.getVertex(0, 0);
	endGraph = m.getVertex(m.numRows() - 1, m.numCols() - 1);
	
	solver.findShortestPathDFS(graph, startGraph, endGraph, bestPath);
	
	StackDebug(bestPath);
	
	m.printPath(graph, endGraph, bestPath);
	
}





