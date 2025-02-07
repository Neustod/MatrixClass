#pragma once
#include <cstdint>


// The class is used to store calculation constants and encrypt/decrypt RNS numbers.
class RNSCrypter
{
private:
	uint8_t* _primes;

	uint8_t* _ovError;
	uint8_t* _twoRevMod;

	uint64_t* _multiplications;
	uint64_t _P;
	size_t _size;

private:
	// Function calculates constants
	void CalcConsts();

public:
	// Default constructors.
	RNSCrypter() = delete;

	// Constructor sets constants by "primes" array.
	RNSCrypter(const uint8_t* primes, size_t _size);

	// Copy constructor
	RNSCrypter(const RNSCrypter& src);

	RNSCrypter(RNSCrypter&& src) noexcept;

public:
	// Returns a pointer to an array of bases.
	const uint8_t* Primes() const { return _primes; };

	uint64_t P() const { return _P; }

	const uint8_t* OverflowErrorValue() const { return _ovError; }

	const uint8_t* ReverseModuleOfTwo() const { return _twoRevMod; }

	// Returns a count of bases.
	size_t Size() const { return _size; };

public:
	// Encodes uint32 number to RNS code.
	// Writes result in the "dst" array.
	void Encode(uint8_t* dst, uint32_t decNum) const 
	{
		for (size_t i = 0; i < _size; i++)
			dst[i] = decNum % _primes[i];
	}

	void EncodeReverseDivider(const uint8_t* srcDivider, uint8_t* dstRevDivider) const
	{
		for (auto i = 0; i < _size; i++)
		{
			dstRevDivider[i] = ReverseModule(srcDivider[i], _primes[i]);
		}
	}

	// Decodes RNS code to uint32 number.
	uint32_t Decode(const uint8_t* rnsNum) const;

	// TODO: [RNSCrypter.DeepDecode] test function
	uint32_t DeepDecode(const uint8_t* rnsNum) const;

private:
	// Polinomial reverse module
	static uint32_t ReverseModule(uint32_t a, uint32_t m)
	{
		uint32_t result{ 1 };
		for (int i = 0; i < m - 2; i++) result *= a;
		return result % m;
	}

public:
	void operator=(const RNSCrypter& src);

	void operator=(RNSCrypter&& src) noexcept;

public:
	// Deconstructor
	~RNSCrypter() 
	{
		if (_primes != nullptr) delete[] _primes;
		if (_ovError != nullptr) delete[] _ovError;
		if (_multiplications != nullptr) delete[] _multiplications;
		if (_twoRevMod != nullptr) delete[] _twoRevMod;
	}
};

