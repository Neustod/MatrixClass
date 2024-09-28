#pragma once
#include "Matrix.h"

// Matrix for all types that have arithmetic operations overload.
template<typename T>
class SimpleMatrix : public Matrix<T>
{
public:
	// Default constructor.
	SimpleMatrix() {}

	// Constructor with initial size and default values.
	SimpleMatrix(int size, const T& defaultValue) : Matrix<T>(size, defaultValue) {}

	// Copy constructor.
	SimpleMatrix(const SimpleMatrix& src) : Matrix<T>(src) {}

	// Move constructor.
	SimpleMatrix(SimpleMatrix&& src) noexcept : Matrix<T>(src) {}


	// Addition method.
	void Add(const Matrix<T>& right)
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				(*this)[row][col] += right[row][col];
			}
		}
	}

	// Subliming method.
	void Sub(const Matrix<T>& right) 
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				(*this)[row][col] -= right[row][col];
			}
		}
	}

	// Multiplication method.
	void Mul(const Matrix<T>& right)
	{
		int size = Matrix<T>::GetSize();
		if (size == 0) return;

		std::vector<T> tmpRow(size, 0);

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				tmpRow[col] = 0;

				for (int inner = 0; inner < size; inner++)
				{
					tmpRow[col] += (*this)[row][inner] * right[inner][col];
				}
			}
			for (int col = 0; col < size; col++) (*this)[row][col] = tmpRow[col];
		}
	}

	// Addition method.
	static SimpleMatrix<T>& Add(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right)
	{
		SimpleMatrix<T>* result = new SimpleMatrix<T>{ left };
		result->Add(right);
		return *result;
	}

	// Subliming method.
	static SimpleMatrix<T>& Sub(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right)
	{
		SimpleMatrix<T>* result = new SimpleMatrix<T>{ left };
		result->Sub(right);
		return *result;
	}

	// Multiplication method.
	static SimpleMatrix<T>& Mul(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right)
	{
		SimpleMatrix<T>* result = new SimpleMatrix<T>{ left };
		result->Mul(right);
		return *result;
	}


	// Enter values from console stream.
	void Input() 
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				std::cin >> (*this)[row][col];
			}
		}
	}

	// Output values to console stream.
	void Output() const 
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				std::cout << (*this)[row][col] << " ";
			}
			std::cout << std::endl;
		}
	}

	// Enter values from file.
	void Input(std::ifstream& fin) 
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				fin >> (*this)[row][col];
			}
		}
	}

	// Output values to file.
	void Output(std::ofstream& fout) const 
	{
		int size = Matrix<T>::GetSize();

		for (int row = 0; row < size; row++)
		{
			for (int col = 0; col < size; col++)
			{
				fout << (*this)[row][col] << " ";
			}
			fout << std::endl;
		}
	}


	void operator=(const SimpleMatrix<T>& src)
	{
		Matrix<T>(src);
	}

	void operator=(SimpleMatrix<T>&& src) noexcept
	{
		Matrix<T>(src);
	}
};

