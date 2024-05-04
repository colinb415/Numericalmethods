#ifndef MATRIX_
#define MATRIX_
#include<string>
#include"Complex.h"
#include<stdexcept>
#include<iostream>
#include<sstream>
#include<vector>

/**
*
* @class Matrix that does matrix math
*/

class Matrix {
private:
	int col;
	int row;
	std::vector<Complex> data;

public:

	Matrix(int _row, int _col, const std::vector<Complex>& _data) {
		row = _row;
		col = _col;
		if (row * col != data.size()) {
			throw std::invalid_argument("data does not match the sie of matrix");
		}
		data = _data;
	};

	/**
	* Operator adding matrices
	* @param ref to const matrix
	* @return ref to this Matrix
	*
	*/
	Matrix& operator+=(const Matrix& addition);

	/**
	* Operator returing object
	* @param nothing
	* @return ref to this Matrix
	*
	*/
	Matrix& operator+() const;

	/**
	* Operator subtracting matrices
	* @param ref to const matrix
	* @return ref to this Matrix
	*
	*/
	Matrix& operator-=(const Matrix& subtraction);

	/**
	* Operator returing negated object
	* @param nothing
	* @return ref to this Matrix
	*
	*/
	Matrix& operator-() const;

	/**
	* Operator multiplying two matrices
	* @param ref to const matrix
	* @return ref to this Matrix
	*
	*/
	Matrix& operator*=(const Matrix& multiply);

	/**
	* Operator returing inverse of matrix if it excists
	* @param nothing
	* @return ref to this Matrix
	*
	*/
	Matrix& operator~() const;

	Matrix& qr() const;

	Matrix& shur_decomp() const;

	Matrix&





		// Intialiaze some matrix object
		// Add matrices
		// subtract matrices
		// multiply matrices
		// find information about matrices
		// eigen values and eigen basis
		// find a solution to the matrix as if solving a system of equations
		// get row and get col operations


};

/**
* bool operator that checks if two matrices have the same dimesnions
*/
friend bool operator!=(const Matrix& one, const Matrix& two) {
	if (one.row == two.row && one.col == two.col) {
		return false
	}
	return true
}

/**
* bool operator that checks if two matrices do not have the same dimesnions
*/
friend bool operator==(const Matrix& one, const Matrix& two) {
	return !(one != two)
}






#endif 
