#pragma once
#include <vector>
#include <fstream>


class Matrix
{
private:
	std::vector<std::vector<int>> vector;
	int size;

public:
	// Default constructors
	Matrix(int _size = 0);

	// Copying constructor
	Matrix(const Matrix& src);


	// Changes Matrix's size. Allocates memory with default vaule 0.
	// Throws exceprion.
	void SetSize(int _size);

	// Get actual Matrix's size.
	int GetSize() const;


	// Fills Matrix with random numbers from the left vaule to the right.
	void Randomize(int leftBoard, int rightBoard);


	// Adding Matrixes.
	// Result will be stored in the current Matrix object.
	void Add(const Matrix& right);

	// Subliming Matrixes.
	// Result will be stored in the current Matrix object.
	void Sub(const Matrix& right);

	// Multiplying Matrixes.
	// Result will be stored in the current Matrix object.
	void Mul(const Matrix& right);

	// Adding Matrixes.
	// Returns new Matrix object.
	static Matrix& Add(const Matrix& left, const Matrix& right);

	// Subliming Matrixes.
	// Returns new Matrix object.
	static Matrix& Sub(const Matrix& left, const Matrix& right);

	// Multiplying Matrixes.
	// Returns new Matrix object.
	static Matrix& Mul(const Matrix& left, const Matrix& right);

	// Console stream input.
	void Input();

	// Console stream output.
	void Output() const;

	// File stream input.
	void Input(std::ifstream& fin);

	// File stream output.
	void Output(std::ofstream& fout) const;


	std::vector<int>& operator[](int i) {
		if (i < 0) throw std::exception("Matrix.operator[]: negative index.");
		if (i > size - 1) throw std::exception("Matrix.operator[]: out of range.");

		return vector[i];
	}

	const std::vector<int>& operator[](int i) const {
		if (i < 0) throw std::exception("Matrix.operator[]: negative index.");
		if (i > size - 1) throw std::exception("Matrix.operator[]: out of range.");

		return vector[i];
	}
};
