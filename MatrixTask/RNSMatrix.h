#pragma once
#include "Matrix.h"
#include "RNSVector.h"


class RNSMatrix : public Matrix<RNSVector>
{
public:
	RNSMatrix();

	RNSMatrix(int size, const RNSVector& defaultValue);

	RNSMatrix(const RNSMatrix& src);

	void Add(const Matrix& right);

	void Mul(const Matrix& right);

	static RNSMatrix& Add(const RNSMatrix& left, const RNSMatrix& right);

	static RNSMatrix& Mul(const RNSMatrix& left, const RNSMatrix& right);

	// Console stream input.
	void Input();

	// Console stream output.
	void Output() const;

	// File stream input.
	void Input(std::ifstream& fin);

	// File stream output.
	void Output(std::ofstream& fout) const;
};

