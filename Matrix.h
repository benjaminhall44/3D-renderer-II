#pragma once

#include "rect.h"

class MatrixIndexOutOfBounds {};

template <typename T> 
class Matrix {
public:
	Matrix(int x, int y) : x_size(x), y_size(y) {
		contents = new T[x_size * y_size];
	}
	Matrix(math::rect size) : Matrix(size.x, size.y) {};

	T& at(unsigned int x, unsigned int y) {
		if (x < x_size && y < y_size) {
			return contents[x_size * y + x];
		}
		else {
			throw(MatrixIndexOutOfBounds());
		}
	}

	void setAll(T value) {
		for (int x = 0; x < x_size; x++) {
			for (int y = 0; y < y_size; y++) {
				at(x, y) = value;
			}
		}
	}

	math::rect size() const {
		return math::rect(x_size, y_size);
	}

private:
	const int x_size;
	const int y_size;

	T* contents;

};