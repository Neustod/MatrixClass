#pragma once
#include "Matrix.h"

template<typename T>
class SimpleMatrix : public Matrix<T>
{
public:
	SimpleMatrix() {}
	SimpleMatrix(int size, const T& defaultValue) : Matrix<T>(size, defaultValue) {}
	SimpleMatrix(const SimpleMatrix& src) : Matrix<T>(src) {}

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

	static SimpleMatrix<T>& Add(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right);
	static SimpleMatrix<T>& Mul(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right);

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
};

