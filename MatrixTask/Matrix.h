#pragma once
#include <vector>
#include <fstream>
#include <iostream>


// Abstract Matrix template class. 
// Based on STL Vectors.
template<typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> _vector;
	int _size;

public:
	// Default constructor.
	Matrix() : _size(0), _vector(std::vector<std::vector<T>>(0)) {}

	// Constructor with initial size and default values.
	Matrix(int size, const T& defaultValue)
	{
		try
		{
			SetSize(size, defaultValue);
		}
		catch (std::exception e)
		{
			std::cout << "RuntimeError: Matrix." << e.what() << std::endl;
		}
	}

	// Copying constructor.
	Matrix(const Matrix<T>& src) : _size(src._size), _vector(src._vector) {}

	// Moving constructor.
	Matrix(Matrix<T>&& src) noexcept : _size(src._size), _vector(std::move(src._vector)) {}


	// Changes Matrix's size. Allocates memory with default value 0.
	// Throws exception.
	void SetSize(int size, const T& defaultValue)
	{
		if (size < 0) throw std::exception("Matrix.SetSize: negative matrix size.");

		_size = size;

		_vector.resize(_size);
		for (int i = 0; i < _size; i++) _vector[i].resize(_size, defaultValue);
	}

	// Get actual Matrix's size.
	int GetSize() const { return _size; }


	// Adding Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Add(const Matrix<T>& right) = 0;

	// Subliming Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Sub(const Matrix<T>& right) = 0;

	// Multiplying Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Mul(const Matrix<T>& right) = 0;

	// Console stream input.
	virtual void Input() = 0;

	// Console stream output.
	virtual void Output() const = 0;

	// File stream input.
	virtual void Input(std::ifstream& fin) = 0;

	// File stream output.
	virtual void Output(std::ofstream& fout) const = 0;


	void operator=(const Matrix<T>& src)
	{
		_size = src._size;
		_vector = src._vector;
	}

	void operator=(Matrix<T>&& src) noexcept
	{
		_size = src._size;
		_vector = std::move(src._vector);
	}

	std::vector<T>& operator[](int i) {
		if (i < 0) throw std::exception("Matrix.operator[]: negative index.");
		if (i > _size - 1) throw std::exception("Matrix.operator[]: out of range.");

		return _vector[i];
	}

	const std::vector<T>& operator[](int i) const {
		if (i < 0) throw std::exception("Matrix.operator[]: negative index.");
		if (i > _size - 1) throw std::exception("Matrix.operator[]: out of range.");

		return _vector[i];
	}
};
