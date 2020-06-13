//
//  main.cpp
//  finalP
//
//  Created by Tamara Kahhale on 6/12/20.
//  Copyright © 2020 Tamara Kahhale. All rights reserved.
//


#include <iostream>
#include <iterator>
#include <algorithm>
#include "maze.hpp"

/* Pretty sure this function is necessary, but I am a little unsure how we should implement it
 figured I'd just include it anyways!

// intialize graph g using data, set start and end equal to the start and goal nodes
void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &goal, ifstream &fin)
{
    EdgeProperties e;
    
    int n, i, j;
    int startID, goalID;
    fin >> n;
    fin >> startID >> goalID;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
        if (i == startID)
            start = v;
        if (i == goalID)
            goal = v;
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        pair<Graph::edge_descriptor, bool> checkEdge = edge(i, j, g);
        // If an edge doesn't already exist
        if (!checkEdge.second)
            add_edge(i, j, e, g);
        // The edge exists but the newly discovered edge has a lower weight
        else if (g[checkEdge.first].weight < e.weight)
            g[checkEdge.first].weight = e.weight;
        else
            continue;
    }
}

 */
 
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
    // get edge between u and v
    pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
    
    // make sure the edge exists
    if (checkEdge.second != true) {
        cout << "The edge does not exist!" << endl;
    }
    
    // relax
    if (g[v].weight > g[u].weight + g[checkEdge.first].weight)
    {
        g[v].weight = g[u].weight + g[checkEdge.first].weight;
        g[v].pred = u;
    }
}

bool dijkstra(Graph &g, Graph::vertex_descriptor s) {

} // end of dijikstra


bool bellmanFord(Graph &g, Graph::vertex_descriptor s){

} // end bellmanFord






int main()
{
    
    std::cout << "goodbye";
}
