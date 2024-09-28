#pragma once
#include "IRNSCrypter.h"
#include <fstream>


// The class is used to store RNS numbers and doing arithmetical operatiions.
class RNSVector
{
private:
	uint32_t* _digits;
	uint32_t* _primes;
	size_t _size;

public:
	// Default constractor was deleted, so
	// you have to initialize Cryptor first.
	RNSVector() = delete;

	// Construct class by encoding RNS number with Cryptor and decimal number.
	RNSVector(const IRNSCrypter& crypter, uint32_t decNum = 0);

	// Copy constructor.
	RNSVector(const RNSVector& src);

	// Move constructor.
	RNSVector(RNSVector&& src) noexcept;


	size_t Size() const;

	const uint32_t* Primes() const;

	// Returns decoded value by decrypting RNS number in the Crypter.
	uint32_t Decode(const IRNSCrypter& crypter);

	// Encodes RNS number with decimal number in the Crypter.
	void Encode(const IRNSCrypter& crypter, uint32_t decNum);


	// Local adding operation for RNS numbers.
	void Add(const RNSVector& rightRnsNum);

	// Local subliming operation for RNS numbers.
	void Sub(const RNSVector& rightRnsNum);

	// Local multiplicating operation for RNS numbers.
	void Mul(const RNSVector& rightRnsNum);

	void Div(const RNSVector& rightRnsNum);

	void Mod(const RNSVector& rightRnsNum);

	// Adding operation for RNS numbers.
	static RNSVector& Add(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum);

	// Subliming operation for RNS numbers.
	static RNSVector& Sub(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum);

	// Multiplicating operation for RNS numbers.
	static RNSVector& Mul(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum);

	static RNSVector& Div(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum);

	static RNSVector& Mod(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum);

	void Input();

	void Output() const;

	void Input(std::ifstream& fin);

	void Output(std::ofstream& fout) const;


	void operator=(const RNSVector& src);

	void operator=(RNSVector&& src) noexcept;


	// Deconstructor
	~RNSVector();
};

