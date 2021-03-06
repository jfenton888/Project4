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
#include "findPath.h"

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;


struct MazeProperties
{
	bool value;
	Graph::vertex_descriptor vertex;
};



class maze
{
private:
	int m_rows; // number of rows in the maze
	int m_cols; // number of columns in the maze
	
	matrix<MazeProperties> m_maze;


public:
	maze(ifstream &fin); //constructor
	
	findPath solve;
	
	void print(int a_goalY, int a_goalX, int a_cY, int a_cX);
	bool isLegal(int a_y, int a_x);
	void mapMazeToGraph(Graph &a_graph);
	void printPath(Graph a_graph,
				   Graph::vertex_descriptor a_goal,
				   stack<Graph::vertex_descriptor> &a_stack);
	
	int numRows(){return m_rows;};
	int numCols(){return m_cols;};
	
	bool getValue(int a_row, int a_col) const {return m_maze[a_row][a_col].value;};
	Graph::vertex_descriptor getVertex(int a_row, int a_col) const {return m_maze[a_row][a_col].vertex;};
	
	void showPath(Graph a_graph,
						Graph::vertex_descriptor a_start,
						Graph::vertex_descriptor a_goal,
						stack<Graph::vertex_descriptor> &a_stack);
	
	
	
	
	void printGraphProperties(Graph &a_graph) const;
	friend ostream& operator<<(ostream& cout, const Graph &a_graph);
	
};

					 

#endif //PROJECT4_MAZE_H
