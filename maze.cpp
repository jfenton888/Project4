//
//  maze.cpp
//  finalP
//
//  Created by Tamara Kahhale on 6/12/20.
//  Copyright © 2020 Tamara Kahhale. All rights reserved.
//


#include "maze.hpp"
#include <boost/graph/adjacency_list.hpp>


// initialize a maze by reading values from fin
maze::maze(ifstream &fin)
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
   
    vertices.resize(rows, cols);
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
void maze::print(int goalI, int goalJ, int currI, int currJ)
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


// return the value stored at the (i,j) entry in the maze, show whether it is legal to go to cell (i,j)
bool maze::isLegal(int i, int j)
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

// create a graph g that represents the legal moves in the maze m
void maze::mapMazeToGraph(Graph &g)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            if (isLegal(i, j)) {
                Graph::vertex_descriptor v = add_vertex(g);
                g[v].cell = pair<int, int>(i, j);
                vertices[i][j] = v;
                g[v].pred = 1;
                if (i != 0 && value[i - 1][j]) {
                    add_edge(vertices[i - 1][j], v, g);
                }
                if (j != 0 && value[i][j - 1]) {
                    add_edge(vertices[i][j - 1], v, g);
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
   

