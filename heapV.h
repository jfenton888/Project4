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
	vector<T> list;

public:
	heapV();
	
	void initializeMaxHeap(vector<T> list2, U &g);
	void initializeMinHeap(vector<T> list2, U &g);
	
	void maxHeapify(int i, int heapSize, U &g);
	void buildMaxHeap(int heapSize, U &g);
	
	void minHeapify(int i, int heapSize, U &g);
	void buildMinHeap(int heapSize, U &g);
	
	void heapsort(int heapSize, U &g);
	
	int parent(int i) {return (i+1)/2-1;}  // Given a node in a heap, return the index of the parent
	// Map vertex indices from 0-based to 1-based and
	int left(int i) {return 2*(i+1)-1;}    // Given a node in a heap, return the left child
	// Map vertex indices from 0-based to 1-based and back
	int right(int i) {return 2*(i+1);}     // Given a node in a heap, return the right child
	
	T &getItem(int i) {return list[i];}      // Return a reference to the ith item in the heap
	int getIndex(T &key);
	int size() {return (int) list.size();}
	
	T getMaxHeapMaximum();
	T getMinHeapMinimum();
	
	T extractMaxHeapMaximum(U &g);
	T extractMinHeapMinimum(U &g);
	
	void maxHeapIncreaseKey(int i, U &g);
	void minHeapDecreaseKey(int i, U &g);
	
	void maxHeapInsert(T key, U &g);
	void minHeapInsert(T key, U &g);
	
};



#endif //PROJECT4_HEAPV_H
