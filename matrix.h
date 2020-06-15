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

class matrix
{
private:
    // number of rows and columns
    int m_nRows;
    int m_nCols;
    vector<vector<T>> mat; // matrix implemented as vector with nRows and nColumns


public:
    matrix(int a_nRows = 1, int a_nCols = 1,const T& a_initVal = T()):m_nRows(a_nRows),
                                                                      m_nCols(a_nCols),
                                                                      mat(a_nRows, vector<T>(a_nCols, a_initVal))
    {}; // constructor
    
    vector<T>& operator[] (int a_index) // index operator
    {
        if (a_index < 0 || a_index >= m_nRows)
            throw indexRangeError("matrix: invalid row index", a_index, m_nRows);
    
        return mat[a_index];
    };
    
    const vector<T>& operator[](int a_index) const
    {
        if (a_index < 0 || a_index >= m_nRows)
            throw indexRangeError("matrix: invalid row index", a_index, m_nRows);
        
        return mat[a_index];
    };
    
    
    matrix<T> &operator=(matrix<T> a_mat)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                (*this)[i][j] = a_mat[i][j];
    
        return *this;
    };
    
    int rows() const {return m_nRows;}; // returns number of rows
    int cols() const {return m_nCols;}; // returns number of columns
    
    void resize(int a_nRows, int a_nCols) // changes the size of the matrix
    {
    
        // no size
        if (a_nRows == m_nRows && a_nCols == m_nCols)
            return;
    
        // new matrix size
        m_nRows = a_nRows;
        m_nCols = a_nCols;
    
        // resize rows
        mat.resize(m_nRows);
    
        // resize each row with columns
        for (int i=0; i < m_nRows; i++)
            mat[i].resize(m_nCols);
    };
    
};



#endif //PROJECT4_MATRIX_H
