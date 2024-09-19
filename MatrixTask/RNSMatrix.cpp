#include "RNSMatrix.h"
#include "RNSCrypter.h"
#include <iostream>


RNSMatrix::RNSMatrix() {}

RNSMatrix::RNSMatrix(int size, const RNSVector& defaultValue) : Matrix<RNSVector>(size, defaultValue) {}

RNSMatrix::RNSMatrix(const RNSMatrix& src) : Matrix<RNSVector>(src) {}

void RNSMatrix::Add(const Matrix<RNSVector>& right)
{
	int size = this->GetSize();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			(*this)[row][col].Add(right[row][col]);
		}
	}
}

void RNSMatrix::Mul(const Matrix<RNSVector>& right)
{
	int size = this->GetSize();

	if (size == 0) return;

	RNSCrypter crypter{(*this)[0][0].Primes(), (*this)[0][0].Size()};
	RNSVector rowSum{ crypter };

	std::vector<RNSVector> tmpRow;
	for (int i = 0; i < (*this)[0][0].Size(); i++) tmpRow.push_back(RNSVector{ crypter });

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			rowSum.Encode(crypter, 0);

			for (int inner = 0; inner < size; inner++)
			{
				rowSum.Add(RNSVector::Mul((*this)[row][inner], right[inner][col]));
			}

			tmpRow[col] = rowSum;
		}
		for (int col = 0; col < size; col++) (*this)[row][col] = tmpRow[col];
	}
}

RNSMatrix& RNSMatrix::Add(const RNSMatrix& left, const RNSMatrix& right)
{
	RNSMatrix* result{ new RNSMatrix{ left } };
	result->Add(right);

	return *result;
}

RNSMatrix& RNSMatrix::Mul(const RNSMatrix& left, const RNSMatrix& right)
{
	RNSMatrix* result{ new RNSMatrix{ left } };
	result->Mul(right);

	return *result;
}

void RNSMatrix::Input()
{
	int size = GetSize();

	for (int row = 0; row < size; row++)
	{
		for ( int col = 0; col < size; col++)
		{
			(*this)[row][col].Input();
		}
	}
}

void RNSMatrix::Input(std::ifstream& fin)
{
	int size = GetSize();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			(*this)[row][col].Input(fin);
		}
	}
}

void RNSMatrix::Output() const 
{
	int size = GetSize();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			(*this)[row][col].Output();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void RNSMatrix::Output(std::ofstream& fout) const
{
	int size = GetSize();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			(*this)[row][col].Output(fout);
			fout << std::endl;
		}
	}
}