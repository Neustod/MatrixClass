#pragma once
#include <cstdint>
#include "IRNSCrypter.h"


// The class is used to store calculation constants and encrypt/decrypt RNS numbers.
class RNSCrypter : public IRNSCrypter
{
private:
	uint32_t* _primes;
	uint64_t* _multiplications;
	uint64_t _P;
	size_t _size;

	// Function calculates constants
	void CalcConsts();

public:
	// Default constructors.
	RNSCrypter();

	// Constructor sets constants by "primes" array.
	RNSCrypter(const uint32_t* primes, size_t _size);

	// Copy constructor
	RNSCrypter(const RNSCrypter& src);

	RNSCrypter(RNSCrypter&& src) noexcept;

	// Returns a pointer to an array of bases.
	const uint32_t* Primes() const;

	// Returns a count of bases.
	size_t Size() const;


	// Encodes uint32 number to RNS code.
	// Returns an array of uint32 numbers with RNS code.
	uint32_t* Encode(uint32_t decNum) const;

	// Encodes uint32 number to RNS code.
	// Writes result in the "dst" array.
	void Encode(uint32_t* dst, uint32_t decNum) const;

	// Decodes RNS code to uint32 number.
	uint32_t Decode(const uint32_t* rnsNum) const;

	void operator=(const RNSCrypter& src);

	void operator=(RNSCrypter&& src) noexcept;

	// Deconstructor
	~RNSCrypter();
};

