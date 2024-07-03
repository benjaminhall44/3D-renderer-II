#pragma once
#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix(int x, int y) : x_size(x), y_size(y) {
	contents = new T[x_size * y_size];
}

template <typename T>
T& Matrix<T>::at(unsigned int x, unsigned int y) {
	if (x < x_size && y < y_size) {
		return contents[x_size * y + x];
	}
	else {
		throw(MatrixIndexOutOfBounds());
	}
}

template <typename T>
void Matrix<T>::setAll(T value) {
	int size = x_size * y_size;
	for (int i = 0; i < size; i++) {
		contents[i] = value;
	}
}
