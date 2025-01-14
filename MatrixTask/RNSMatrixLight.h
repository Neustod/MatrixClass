#pragma once
#include "RNSVectorLight.h"
#include "Matrix.h"

class RNSMatrixLight : public Matrix<RNSVectorLight> 
{
public:
	RNSMatrixLight(size_t primesCount, size_t size = 0) : Matrix<RNSVectorLight>(RNSVectorLight{primesCount}, size) {}

	RNSMatrixLight(const RNSMatrixLight& src) : Matrix<RNSVectorLight>(src) {}

	RNSMatrixLight(RNSMatrixLight&& src) noexcept : Matrix<RNSVectorLight>(src) {}

public:
	void operator=(const RNSMatrixLight& src) { Matrix<RNSVectorLight>::operator=(src); }

	void operator=(RNSMatrixLight&& src) noexcept { Matrix<RNSVectorLight>::operator=(src); }

public:
	// Overflow correction
	RNSMatrixLight& OverflowCorrection(const unsigned char* overflowErrorValue) 
	{
		size_t size = this->size();

		for (size_t row = 0; row < size; row++) 
		{
			for (size_t col = 0; col < size; col++) 
			{
				(*this)[row][col].OverflowCorrection(overflowErrorValue);
			}
		}

		return *this;
	}

	RNSMatrixLight& SingleOverflowCorrection(const unsigned char* overflowErrorValue)
	{
		size_t size = this->size();

		for (size_t row = 0; row < size; row++)
		{
			for (size_t col = 0; col < size; col++)
			{
				(*this)[row][col].SingleOverflowCorrection(overflowErrorValue);
			}
		}

		return *this;
	}

	// Overflow correction
	RNSMatrixLight& OverflowCorrection(const RNSVectorLight& overflowErrorValue) 
	{
		return OverflowCorrection(overflowErrorValue.Digits());
	}

	RNSMatrixLight& SingleOverflowCorrection(const RNSVectorLight& overflowErrorValue)
	{
		return SingleOverflowCorrection(overflowErrorValue.Digits());
	}

public:
	void Mul(const Matrix<RNSVectorLight>& right, const RNSVectorLight& overflowError)
	{
		size_t matrixSize = this->size();
		size_t primesCount = (*this)[0][0].Size();

		if (matrixSize == 0) return;

		RNSMatrixLight buffer(primesCount, matrixSize);

		for (size_t row = 0; row < matrixSize; row++)
		{
			for (size_t col = 0; col < matrixSize; col++)
			{
				for (size_t inner = 0; inner < matrixSize; inner++)
				{
					buffer[row][col] += ((*this)[row][inner] * right[inner][col]).OverflowCorrection(overflowError);
				}
				buffer[row][col].OverflowCorrection(overflowError);
			}
		}

		Matrix<RNSVectorLight>::operator=(std::move(buffer));
	}
};
