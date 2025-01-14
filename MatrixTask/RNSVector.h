#pragma once
#include "RNSVectorLight.h"
#include "RNSCrypter.h"
#include <fstream>


// The class is used to store RNS numbers and doing arithmetical operatiions.
class RNSVector : public RNSVectorLight
{
private:
	std::shared_ptr<RNSCrypter> _crypter;

public:
	// Default constructor was deleted, so
	// you have to initialize Crypter first.
	RNSVector() = delete;

	// Construct class by encoding RNS number with Crypter and decimal number.
	RNSVector(const std::shared_ptr<RNSCrypter>& crypter, uint32_t decNum = 0);

	RNSVector(const std::shared_ptr<RNSCrypter>& crypter, const RNSVectorLight& src);

	RNSVector(const std::shared_ptr<RNSCrypter>& crypter, RNSVectorLight&& src);

	// Deconstructor
	~RNSVector() {};

	// Copy constructor.
	RNSVector(const RNSVector& src);

	RNSVector(RNSVector&& src) noexcept;

public:
	void operator=(const RNSVector& src);

	void operator=(RNSVector&& src) noexcept;

public:
	const uint8_t* Primes() const { return _crypter.get()->Primes(); }

	const std::shared_ptr<RNSCrypter>& Crypter() const { return _crypter; }

public:
	// Returns decoded value by decrypting RNS number in the Crypter.
	uint32_t Decode();

	// Returns decoded value by binary division method
	uint32_t DeepDecode() const { return _crypter.get()->DeepDecode(Digits()); };

	// Encodes RNS number with decimal number in the Crypter.
	void Encode(uint32_t decNum);

public:
	//unsigned char DivisionDeep(unsigned int maxDeep = 21) const;

	// Elevation to the power of degree
	void Pow(uint32_t degree);

	RNSVector& OverflowCorrection();

	// Correction by modules
	RNSVector& Normalize();
};

