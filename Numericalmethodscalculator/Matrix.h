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
public:
	int col;
	int row;
	std::vector<Complex> data;


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
	Matrix& operator+();

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
	Matrix& operator-();

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




		// Intialiaze some matrix object
		// Add matrices
		// subtract matrices
		// multiply matrices
		// find information about matrices
		// eigen values and eigen basis
		// find a solution to the matrix as if solving a system of equations
		// get row and get col operations


};



Matrix operator+(Matrix left, const Matrix& right);

Matrix operator-(Matrix left, const Matrix& right);

Matrix operator*(Matrix left, const Matrix& right);

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

Matrix& Matrix::operator+=(const Matrix& addition) {
	// Check if matrices have the same dimensions
	if (row != other.row || col != other.col) {
		throw std::invalid_argument("Matrix dimensions must match for in-place addition");
	}
	// Perform in-place addition
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] += other.data[i];
	}
	return *this; // Return the current instance
}


Matrix& Matrix::operator+()  {
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& other) {

	// Check if matrices have the same dimensions
	if (row != other.row || col != other.col) {
		throw std::invalid_argument("Matrix dimensions must match for in-place addition");
	}
	// Perform in-place addition
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] -= other.data[i];
	}
	return *this; // Return the current instance

}


Matrix& Matrix::operator-() {
	// negate the values of the data
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] = -data[i];
	}
	return *this; // return the current instance
}


Matrix& Matrix::operator*=(const Matrix& other) {
	if (col != other.row) {
		throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
	}

	// Create a new vector for the resulting matrix data
	std::vector<Complex> newData(row * other.col, Complex());

	// Perform matrix multiplication
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < other.col; ++j) {
			Complex sum = Complex(); // Assuming default constructor creates a zero complex number
			for (size_t k = 0; k < col; ++k) {
				sum += data[i * col + k] * other.data[k * other.col + j];
			}
			newData[i * other.col + j] = sum;
		}
	}

	// Update the current matrix with the result
	col = other.col;
	data = std::move(newData);

	return *this;
}


Matrix& Matrix::operator~() {

}

Matrix operator+(Matrix left, const Matrix& right) {
	return left += right;
}

Matrix operator-(Matrix left, const Matrix& right) {
	return left -= right;
}

Matrix operator*(Matrix left, const Matrix& right) {
	return left *= right;
}



#endif 
