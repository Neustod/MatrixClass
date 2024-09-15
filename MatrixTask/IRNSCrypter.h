#pragma once
#include <stdint.h>


__interface IRNSCrypter
{
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
};