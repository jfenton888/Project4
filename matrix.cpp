//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//


//#include <iostream>
//#include <vector>
//#include "d_except.h"
//
//#include "matrix.h"
//
//using namespace std;
//
//
//template <typename T>
//matrix<T>::matrix(int a_nRows, int a_nCols, const T& a_initVal):
//																m_nRows(a_nRows),
//																m_nCols(a_nCols),
//																mat(a_nRows, vector<T>(a_nCols, a_initVal))
//																{}
//
//
// non-constant version: provides general access to matrix elements
//template <typename T>
//vector<T>& matrix<T>::operator[] (int a_index)
//{
//	if (a_index < 0 || a_index >= m_nRows)
//		throw indexRangeError("matrix: invalid row index", a_index, m_nRows);
//
//	return mat[a_index];
//}
//
//
//// constant version, does not allow modification of a matrix element
//template <typename T>
//const vector<T>& matrix<T>::operator[] (int a_index) const
//{
//	if (a_index < 0 || a_index >= m_nRows)
//		throw indexRangeError("matrix: invalid row index", a_index, m_nRows);
//
//	return mat[a_index];
//}
//
//
//template <typename T>
//matrix<T> &matrix<T>::operator=(matrix<T> a_mat)
//{
//	for (int i = 0; i < rows(); i++)
//		for (int j = 0; j < cols(); j++)
//			(*this)[i][j] = a_mat[i][j];
//
//	return *this;
//}
//
//
//template <typename T>
//void matrix<T>::resize(int a_nRows, int a_nCols)
//{
//
//	// no size
//	if (a_nRows == m_nRows && a_nCols == m_nCols)
//		return;
//
//	// new matrix size
//	m_nRows = a_nRows;
//	m_nCols = a_nCols;
//
//	// resize rows
//	mat.resize(m_nRows);
//
//	// resize each row with columns
//	for (int i=0; i < m_nRows; i++)
//		mat[i].resize(m_nCols);
//}
//
