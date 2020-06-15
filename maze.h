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


struct MazeProperties
{
	matrix<bool> value;
	matrix<Graph::vertex_descriptor> vertex;
};



class maze
{
private:
	int m_rows; // number of rows in the maze
	int m_cols; // number of columns in the maze
	
	//matrix<bool> m_boolMaze;
	//matrix<Graph::vertex_descriptor> m_vertices;
	
	MazeProperties m_maze;


public:
	maze(ifstream &fin); //constructor
	
	void print(int a_goalY, int a_goalX, int a_cY, int a_cX);
	bool isLegal(int a_y, int a_x);
	void mapMazeToGraph(Graph &a_graph);
	void printPath(Graph::vertex_descriptor a_end,
				   stack<Graph::vertex_descriptor> &a_stack,
				   Graph a_graph);
	
	int numRows(){return m_rows;};
	int numCols(){return m_cols;};

	
};

					 

#endif //PROJECT4_MAZE_H
