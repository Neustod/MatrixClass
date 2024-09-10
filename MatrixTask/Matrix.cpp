#include "Matrix.h"
#include "Randomizer.h"
#include <exception>
#include <iostream>

// Constructors

Matrix::Matrix(int _size)
{
	vector = std::vector<std::vector<int>>(0);

	try {
		SetSize(_size);
	}
	catch (std::exception e) {
		std::cout << "RuntimeError: Matrix." << e.what() << std::endl;
	}
}

Matrix::Matrix(const Matrix& src) : size(src.size), vector(src.vector) {}


// Getters and setters

void Matrix::SetSize(int _size)
{
	if (_size < 0) throw std::exception("Matrix.SetSize: negative matrix size.");

	size = _size;

	vector.resize(size);
	for (int i = 0; i < size; i++) vector[i].resize(size, 0);
}

int Matrix::GetSize() const { return size; }


// Randomizer's wrapper function

void Matrix::Randomize(int leftBoard, int rightBoard)
{
	for (size_t row = 0; row < size; row++)
		for (size_t col = 0; col < size; col++)
			vector[row][col] = Randomizer::Instance().RandInt(leftBoard, rightBoard);
}


// Matrix operation methods

void Matrix::Add(const Matrix& right)
{
	if (size != right.GetSize()) throw std::exception("MatrixCalculator.Add: different matrix sizes.");

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			vector[row][col] += right[row][col];
		}
	}
}

void Matrix::Sub(const Matrix& right) {
	if (size != right.GetSize()) throw std::exception("MatrixCalculator.Add: different matrix sizes.");

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			vector[row][col] -= right[row][col];
		}
	}
}

void Matrix::Mul(const Matrix& right) {
	if (size != right.GetSize()) throw std::exception("MatrixCalculator.Mul: different matrix sizes.");

	int rowSum = 0;
	int* tmpRow = new int[size];

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			rowSum = 0;

			for (int inner = 0; inner < size; inner++)
			{
				rowSum += vector[row][inner] * right[inner][col];
			}

			tmpRow[col] = rowSum;
		}
		for (int col = 0; col < size; col++) vector[row][col] = tmpRow[col];
	}

	delete[] tmpRow;
}

Matrix& Matrix::Add(const Matrix& left, const Matrix& right) 
{
	Matrix* result = new Matrix{ left };

	try {
		result->Add(right);
	}
	catch(std::exception e){
		delete result;
		throw std::exception(e.what());
	}

	return *result;
}

Matrix& Matrix::Sub(const Matrix& left, const Matrix& right)
{
	Matrix* result = new Matrix{ left };

	try {
		result->Sub(right);
	}
	catch (std::exception e) {
		delete result;
		throw std::exception(e.what());
	}

	return *result;
}

Matrix& Matrix::Mul(const Matrix& left, const Matrix& right)
{
	if (left.GetSize() != right.GetSize()) throw std::exception("MatrixCalculator.Mul: different matrix sizes.");

	Matrix* result = new Matrix{ left };
	int size = result->GetSize();
	int rowSum = 0;

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			rowSum = 0;

			for (int inner = 0; inner < size; inner++)
			{
				rowSum += left[row][inner] * right[inner][col];
			}

			(*result)[row][col] = rowSum;
		}
	}

	return *result;
}


// Input/Output methods

void Matrix::Input()
{
	for (size_t row = 0; row < size; row++)
		for (size_t col = 0; col < size; col++)
			std::cin >> vector[row][col];
}

void Matrix::Output() const
{
	for (size_t row = 0; row < size; row++)
	{
		for (size_t col = 0; col < size; col++)
			std::cout << vector[row][col] << ' ';

		std::cout << std::endl;
	}
}

void Matrix::Input(std::ifstream& fin)
{
	for (size_t row = 0; row < size; row++)
		for (size_t col = 0; col < size; col++)
			fin >> vector[row][col];
}

void Matrix::Output(std::ofstream& fout) const
{
	for (size_t row = 0; row < size; row++)
	{
		for (size_t col = 0; col < size; col++)
			fout << vector[row][col] << ' ';

		fout << std::endl;
	}
}
