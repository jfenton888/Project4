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






//dijkstra's algorithm will generate best path to every other node it is connected to
//exact path can be built by backtracking from a goal to its predecessor, and the predecessor of that, until reaching start
bool dijkstra(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	heapV<Graph::vertex_descriptor, Graph> queue; //structure to hold priority queue
	Graph::vertex_descriptor currV;
	
	initializeSingleSource(a_graph, a_start); //sets weight of start to 0 and all others to LargeValue
	
	clearVisited(a_graph); //visited property of all nodes set to false
	clearMarked(a_graph); //marked property of all nodes set to false
						  //marked is used to denote if node in priority queue already
	
	//add starting node to queue and mark it
	queue.minHeapInsert(a_start, a_graph);
	a_graph[a_start].marked=true;
	
	//explores every node connected to start
	while (queue.size()>0)
	{
		//current node is the one whose cost is least to explore from those in queue
		//node is then removed from queue and queue is updated
		//when a node is explored there is no better path to that node
		currV=queue.extractMinHeapMinimum(a_graph);
		a_graph[currV].visited=true;
		
		//iterates through all vertices adjacent to current
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vAdjItrRange = adjacent_vertices(currV, a_graph);
		for (Graph::adjacency_iterator vAdjItr= vAdjItrRange.first; vAdjItr != vAdjItrRange.second; ++vAdjItr)
		{
			//if adjacent has been visited don't bother trying to update, no better path exists
			if(!a_graph[*vAdjItr].visited)
			{
				relax(a_graph, currV, *vAdjItr); //updates path to adjacent to be through current if that is cheaper
				
				if(!a_graph[*vAdjItr].marked) //if adjacent not yet in queue then add it and mark as such
				{
					queue.minHeapInsert(*vAdjItr, a_graph);
					a_graph[*vAdjItr].marked=true;
				}
				else //if already in queue then update value based on result of relax
					queue.minHeapDecreaseKey(*vAdjItr, a_graph);
			}
		}
	}
	
	//iterate through every node to check if every node was visited, return false if not
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		if(!a_graph[*vItr].visited)
			return false;
	
	return true;
} // end of dijikstra



bool bellmanFord(Graph &a_graph, Graph::vertex_descriptor a_start)
{
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(a_graph);
	pair<Graph::edge_descriptor, bool> checkEdge;
	Graph::vertex_descriptor edgeSource, edgeTarget;
	
	initializeSingleSource(a_graph, a_start); //sets weight of start to 0 and all others to LargeValue
	
	//edges will be iterated over for the number of vertices in the graph
	//will update the cost of to the target if cost to source and then the connecting edge is less than previous
	for (int itr=1;itr<num_vertices(a_graph);itr++)
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
			relax(a_graph, source(*eItr,a_graph), target(*eItr,a_graph));
	
	
	//iterate over all edges again and check if costs are the same as what is currently recorded
	//if not then there must be a negative cycle so return false, otherwise path creation is done
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


bool wavefront(Graph &a_graph, Graph::vertex_descriptor a_start, Graph::vertex_descriptor a_goal)
{
	queue<Graph::vertex_descriptor> atEdge; //queue of all nodes whose weight has been set
											//and whose neighbors still need to be checked
											//nodes that are marked have been added to the queue already
	Graph::vertex_descriptor currV;
	bool found=false;
	
	//clear markers from all nodes
	clearVisited(a_graph);
	setNodeWeights(a_graph, 0);
	clearMarked(a_graph);
	
	//set goal as first explored, add to queue, and mark as in the queue
	a_graph[a_goal].weight=1;
	a_graph[a_goal].marked=true;
	atEdge.push(a_goal);
	
	//iterates through until all connected nodes have been visited
	while(!atEdge.empty())
	{
		//node at front of queue becomes current, gets removed, and marked as visited
		currV=atEdge.front();
		atEdge.pop();
		a_graph[currV].visited=true;
		
		//cout<<"adding from node at ("<<a_graph[currV].cell.first<<", " <<a_graph[currV].cell.second<<")\n";
		
		//iterates over all nodes adjacent to current
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			//if adjacent node not yet marked, becomes marked, weight is one more than current, added to queue
			if (!a_graph[*vItr].marked)
			{
				a_graph[*vItr].marked = true;
				a_graph[*vItr].weight = a_graph[currV].weight + 1;
				atEdge.push(*vItr);
				
				//wavefront will find solution if start gets added to the queue
				if (*vItr==a_start)
					found=true;
			}
		}
	}
	
	//if start was never added, a path was not found
	if(!found)
		return false;
	
	//then must find path by beginning from start
	currV=a_start;
	int minCost=a_graph[currV].weight;
	//continues until traversed to goal
	while(currV!=a_goal)
	{
		//cout<<"Backtracking from node at ("<<a_graph[currV].cell.first<<", " <<a_graph[currV].cell.second<<") with cost "<<a_graph[currV].weight<<endl;
		
		//iterates over all nodes adjacent to current
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(currV, a_graph);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			//looks for the path that has a lower cost
			//path with lower cost is guarenteed to be closer to goal than current
			//assigns .pred accordingly and doesn't need to look at any others
			if(a_graph[*vItr].weight<minCost)
			{
				minCost=a_graph[*vItr].weight;
				a_graph[*vItr].pred=currV;
				currV=*vItr;
				break;
			}
		}
	}
	return true;

}




bool A_star(Graph &a_graph, Graph::vertex_descriptor a_start, Graph::vertex_descriptor a_goal)
{
	heapV<Graph::vertex_descriptor, Graph> queue; //structure to hold priority queue
	heuristicCost h(a_graph, a_goal); //contains functions to evaluate theoretical cost from any node to goal
									  //can evaluate using Manhattan, Diagonal, or Euclidean Distance
	Graph::vertex_descriptor currV;
	int gCurr=0, gAdj=0; //temporary variables, hold the cost from start to that node
	
	initializeSingleSource(a_graph, a_start); //sets weight of start to 0 and all others to LargeValue
	
	clearVisited(a_graph);//visited property of all nodes set to false
	clearMarked(a_graph); //marked property of all nodes set to false
						  //marked is used to denote if node in priority queue already
	
	//add starting node to queue and mark it
	queue.minHeapInsert(a_start, a_graph);
	a_graph[a_start].marked=true;
	a_graph[a_start].weight=h.ManDist(a_graph, a_start);
	
	//explores every node connected to start until goal is found
	while (queue.size()>0)
	{
		//current node is the one whose cost is least to explore from those in queue
		//node is then removed from queue and queue is updated
		currV=queue.extractMinHeapMinimum(a_graph);
		a_graph[currV].visited=true;
		
		//the cost to traverse to the current node must be calculated
		gCurr = a_graph[currV].weight-h.ManDist(a_graph,currV);
		
		//iterates over all nodes adjacent to the current
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vAdjItrRange = adjacent_vertices(currV, a_graph);
		for (Graph::adjacency_iterator vAdjItr= vAdjItrRange.first; vAdjItr != vAdjItrRange.second; ++vAdjItr)
		{
			//if adjacent has been visited don't bother trying to update, no better path exists
			if(!a_graph[*vAdjItr].visited)
			{
				//checkEdge contains information about the edge that connects the current and adjacent node
				pair<Graph::edge_descriptor, bool> checkEdge = edge(currV, *vAdjItr, a_graph);
				
				//total cost to get to adjacent node is total expected cost minus expected remaining cost
				gAdj = a_graph[*vAdjItr].weight-h.ManDist(a_graph,*vAdjItr);
				
				//if cost to get to adjacent through the current is better than currently recorded,
				// update expected total cost and predecessor
				if (gAdj > gCurr + a_graph[checkEdge.first].weight)
				{
					gAdj = gCurr + a_graph[checkEdge.first].weight;
					a_graph[*vAdjItr].weight = gAdj + h.ManDist(a_graph, *vAdjItr);
					
					a_graph[*vAdjItr].pred = currV;
				}
				//if the adjacent hasnt yet joined the queue, add it
				if(!a_graph[*vAdjItr].marked)
				{
					queue.minHeapInsert(*vAdjItr, a_graph);
					a_graph[*vAdjItr].marked=true;
				}
				else //otherwise update its value
					queue.minHeapDecreaseKey(*vAdjItr, a_graph);
				
				if(*vAdjItr==a_goal) //if that adjacent node is the goal, search is complete
					return true;
			}
		}
	}
	//return false if all connected nodes have been iterated over and goal was never found
	return false;
} // end of A*




int main()
{
	int num = 0;
	cout << "Maze File Algorthims: " << endl;
	cout << "1. Depth First Search Recursive" << endl; 
	cout << "2. Depth First Search stack" << endl;
	cout << "3. Shortest Path Depth First Search" << endl;
	cout << "4. Shortest Path Breadth First Search" << endl;
	cout << "5. Wavefront Algorithm" << endl;
	cout << "6. A* algorithm " << endl;
	cout << "Graph File Algorithms" << endl;
	cout << "7. Dijkstra's Algorithm" << endl;
	cout << "8. BellmanFord Algorithm" << endl; 
	cin >> num;

	
	if (num < 7) {
		ifstream fin;
		// Read the maze from the file.
		string fileName = "maze-files/maze1.txt";

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

		Graph::vertex_descriptor startNode, goalNode;
		startNode = myMaze.getVertex(0, 0);
		goalNode = myMaze.getVertex(myMaze.numRows() - 1, myMaze.numCols() - 1);

		if (num == 1) {
			myMaze.solve.findPathDFSRecursive(graph, startNode, goalNode, bestPath);
		}

		if (num == 2) {
			myMaze.solve.findPathDFSStack(graph, startNode, goalNode, bestPath);
		}

		if (num == 3) {
			myMaze.solve.findShortestPathDFS(graph, startNode, goalNode, bestPath);
		}

		if (num == 4) {
			myMaze.solve.findShortestPathBFS(graph, startNode, goalNode, bestPath);
		}

		if (num == 5) {
			wavefront(graph, startNode, goalNode);
		}

		if (num == 6) {
			if (!A_star(graph, startNode, goalNode))
			{
				cout << "Cannot find path \n";
				return 0;
			}
			else
				generateStack(graph, startNode, goalNode, bestPath);
		}

		myMaze.showPath(graph, startNode, goalNode, bestPath);
	}

	if (num > 6) {
		Graph graph;
		Graph::vertex_descriptor startNode, goalNode;
		stack<Graph::vertex_descriptor> bestPath;

		ifstream fin;

		// Read the maze from the file.
		string fileName = "graph/graph/graph1.txt";

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}
		initializeGraph(graph, startNode, goalNode, fin);

		if (num == 7) {
			if (dijkstra(graph, startNode))
			{
				generateStack(graph, startNode, goalNode, bestPath);

				StackDebug(bestPath);
			}
		}

		if (num == 8) {
			if (bellmanFord(graph, startNode))
			{
				generateStack(graph, startNode, goalNode, bestPath);

				StackDebug(bestPath);
			}
		}
	}
}


