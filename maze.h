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

#define LargeValue 99999999

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

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;
	
	char x;
	
	value.resize(rows,cols);
	for (int i = 0; i <= rows-1; i++)
		for (int j = 0; j <= cols-1; j++)
		{
			fin >> x;
			if (x == 'O')
				value[i][j] = true;
			else
				value[i][j] = false;
		}
	
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
	cout << endl;
	
	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");
	
	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");
	
	for (int i = 0; i <= rows-1; i++)
	{
		for (int j = 0; j <= cols-1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
			if (i == currI && j == currJ)
				cout << "+";
			else
			if (value[i][j])
				cout << " ";
			else
				cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");
	
	return value[i][j];
}

void maze::mapMazeToGraph(Graph &g);
// Create a graph g that represents the legal moves in the maze m.

void maze::printPath(Graph::vertex_descriptor end,
					 stack<Graph::vertex_descriptor> &s,
					 Graph g)

					 

#endif //PROJECT4_MAZE_H
