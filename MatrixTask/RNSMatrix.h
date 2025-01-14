#pragma once
#include "RNSMatrixLight.h"
#include "RNSCrypter.h"


class RNSMatrix : public RNSMatrixLight 
{
private:
	std::shared_ptr<RNSCrypter> _crypter;

public:
	RNSMatrix(const std::shared_ptr<RNSCrypter>& crypter, size_t size = 0) : _crypter(crypter), RNSMatrixLight(crypter.get()->Size(), size) {}

	RNSMatrix(const RNSMatrix& src) : _crypter(src._crypter), RNSMatrixLight(src) {}

	RNSMatrix(RNSMatrix&& src) noexcept : _crypter(std::move(src._crypter)), RNSMatrixLight(src) {}

	RNSMatrix(const std::shared_ptr<RNSCrypter>& crypter, const RNSMatrixLight& src) : _crypter(crypter), RNSMatrixLight(src) {}

	RNSMatrix(const std::shared_ptr<RNSCrypter>& crypter, RNSMatrixLight&& src) : _crypter(crypter), RNSMatrixLight(src) {}

public:
	void operator=(const RNSMatrix& src) { _crypter = src._crypter; RNSMatrixLight::operator=(src); }

	void operator=(RNSMatrix&& src) noexcept { _crypter = std::move(src._crypter); RNSMatrixLight::operator=(src); }

public:
	static Matrix<uint32_t>& Decode(const std::shared_ptr<RNSCrypter>& crypter, const RNSMatrixLight& src)
	{
		size_t matrixSize = src.size();
		auto& simplifiedMatrix = *new Matrix<uint32_t>(0, matrixSize); // Default value for matrix and matrix size

		for (size_t row = 0; row < matrixSize; row++)
		{
			for (size_t col = 0; col < matrixSize; col++)
			{
				simplifiedMatrix[row][col] = crypter.get()->Decode(src[row][col].Digits()); // Unsafe
			}
		}

		return simplifiedMatrix;
	}

	Matrix<uint32_t>& Decode() { return Decode(_crypter, *this); }
};