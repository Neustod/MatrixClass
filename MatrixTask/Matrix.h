#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>


// Abstract Matrix template class. 
// Based on STL Vectors.
template<typename T>
class Matrix : public std::vector<std::vector<T>>
{
private:
	T _defaultValue;

public:
	// Constructor with initial size and default values.
	Matrix(const T& defaultValue, size_t size = 0) : std::vector<std::vector<T>>(std::vector<std::vector<T>>(size, std::vector<T>(size, defaultValue))), _defaultValue(defaultValue) {}

	Matrix(T&& defaultValue, size_t size = 0) : std::vector<std::vector<T>>(std::vector<std::vector<T>>(size, std::vector<T>(size, defaultValue))), _defaultValue(defaultValue) {}

	// Copying constructor.
	Matrix(const Matrix<T>& src) : std::vector<std::vector<T>>(src), _defaultValue(src._defaultValue) {}

	// Moving constructor.
	Matrix(Matrix<T>&& src) noexcept : std::vector<std::vector<T>>(src), _defaultValue(std::move(src._defaultValue)) {}

public:
	void operator=(const Matrix<T>& src)
	{
		_defaultValue = src._defaultValue;
		std::vector<std::vector<T>>::operator=(src);
	}

	void operator=(Matrix<T>&& src) noexcept
	{
		_defaultValue = std::move(src._defaultValue);
		std::vector<std::vector<T>>::operator=(src);
	}

public:
	// Adding Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Add(const Matrix<T>& right) 
	{
		for (size_t row = 0; row < this->size(); row++)
		{
			for (size_t col = 0; col < this->size(); col++)
			{
				(*this)[row][col] += right[row][col];
			}
		}
	};

	// Subliming Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Sub(const Matrix<T>& right) 
	{
		for (size_t row = 0; row < this->size(); row++)
		{
			for (size_t col = 0; col < this->size(); col++)
			{
				(*this)[row][col] -= right[row][col];
			}
		}
	};

	// Multiplying Matrixes.
	// Result will be stored in the current Matrix object.
	virtual void Mul(const Matrix<T>& right) 
	{
		size_t matrixSize = this->size();
		Matrix<T> buffer(_defaultValue, matrixSize);

		for (size_t row = 0; row < matrixSize; row++)
		{
			for (size_t col = 0; col < matrixSize; col++)
			{
				for (size_t inner = 0; inner < matrixSize; inner++)
				{
					buffer[row][col] += (*this)[row][inner] * right[inner][col];
				}
			}
		}

		this->operator=(std::move(buffer));
	};

public:
	std::string ToString() const 
	{
		using namespace std;

		std::string result{ "" };
		
		for (size_t row = 0; row < this->size(); row++)
		{
			for (size_t col = 0; col < this->size(); col++)
			{
				result += to_string((*this)[row][col]);
				result += ":";
			}
			result += "\n";
		}

		return result;
	};

	// File stream input.
	virtual void Input(std::ifstream& fin) 
	{
		size_t size{ 0 };
		
		fin >> size;
		
		Matrix<T>& buffer = *new Matrix<T>{_defaultValue, size};

		for (size_t row = 0; row < this->size(); row++) 
		{
			for (size_t col = 0; col < this->size(); col++)
			{
				fin >> buffer[row][col];
			}
		}

		*this = std::move(buffer);
	}

	// File stream output.
	virtual void Output(std::ofstream& fout) const 
	{
		fout << this->size();

		for (size_t row = 0; row < this->size(); row++)
		{
			for (size_t col = 0; col < this->size(); col++)
			{
				fout << (*this)[row][col];
			}
		}
	}
};