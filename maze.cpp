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
   
    m_boolMaze.resize(m_rows,m_cols);
   for (int i = 0; i <= m_rows-1; i++)
      for (int j = 0; j <= m_cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
             m_boolMaze[i][j] = true;
         else
             m_boolMaze[i][j] = false;
      }
   
    vertices.resize(m_rows, m_cols);
}

// mark all nodes in g as not visited
void clearVisited(Graph &g)
{
    // get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
       {
           g[*vItr].visited = false;
       }
}

// set all node weights to w
// edges, not verticies???????????????????
void setNodeWeights(Graph &g, int w) {
    
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].weight = w;
    }
}

// unmark all nodes
void clearMarked(Graph &g){
    
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].marked = false;
    }
}

// function to clear the stack
void clearStack(stack<Graph::vertex_descriptor> &path){
    
    while (!path.empty())
    {
        path.pop();
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
           if (m_boolMaze[y][x])
          cout << " ";
           else
          cout << "X";
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

   return m_boolMaze[a_y][a_x];
}

// create a graph g that represents the legal moves in the maze m
void maze::mapMazeToGraph(Graph &a_graph)
{
    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            
            if (isLegal(y, x)) {
                Graph::vertex_descriptor v = add_vertex(a_graph);
                a_graph[v].cell = pair<int, int>(y, x);
                vertices[y][x] = v;
                a_graph[v].pred = 1;
                if (y != 0 && m_boolMaze[y - 1][x]) {
                    add_edge(vertices[y - 1][x], v, a_graph);
                }
                if (x != 0 && m_boolMaze[y][x - 1]) {
                    add_edge(vertices[y][x - 1], v, a_graph);
                }
            }
        }
    }
}


// prints the path represented by the vertices in stack s
void maze::printPath(Graph::vertex_descriptor end,stack<Graph::vertex_descriptor> &s,Graph g) {
    // initialize a pair to store values while iterating through the stack
    pair<int,int> curr;
    // get the end of the matrix
    pair<int,int> goal = g[end].cell;
    
    if (s.empty()) {
        cout << "The stack is empty - could not find a solution!" << endl;
    }
    while (!s.empty()) {
        curr = g[s.top()].cell;
        print(goal.first,goal.second,curr.first,curr.second);
        s.pop();
    }
}

// output operator for the Graph class, prints out all nodes&properties and edges&properties
ostream &operator<<(ostream &ostr, const Graph &g){
    int numEdge = 0;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        numEdge++;
        ostr << "Edge: " << *eItr << endl;
        ostr << "Origin Vertex: " << source(*eItr, g) << endl;
        ostr << "Target Vertex: " << target(*eItr, g) << endl;
        ostr << "Weight: " << g[*eItr].weight << endl;
        ostr << "Visited: " << g[*eItr].visited << endl;
        ostr << "Marked: " << g[*eItr].marked << endl << endl;
    }
    
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        ostr << "Vertex: " << *vItr << endl;
        ostr << "Cell: (" << g[*vItr].cell.first << ", " <<
            g[*vItr].cell.second << ")" << endl;
        ostr << "Predecesor: " << g[*vItr].pred << endl;
        ostr << "Weight: " << g[*vItr].weight << endl;
        ostr << "Visited: " << g[*vItr].visited << endl;
        ostr << "Marked: " << g[*vItr].marked << endl << endl;
    }
    return ostr;
}

// traverse function for recursive DFS
bool traverseDFSRecursive(Graph &g, Graph::vertex_descriptor v, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path)
{
    // check to see if we are at the goal
    if (v == goal)
    {
        path.push(v);
        return true;
    }
    else {
        g[v].visited = true;
        bool found = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
            vItrRange = adjacent_vertices(v, g);
        for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
        {
            if (!g[*vItr].visited)
            {
                found = traverseDFSRecursive(g, *vItr, goal, path);
            }
            if (found) break;
        }
        if (found)
        {
            path.push(v);
        }
        return found;
    }
}
   
// recursive DFS
bool findPathDFSRecursive(Graph& g, Graph::vertex_descriptor start,
    Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor>& path) {
    
    clearVisited(g);
    path.push(goal);
    return traverseDFSRecursive(g, start, end, path);
}

// DFS using stack, not recursion
bool findPathDFSStack(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path){
   
    clearVisited(g);
    bool found = false;
    stack<Graph::vertex_descriptor> theVertices;
    theVertices.push(start);
    Graph::vertex_descriptor currV;
        
    while (!theVertices.empty() && !found) {
        currV = theVertices.top();
        theVertices.pop();
        if (!g[currV].visited) {
            if (currV == goal) {
                found = true;
            }
            g[currV].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
                vItrRange = adjacent_vertices(currV, g);
            for (Graph::adjacency_iterator vItr = vItrRange.first;
            vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    g[*vItr].pred = currV;
                    theVertices.push(*vItr);
                }
            }
        }
    }
    if (found) {
        while (currV != -1) {
            path.push(currV);
            currV = g[currV].pred;
        }
    }
    return found;
    
}

// traverse function for shortest DFS
bool traverseDFSShortest(Graph &g, Graph::vertex_descriptor v, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor>& tempStack, stack<Graph::vertex_descriptor> &path){
    tempStack.push(v);

    // check if we are at the end
    if (v == goal) {
        if (path.empty() or tempStack.size() < path.size()) {
            path = tempStack;
        }
        return true;
    }
    else {
        g[v].visited = true;
        bool found = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
            vItrRange = adjacent_vertices(v, g);
        for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
            if (!g[*vItr].visited) {
                found = traverseDFSShortest(g, *vItr, end, path, tempStack);
                tempStack.pop();
            }
        }
        return found;
    }
}

// find shortest path for DFS
bool findShortestPathDFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path){
    clearVisited(g);
    stack<Graph::vertex_descriptor> temp;
    return traverseDFSShortest(g,start, goal, temp);
}
     
// search using BFS
bool findShortestPathBFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path){
    
    clearVisited(g);
    bool found = false;

    queue<Graph::vertex_descriptor> qVertices;
    qVertices.push(start);
    Graph::vertex_descriptor currV;
     
    while (!qVertices.empty() && !found) {
        currV = qVertices.front();
        qVertices.pop();
        if (!g[currV].visited) {
            g[currV].visited = true;
            if (currV == goal) {
                found = true;
            }
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
                vItrRange = adjacent_vertices(currV, g);
            for (Graph::adjacency_iterator vItr = vItrRange.first;
            vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    g[*vItr].pred = currV;
                    qVertices.push(*vItr);
                }
            }
        }

    }
    if (found) {
        currV = goal;
        while (currV != start) {
            path.push(currV);
            currV = g[currV].pred;
        }
        path.push(start);
    }
    return found;
}
   

