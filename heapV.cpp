//
// Project by Jack Fenton
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#include <iostream>
#include <vector>

#include "boostGraph.h"
#include "d_except.h"
#include "heapV.h"


template <typename T, typename U>
heapV<T,U>::heapV()
// Construct an empty heap.
{
}

template <typename T, typename U>
int heapV<T,U>::getIndex(T &a_key)
// Return the index of the item key in the heap.  Assumes each item is unique.
{
	for (int i = 0; i < size(); i++)
		if (getItem(i) == a_key)
			return i;
	throw rangeError("key not found in heap::getIndex");
}


template <typename T, typename U>
void heapV<T,U>::initializeMaxHeap(vector<T> a_list, U &a_graph)
// Initialize a max heap from values in list2.
{
	for (int i = 0; i < a_list.size(); i++)
		m_list.push_back(a_list[i]);
	
	buildMaxHeap(size(),a_graph);
}

template <typename T, typename U>
void heapV<T,U>::initializeMinHeap(vector<T> a_list, U &a_graph)
// Initialize a min heap from values in list2.
{
	for (int i = 0; i < a_list.size(); i++)
		m_list.push_back(a_list[i]);
	
	buildMinHeap(size(),a_graph);
}


template <typename T, typename U>
void heapV<T,U>::maxHeapify(int a_index, int a_heapSize, U &a_graph)
// Assumes the binary trees rooted at left(i) and right(i) are max heaps, but node i
// might be smaller than its children, violating the max-heap property.  The function
// lets the value at i float down so the subtree rooted at i obeys the max heap property.
{
	int l = left(a_index);
	int r = right(a_index);
	int largest;
	
	// Set largest = the largest of the two children and i (the root)
	
	if (l <= a_heapSize-1 && a_graph[m_list[l]].weight > a_graph[m_list[a_index]].weight)
		largest = l;
	else
		largest = a_index;
	
	if (r <= a_heapSize-1 && a_graph[m_list[r]].weight > a_graph[m_list[largest]].weight)
		largest = r;
	
	// If the root isn't the largest, swap the root with the largest child and recurse.
	if (largest != a_index)
	{
		swap(m_list[a_index], m_list[largest]);
		maxHeapify(largest, a_heapSize, a_graph);
	}
}

template <typename T, typename U>
void heapV<T,U>::minHeapify(int a_index, int a_heapSize, U &a_graph)
// Assumes the binary trees rooted at left(i) and right(i) are min heaps, but node i
// might be larger than its children, violating the min-heap property.  The function
// lets the value at i float down so the subtree rooted at i obeys the min heap property.
{
	int l = left(a_index);
	int r = right(a_index);
	int smallest;
	
	// Set smallest = the smallest of the two children and i (the root)
	
	if (l <= a_heapSize-1 && a_graph[m_list[l]].weight < a_graph[m_list[a_index]].weight)
		smallest = l;
	else
		smallest = a_index;
	
	if (r <= a_heapSize-1 && a_graph[m_list[r]].weight < a_graph[m_list[smallest]].weight)
		smallest = r;
	
	// If the root isn't the smallest, swap the root with the smallest child and recurse.
	if (smallest != a_index)
	{
		//cout << "Swapping " << list[i] << " and " << list[smallest] << endl;
		swap(m_list[a_index], m_list[smallest]);
		minHeapify(smallest, a_heapSize, a_graph);
	}
}

template <typename T, typename U>
void heapV<T,U>::buildMaxHeap(int a_heapSize, U &a_graph)
// Transforms an unordered list into a heap bottom-up.  The second half of a list
// represents leaves of the tree, so each element represents a one-element heap.
// This function builds a heap by running minHeapify on the first non-leaf, and
// works up to the first element.  Max indices from starting at 0 to 1.
{
	for (int index = (size()+1)/2; index >= 0; index--)
		maxHeapify(index, a_heapSize, a_graph);
}

template <typename T, typename U>
void heapV<T,U>::buildMinHeap(int a_heapSize, U &a_graph)
// Transforms an unordered list into a heap bottom-up.  The second half of a list
// represents leaves of the tree, so each element represents a one-element heap.
// This function builds a heap by running minHeapify on the first non-leaf, and
// works up to the first element.  Max indices from starting at 0 to 1.
{
	for (int index = (size()+1)/2; index >= 0; index--)
		minHeapify(index, a_heapSize, a_graph);
}

template <typename T, typename U>
T heapV<T,U>::getMinHeapMinimum()
// Return the smallest item in a min heap.
{
	return m_list[0];
}

template <typename T, typename U>
T heapV<T,U>::getMaxHeapMaximum()
// Return the largest item in a max heap
{
	return m_list[0];
}

template <typename T, typename U>
T heapV<T,U>::extractMinHeapMinimum(U &a_graph)
// Return the smallest item in a min heap and remove it.
{
	if (size() < 1)
		throw rangeError("heap too small in extractMinHeapMinimum");
	T min = m_list[0];
	m_list[0] = m_list[size()-1];
	//cout << "Swapping " << list[0] << " to the top" << endl;
	m_list.resize(size()-1);
	minHeapify(0,size(), a_graph);
	return min;
}

template <typename T, typename U>
T heapV<T,U>::extractMaxHeapMaximum(U &a_graph)
// Return the largest item in a max heap and remove it.
{
	if (size() < 1)
		throw rangeError("heap too small in extractMaxHeapMaximum");
	T max = m_list[0];
	m_list[0] = m_list[size()-1];
	m_list.resize(size()-1);
	maxHeapify(0,size(), a_graph);
	return max;
}

template <typename T, typename U>
void heapV<T,U>::maxHeapIncreaseKey(int a_index, U &a_graph)
// Assumes the item at position i has had its value increased.  Rebuilds the max-heap by performing
// an insertion sort that finds the new item's correct location in the list.
{
	while (a_index > 0 && a_graph[m_list[parent(a_index)]].weight < a_graph[m_list[a_index]].weight)
	{
		swap(m_list[a_index], m_list[parent(a_index)]);
		a_index = parent(a_index);
	}
}

template <typename T, typename U>
void heapV<T,U>::minHeapDecreaseKey(int a_index, U &a_graph)
// Assumes the item at position i has had its value decreased.  Rebuilds the min-heap by performing
// an insertion sort that finds the new item's correct location in the list.
{
	// cout << i << " " << list[i] << " " << list[parent(i)] << endl;
	
	while (a_index > 0 && a_graph[m_list[parent(a_index)]].weight > a_graph[m_list[a_index]].weight)
	{
		swap(m_list[a_index], m_list[parent(a_index)]);
		a_index = parent(a_index);
	}
}

template <typename T, typename U>
void heapV<T,U>::maxHeapInsert(T a_key, U &a_graph)
// Adds a new leaf then calls maxHeapIncreaseKey to move the key to the correct location.
{
	m_list.push_back(a_key);
	maxHeapIncreaseKey(size()-1, a_graph);
}

template <typename T, typename U>
void heapV<T,U>::minHeapInsert(T a_key, U &a_graph)
// Adds a new leaf then calls minHeapDecreaseKey to move the key to the correct location.
{
	m_list.push_back(a_key);
	minHeapDecreaseKey(size()-1, a_graph);
}


template <typename T, typename U>
void heapV<T,U>::heapsort(int a_heapSize, U &a_graph)
// Given an unordered list, first builds a max-heap.  The maximum
// element is now in the first position, and it is swapped into the
// last position.  The heap size is reduced by one, which might cause
// element 1 to violate the max-heap property.  The call to maxHeapify
// restores the max-heap property, and the functions repeats.
{
	buildMaxHeap(a_heapSize, a_graph);
	
	for (int index = size()-1; index >= 0; index--)
	{
		// cout << "Position: " << i << endl;
		// cout << "Swap" << endl;
		
		swap(m_list[0],m_list[index]);
		a_heapSize--;
		
		// cout << "maxHeapify" << endl;
		maxHeapify(0,a_heapSize,a_graph);
	}
}

template <typename T, typename U>
ostream &operator<<(ostream &ostr, heapV<T,U> &a_heap)
// Print all information about the graph.
{
	cout << "------------------------------------------------" << endl;
	for (int index = 0; index < a_heap.size(); index++)
		cout << a_heap.getItem(index);
	
	cout << endl;
	
	return ostr;
}