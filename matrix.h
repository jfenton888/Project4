//
// Project by Jack Fenton, Jonathan Hsin, and Tamara Kahhale
// Northeastern University Department of Computer and Electrical Engineering
// EECE2560 Introduction to Engineering Algorithms
// Project begun on 2020-06-12.
//

#ifndef PROJECT4_MATRIX_H
#define PROJECT4_MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class matrix {
private:
    // number of rows and columns
    int m_nRows;
    int m_nCols;
    vector<vector<T>> mat; // matrix implemented as vector with nRows and nColumns


public:
    matrix(int a_nRows = 1, int a_nCols = 1,const T& a_initVal = T()); // constructor
    
    //vector<T>& operator[] (int a_index); // index operator
    //matrix<T> &operator=(matrix<T> a_mat);
    //const vector<T>& operator[](int a_index) const;
    
    int rows() const {return m_nRows;}; // returns number of rows
    int cols() const {return m_nCols;}; // returns number of columns
    
    void resize(int a_nRows, int a_nCols); // changes the size of the matrix
    
};



#endif //PROJECT4_MATRIX_H
