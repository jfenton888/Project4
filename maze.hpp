//
//  maze.hpp
//  finalP
//
//  Created by Tamara Kahhale on 6/12/20.
//  Copyright © 2020 Tamara Kahhale. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_excecpt.h"
#include "matrix.h"
#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

//using namespace std;
//using namespace boost;

struct VertexProperties;
struct EdgeProperties;

//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
   pair<int,int> cell; // maze cell (x,y) value
   Graph::vertex_descriptor pred; // predecessor node
   int weight;
   bool visited;
   bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   int weight;
   bool visited;
   bool marked;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties, EdgeProperties> Graph;

class maze
{
    
private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze12 a
    
    matrix<bool> value;
    matrix<Graph::vertex_descriptor> vertices;
    //stack<Graph::vertex_descriptor> tempStack;

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
    Graph::vertex_descriptor getVertex(int i, int j){return vertices[i][j];};
    
    bool traverseDFSRecursive(Graph &g, Graph::vertex_descriptor v, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);

    bool findPathDFSRecursive(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);
      
    bool findPathDFSStack(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);
    
    bool traverseDFSShortest(Graph &g, Graph::vertex_descriptor v, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);
   
    bool findShortestPathDFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);
      
    bool findShortestPathBFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &path);
    
    void clearStack(stack<Graph::vertex_descriptor> &path);

};

#endif /* maze_hpp */


