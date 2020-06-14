//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#ifndef PROJECT4_MAZE_H
#define PROJECT4_MAZE_H

// Sample solution for project #4

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "matrix.h"

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;

class maze
{
private:
	int m_rows; // number of rows in the maze
	int m_cols; // number of columns in the maze12 a
	
	matrix<bool> m_boolMaze;
	
public:
	maze(ifstream &fin); //constructor
	
	void print(int,int,int,int);
	bool isLegal(int i, int j);
	void mapMazeToGraph(Graph &g);
	void printPath(Graph::vertex_descriptor end,
				   stack<Graph::vertex_descriptor> &s,
				   Graph g);
	
	int numRows(){return m_rows;};
	int numCols(){return m_cols;};

	
};

					 

#endif //PROJECT4_MAZE_H
