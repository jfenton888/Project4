//
// Project by Jack Fenton
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-18.
//

#ifndef PROJECT4_GLOBAL_H
#define PROJECT4_GLOBAL_H

#include <iostream>
#include <stack>

#include <boost/graph/adjacency_list.hpp>
#include "boostGraph.h"

using namespace boost;
using namespace std;

void clearVisited(Graph &a_graph);

void setNodeWeights(Graph &a_graph, int a_value);

void clearMarked(Graph &a_graph);

void clearStack(stack<Graph::vertex_descriptor> &a_path);


void generateStack(Graph &a_graph,
				   Graph::vertex_descriptor a_start,
				   Graph::vertex_descriptor a_goal,
				   stack<Graph::vertex_descriptor> &a_path);


void relax(Graph &a_graph,
		   Graph::vertex_descriptor a_source,
		   Graph::vertex_descriptor a_target);

void initializeSingleSource(Graph &a_graph, Graph::vertex_descriptor a_start);

int isInt(string a_prompt, int a_min, int a_max);

//class can be used to find the heuristic cost from any node the goal node,
//whose vertex is given in constructor
//3 member functions provide different types of distance calculations, based on ability to move in grid
//for an object, h, of this class, the distance to the goal from vertex can be found by calling h.ManDist(graph, vertex)
class heuristicCost
{
private:
	double m_goalY;
	double m_goalX;
public:
	heuristicCost(Graph &a_graph, Graph::vertex_descriptor a_goal): m_goalY(a_graph[a_goal].cell.first),
																	m_goalX(a_graph[a_goal].cell.second){};
	
	//Manhattan distance, where movement is only possible in 4 directions
	double ManDist(Graph &a_graph, Graph::vertex_descriptor a_currV)
	{
		return (abs(m_goalY-a_graph[a_currV].cell.first) + abs(m_goalX-a_graph[a_currV].cell.second));
	}
	//Diagonal distance, where movement is possible in 8 directions
	double DiagDist(Graph &a_graph, Graph::vertex_descriptor a_currV)
	{
		return (min(abs(m_goalY-a_graph[a_currV].cell.first), abs(m_goalX-a_graph[a_currV].cell.second)));
	}
	//Euclidean distance, where direction of movement is free
	double EuclidDist(Graph &a_graph, Graph::vertex_descriptor a_currV)
	{
		return (sqrt(pow(m_goalY - a_graph[a_currV].cell.first, 2) + pow(m_goalX - a_graph[a_currV].cell.second, 2)));
	}
};



template <typename T>
void StackDebug(stack<T> a_stack)
{
	vector<T> debugVector = vector<T>();
	while (!a_stack.empty())
	{
		T top = a_stack.top();
		debugVector.push_back(top);
		a_stack.pop();
	}
	
	// stack, read from top down, is reversed relative to its creation (from bot to top)
	reverse(debugVector.begin(), debugVector.end());
	for(const auto& it : debugVector)
	{
		cout << it << " ";
	}
}

template <typename T>
void PrintStack(stack<T> a_stack)
{
	T top;
	if (!a_stack.empty())
	{
		top = a_stack.top();
		cout << top;
		a_stack.pop();
		
		while (!a_stack.empty())
		{
			top = a_stack.top();
			cout << " -> " << top;
			a_stack.pop();
			
		}
		cout << endl;
	}
}


#endif //PROJECT4_GLOBAL_H
