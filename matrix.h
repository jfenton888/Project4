//
//  matrix.h
//
//
//  Created by Tamara Kahhale on 5/28/20.
//  Copyright © 2020 Tamara Kahhale. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <vector>
#include "d_excecpt.h"

template <typename T>

class matrix {

public:
    matrix(int numRows = 1, int numCols = 1,const T& initVal = T()); // constructor
    std::vector<T>& operator[] (int i); // index operator
    matrix<T> &operator=(matrix<T> m);
    const std::vector<T>& operator[](int i) const;
    int rows() const; // returns number of rows
    int cols() const; // returns number of columns
    void resize(int numRows, int numCols); // changes the size of the matrix

private:
    int nRows, nCols; // number of rows and columns
    std::vector<std::vector<T> > mat; // matrix implemented as vector with nrows and ncolumns
};

template <typename T>
matrix<T>::matrix(int numRows, int numCols, const T& initVal):
nRows(numRows), nCols(numCols), mat(numRows, std::vector<T>(numCols, initVal))
{}

// non-constant version: provides general access to matrix elements
template <typename T>
std::vector<T>& matrix<T>::operator[] (int i)
{
    if (i < 0 || i >= nRows)
        throw indexRangeError("matrix: invalid row index", i, nRows);
   
    return mat[i];
}

// constant version, does not allow modification of a matrix element
template <typename T>
const std::vector<T>& matrix<T>::operator[] (int i) const
{
    if (i < 0 || i >= nRows)
        throw indexRangeError("matrix: invalid row index", i, nRows);

    return mat[i];
}


template <typename T>
matrix<T> &matrix<T>::operator=(matrix<T> m)
{
   for (int i = 0; i < rows(); i++)
      for (int j = 0; j < cols(); j++)
         (*this)[i][j] = m[i][j];
   
   return *this;
}

template <typename T>
int matrix<T>::rows() const
{
   return nRows;
}

template <typename T>
int matrix<T>::cols() const
{
   return nCols;
}

template <typename T>
void matrix<T>::resize(int numRows, int numCols)
{
   int i;
   
   // no size
   if (numRows == nRows && numCols == nCols)
      return;

   // new matrix size
   nRows = numRows;
   nCols = numCols;

   // resize rows
   mat.resize(nRows);

   // resize each row with columns
   for (i=0; i < nRows; i++)
      mat[i].resize(nCols);
}


#endif /* matrix_h */

