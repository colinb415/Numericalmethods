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

	Matrix& operator=(const Matrix& other) {
		if (this == &other) {
			return *this; // Return the current instance (no-op)
		}

		if (this->col != other.col || this->row != other.col) {
			throw invalid_argument("The matrices are not the same size so you can not assign");
		}

		this->data = other.data;
		return *this;
	}

	Complex& at(int row, int col) {
		return data[row * cols + col];
	}

	const Complex& at(int row, int col) const {
		return data[row * cols + col];
	}

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

	void qr_decomposition() const;

	std::vector<Complex> qralgorithm();

	Matrix& shur_decomp() const;

	/**
	* Returns the transpose of the matrix
	* @param nothing
	* @return Matrix
	*/
	Matrix& t();




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

void qr_decomposition(Matrix& Q, Matrix& R){
	// Initialize Q as the identity matrix and R as the input matrix
	Q = Matrix(rows, cols);
	R = *this;

	// Initialize Q as an identity matrix
	for (int i = 0; i < rows; i++) {
		Q.at(i, i) = Complex(1, 0);
	}

	// Perform QR decomposition using the Gram-Schmidt process
	for (int k = 0; k < cols; k++) {
		// Calculate the norm of the current column
		Complex norm(0, 0);
		for (int i = 0; i < rows; i++) {
			norm = norm + (R.at(i, k) * R.at(i, k).conjugate());
		}
		norm = Complex(std::sqrt(norm.real), 0);

		// Normalize the current column and store it in Q
		for (int i = 0; i < rows; i++) {
			Q.at(i, k) = R.at(i, k) / norm;
		}

		// Orthogonalize the remaining columns
		for (int j = k + 1; j < cols; j++) {
			Complex dotProduct(0, 0);
			for (int i = 0; i < rows; i++) {
				dotProduct = dotProduct + (Q.at(i, k) * R.at(i, j));
			}

			// Subtract the projection of the j-th column on the k-th column
			for (int i = 0; i < rows; i++) {
				R.at(i, j) = R.at(i, j) - (dotProduct * Q.at(i, k));
			}
		}
	}

}

std::vector<Complex> Matrix::qralgorithm() {
	// Check if the matrix is square
	if (rows != cols) {
		std::cerr << "Matrix must be square for QR algorithm." << std::endl;
		return {};
	}

	// Define convergence tolerance and maximum iterations
	const double tolerance = 1e-9;
	int maxIterations = 1000;

	// Copy the original matrix
	Matrix currentMatrix = *this;

	// Iteratively perform QR decomposition and update the matrix
	for (int iter = 0; iter < maxIterations; iter++) {
		// Perform QR decomposition
		Matrix Q(rows, cols);
		Matrix R(rows, cols);
		currentMatrix.qrDecomposition(Q, R);

		// Update the matrix: currentMatrix = R * Q
		Matrix newMatrix(rows, cols);
		
		newMatrix = R * Q;

		// Check for convergence
		bool converged = true;
		for (int i = 0; i < rows - 1; i++) {
			for (int j = i + 1; j < cols; j++) {
				if (newMatrix.at(i, j).abs() > tolerance) {
					converged = false;
					break;
				}
			}
		}

		// Update the matrix
		currentMatrix = newMatrix;

		// If converged, break the loop
		if (converged) {
			break;
		}
	}

	// Extract the eigenvalues from the diagonal of the final matrix
	std::vector<Complex> eigenvalues;
	for (int i = 0; i < rows; i++) {
		eigenvalues.push_back(currentMatrix.at(i, i));
	}

	return eigenvalues;
	 
}

#endif 
