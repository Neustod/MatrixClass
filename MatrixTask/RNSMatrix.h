#pragma once
#include "Matrix.h"
#include "RNSVector.h"
#include "RNSCrypter.h"


class RNSMatrix : public Matrix<RNSVector>
{
public:
	RNSMatrix();

	RNSMatrix(int size, const RNSVector& defaultValue);

	RNSMatrix(const RNSMatrix& src);

	RNSMatrix(RNSMatrix&& src) noexcept;


	void Add(const Matrix<RNSVector>& right);

	void Sub(const Matrix<RNSVector>& right);

	void Mul(const Matrix<RNSVector>& right);

	static RNSMatrix& Add(const RNSMatrix& left, const RNSMatrix& right);

	static RNSMatrix& Sub(const RNSMatrix& left, const RNSMatrix& right);

	static RNSMatrix& Mul(const RNSMatrix& left, const RNSMatrix& right);


	// Console stream input.
	void Input() override;

	// Console stream output.
	void Output() const override;

	// File stream input.
	void Input(std::ifstream& fin) override;

	// File stream output.
	void Output(std::ofstream& fout) const override;
};

