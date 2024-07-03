#pragma once

class MatrixIndexOutOfBounds {};

// Object to hold a large 2D matrix
template <typename T> 
class Matrix {
public:
	Matrix(int x, int y);

	T& at(unsigned int x, unsigned int y);

	void setAll(T value);

private:
	const int x_size;
	const int y_size;

	T* contents;

};

#include "Matrix.cpp""