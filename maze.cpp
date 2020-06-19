//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "maze.h"
#include "d_except.h"
#include "matrix.h"
#include <boost/graph/adjacency_list.hpp>

#include "boostGraph.h"

using namespace boost;
using namespace std;

// initialize a maze by reading values from fin
maze::maze(ifstream &fin)
{
   fin >> m_rows;
   fin >> m_cols;
   
   char x;
   
   m_maze.resize(m_rows,m_cols);
   
   //m_boolMaze.resize(m_rows,m_cols);
   //m_vertices.resize(m_rows, m_cols);
   
   
   for (int i = 0; i <= m_rows-1; i++)
   {
       for (int j = 0; j <= m_cols - 1; j++)
       {
           fin >> x;
           if (x == 'O')
               m_maze[i][j].value = true;
               //m_boolMaze[i][j] = true;
           else
               m_maze[i][j].value = false;
           //m_boolMaze[i][j] = false;
       }
   }
}



// print out a maze, with the goal and current cells marked on the board.
void maze::print(int a_goalY, int a_goalX, int a_cY, int a_cX)
{
   cout << endl;

   if (a_goalY < 0 || a_goalY > m_rows || a_goalX < 0 || a_goalX > m_cols)
       throw rangeError("Bad value in maze::print");

   if (a_cY < 0 || a_cY > m_rows || a_cX < 0 || a_cX > m_cols)
      throw rangeError("Bad value in maze::print");

   for (int y = 0; y < m_rows; y++)
   {
       for (int x = 0; x < m_cols; x++)
       {
           if (y == a_goalY && x == a_goalX)
               cout << "*";
           else
               if (y == a_cY && x == a_cX)
                   cout << "+";
               else
                   if (m_maze[y][x].value)
                       //if (m_boolMaze[y][x])
                       cout << " ";
                   else
                       cout << "▓";
       }
       cout << endl;
   }
   cout << endl;
}


// return the value stored at the (i,j) entry in the maze, show whether it is legal to go to cell (i,j)
bool maze::isLegal(int a_y, int a_x)
{
   if (a_y < 0 || a_y > m_rows || a_x < 0 || a_x > m_cols)
      throw rangeError("Bad value in maze::isLegal");
   
   return m_maze[a_y][a_x].value;
   //return m_boolMaze[a_y][a_x];
}


// create a graph g that represents the legal moves in the maze m
void maze::mapMazeToGraph(uGraph &a_graph)
{
    for (int y = 0; y < m_rows; y++)
    {
        for (int x = 0; x < m_cols; x++)
        {
            
            if (isLegal(y, x))
            {
                uGraph::vertex_descriptor v = add_vertex(a_graph);
                a_graph[v].cell = pair<int, int>(y, x);
                m_maze[y][x].vertex = v;
                //vertices[y][x] = v;
                a_graph[v].pred = 1;
                if (y != 0 && m_maze[y - 1][x].value)
                {
//                    cout<<"("<<x<<", "<<y<<") Up \n";
                    add_edge(m_maze[y - 1][x].vertex, v, a_graph);
                    add_edge(v, m_maze[y - 1][x].vertex, a_graph);
                }
                if (x != 0 && m_maze[y][x - 1].value)
                {
//                    cout<<"("<<x<<", "<<y<<") Left \n";
                    add_edge(m_maze[y][x - 1].vertex, v, a_graph);
                    add_edge(v, m_maze[y][x - 1].vertex, a_graph);
                }
//                if (y != m_rows-1 && m_maze[y + 1][x].value) {
//                    cout<<"("<<x<<", "<<y<<") Down \n";
//                    add_edge(m_maze[y + 1][x].vertex, v, a_graph);
//                }
//                if (x != m_cols-1 && m_maze[y][x + 1].value) {
//                    cout<<"("<<x<<", "<<y<<") Right \n";
//                    add_edge(m_maze[y][x + 1].vertex, v, a_graph);
//                }

            }
        }
    }
}


// prints the path represented by the vertices in stack s
void maze::printPath(uGraph a_graph,
                     uGraph::vertex_descriptor a_end,
                     stack<uGraph::vertex_descriptor> &a_stack
                     )
{
    // initialize a pair to store values while iterating through the stack
    pair<int,int> curr;
    // get the end of the matrix
    pair<int,int> goal = a_graph[a_end].cell;
    
    if (a_stack.empty()) {
        cout << "The stack is empty - could not find a solution!" << endl;
    }
    while (!a_stack.empty())
    {
        curr = a_graph[a_stack.top()].cell;
        print(goal.first,goal.second,curr.first,curr.second);
        a_stack.pop();
    }
}


void maze::printGraphProperties(uGraph &a_graph) const
{
    //int numEdge = 0;
    
    pair<uGraph::vertex_iterator, uGraph::vertex_iterator> vItrRange = vertices(a_graph);
    
    for (uGraph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        cout << "Vertex: " << *vItr << endl;
        cout << "Cell: (" << a_graph[*vItr].cell.second << ", " <<
             a_graph[*vItr].cell.first << ")" << endl;
        cout << "Predecesor: " << a_graph[*vItr].pred << endl;
        cout << "Weight: " << a_graph[*vItr].weight << endl;
        cout << "Visited: " << a_graph[*vItr].visited << endl;
        cout << "Marked: " << a_graph[*vItr].marked << endl;
    
        pair<uGraph::adjacency_iterator, uGraph::adjacency_iterator> vAdjItrRange = adjacent_vertices(*vItr, a_graph);
        for (uGraph::adjacency_iterator vAdjItr= vAdjItrRange.first; vAdjItr != vAdjItrRange.second; ++vAdjItr)
            cout << "Adjacent to: "<<*vAdjItr<< " at (" << a_graph[*vAdjItr].cell.second << ", " <<
                                             a_graph[*vAdjItr].cell.first << ")" << endl;
        cout << endl;
    }
    
    pair<uGraph::edge_iterator, uGraph::edge_iterator> eItrRange = edges(a_graph);
    
    for (uGraph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        //numEdge++;
        cout << "Edge: " << *eItr << endl;
        cout << "Origin Vertex: " << source(*eItr, a_graph) << endl;
        cout << "Target Vertex: " << target(*eItr, a_graph) << endl;
        cout << "Weight: " << a_graph[*eItr].weight << endl;
        cout << "Visited: " << a_graph[*eItr].visited << endl;
        cout << "Marked: " << a_graph[*eItr].marked << endl << endl;
    }
    
    
    
}



/*
// output operator for the Graph class, prints out all nodes&properties and edges&properties
ostream &operator<<(ostream &cout, const Graph &a_graph)
{
    int numEdge = 0;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(a_graph);
    
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        numEdge++;
        cout << "Edge: " << *eItr << endl;
        cout << "Origin Vertex: " << source(*eItr, a_graph) << endl;
        cout << "Target Vertex: " << target(*eItr, a_graph) << endl;
        cout << "Weight: " << a_graph[*eItr].weight << endl;
        cout << "Visited: " << a_graph[*eItr].visited << endl;
        cout << "Marked: " << a_graph[*eItr].marked << endl << endl;
    }
    
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(a_graph);
    
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        cout << "Vertex: " << *vItr << endl;
        cout << "Cell: (" << a_graph[*vItr].cell.first << ", " <<
                a_graph[*vItr].cell.second << ")" << endl;
        cout << "Predecesor: " << a_graph[*vItr].pred << endl;
        cout << "Weight: " << a_graph[*vItr].weight << endl;
        cout << "Visited: " << a_graph[*vItr].visited << endl;
        cout << "Marked: " << a_graph[*vItr].marked << endl << endl;
    }
    return cout;
}
*/

