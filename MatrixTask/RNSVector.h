#pragma once
#include "RNSCrypter.h"
#include <fstream>


// The class is used to store RNS numbers and doing arithmetical operatiions.
class RNSVector
{
private:
	uint8_t* _digits;
	uint8_t* _overflowBank = NULL;

	const uint8_t* _primes;
	size_t _size;

	std::shared_ptr<RNSCrypter> _crypter;

public:
	// Default constructor was deleted, so
	// you have to initialize Crypter first.
	RNSVector() = delete;

	// Construct class by encoding RNS number with Crypter and decimal number.
	RNSVector(const std::shared_ptr<RNSCrypter>& crypter, uint32_t decNum = 0);

	// Copy constructor.
	RNSVector(const RNSVector& src);

	// Move constructor.
	RNSVector(RNSVector&& src) noexcept;

public:
	size_t Size() const { return _size; };

	const uint8_t* Primes() const { return _primes; }

	const std::shared_ptr<RNSCrypter>& Crypter() const { return _crypter; }

	const uint8_t* Digits() const { return _digits; }

	uint8_t* Digits() { return _digits; }

public:
	// Returns decoded value by decrypting RNS number in the Crypter.
	uint32_t Decode();

	// Encodes RNS number with decimal number in the Crypter.
	void Encode(uint32_t decNum);

public:
	// Local adding operation for RNS numbers.
	void Add(const RNSVector& rightRnsNum);

	// Local subliming operation for RNS numbers.
	void Sub(const RNSVector& rightRnsNum);

	// Local multiplicating operation for RNS numbers.
	void Mul(const RNSVector& rightRnsNum);

	// Local dividing opertion for RNS numbers.
	// IN TESTING
	void Div(const RNSVector& rightRnsNum);

	// Lightweight dividing by two.
	bool DivByTwo();

	// Elevation to the power of degree
	void Pow(uint32_t degree);

	// Overflow correction
	RNSVector& OverflowCorrection(const RNSVector& errorValue);

	// Correction by modules
	RNSVector& Normalize();

public:
	uint8_t DivisionDeep(uint32_t maxDeep = 21) const;

	uint32_t DeepDecode() const { return _crypter.get()->DeepDecode(_digits); };

	int DeepCompare(const RNSVector rnsRight, uint32_t maxDeep = 21) const;

public:
	void Input(std::ifstream& fin);

	void Output(std::ofstream& fout) const;

	std::string ToString() const;

	friend std::string to_string(const RNSVector& item) { return item.ToString(); };

public:
	inline friend RNSVector& operator+(const RNSVector& left, const RNSVector& right)
	{
		RNSVector* result = new RNSVector(left);
		result->Add(right);

		return *result;
	}

	inline friend RNSVector& operator-(const RNSVector& left, const RNSVector& right)
	{
		RNSVector* result = new RNSVector(left);
		result->Sub(right);

		return *result;
	}

	inline friend RNSVector& operator*(const RNSVector& left, const RNSVector& right)
	{
		RNSVector* result = new RNSVector(left);
		result->Mul(right);

		return *result;
	}

	inline friend RNSVector& operator/(const RNSVector& left, const RNSVector& right)
	{
		RNSVector* result = new RNSVector(left);
		result->Div(right);

		return *result;
	}

	inline void operator+=(const RNSVector& right) { this->Add(right); }

	inline void operator-=(const RNSVector& right) { this->Sub(right); }

	inline void operator*=(const RNSVector& right) { this->Mul(right); }

	inline void operator/=(const RNSVector& right) { this->Div(right); }

	inline RNSVector& operator++() 
	{
		for (size_t i = 0; i < _size; i++)
		{
			_overflowBank[i] += (_digits[i] == 255);
			_digits[i] = (_digits[i] + 1);
		}

		return *this;
	}

	inline RNSVector& operator++(int) 
	{
		RNSVector& result = *new RNSVector{ *this };

		++*this;

		return result;
	}
	
	inline RNSVector& operator--()
	{
		for (size_t i = 0; i < _size; i++)
		{
			_overflowBank[i] -= (_digits[i] == 0);
			--_digits[i];
		}

		return *this;
	}

	inline RNSVector& operator--(int)
	{
		RNSVector& result = *new RNSVector{ *this };

		--* this;

		return result;
	}

	bool operator==(const RNSVector& right) const;
	
	bool operator!=(const RNSVector& right) const { return !(*this == right); };

	void operator=(const RNSVector& src);

	void operator=(RNSVector&& src) noexcept;

	friend std::ostream& operator<<(std::ostream& out, const RNSVector& item) 
	{
		for (size_t i = 0; i < item.Size(); i++) out << item[i];
		return out;
	}

	friend std::istream& operator>>(std::istream& in, RNSVector& item)
	{
		for (size_t i = 0; i < item.Size(); i++) in >> item[i];
		return in;
	}

	uint8_t operator[](size_t index) const 
	{
		if (index >= _size) throw std::exception("RNSVector.operator[]: index out of range.");
		return _digits[index];
	}

	uint8_t& operator[](size_t index) 
	{
		if (index >= _size) throw std::exception("RNSVector.operator[]: index out of range.");
		return _digits[index];
	}

public:
	// Deconstructor
	~RNSVector();
};

