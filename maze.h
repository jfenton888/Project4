//
// Project by Jack Fenton
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
#include "d_matrix.h"

using namespace std;

class maze
{
public:
	maze(ifstream &fin);
	void print(int,int,int,int);
	bool isLegal(int i, int j);
	void mapMazeToGraph(Graph &g);
	void printPath(Graph::vertex_descriptor end,
				   stack<Graph::vertex_descriptor> &s,
				   Graph g);
	int numRows(){return rows;};
	int numCols(){return cols;};

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze12 a
	
	matrix<bool> value;
};

					 

#endif //PROJECT4_MAZE_H
