//
// Project by Jack Fenton
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#ifndef PROJECT4_HEAPV_H
#define PROJECT4_HEAPV_H

// Heap.h header file
//
// Implements min and max heaps and priority queue.
//
// This version is tailored to handle Boost graph objects.

//#define LargeValue 999999999
//#define SmallValue -999999999

#include <iostream>
#include <vector>

#include "boostGraph.h"
#include "d_except.h"

using namespace std;

template <typename T, typename U>
class heapV
{
private:
	vector<T> m_list;

public:
	heapV();
	
	void initializeMaxHeap(vector<T> a_list, U &a_graph);
	void initializeMinHeap(vector<T> a_list, U &a_graph);
	
	void maxHeapify(int a_index, int a_heapSize, U &a_graph);
	void buildMaxHeap(int a_heapSize, U &a_graph);
	
	void minHeapify(int a_index, int a_heapSize, U &a_graph);
	void buildMinHeap(int a_heapSize, U &a_graph);
	
	void heapsort(int a_heapSize, U &a_graph);
	
	int parent(int i) {return (i+1)/2-1;}  // Given a node in a heap, return the index of the parent
	// Map vertex indices from 0-based to 1-based and
	int left(int i) {return 2*(i+1)-1;}    // Given a node in a heap, return the left child
	// Map vertex indices from 0-based to 1-based and back
	int right(int i) {return 2*(i+1);}     // Given a node in a heap, return the right child
	
	T &getItem(int a_index) {return m_list[a_index];}      // Return a reference to the ith item in the heap
	int getIndex(T &a_key);
	int size() {return (int) m_list.size();}
	
	T getMaxHeapMaximum();
	T getMinHeapMinimum();
	
	T extractMaxHeapMaximum(U &a_graph);
	T extractMinHeapMinimum(U &a_graph);
	
	void maxHeapIncreaseKey(int a_index, U &a_graph);
	void minHeapDecreaseKey(int a_index, U &a_graph);
	
	void maxHeapInsert(T a_key, U &a_graph);
	void minHeapInsert(T a_key, U &a_graph);
	
};



#endif //PROJECT4_HEAPV_H
