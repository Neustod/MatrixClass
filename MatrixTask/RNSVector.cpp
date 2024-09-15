#include "RNSVector.h"
#include <xmemory>


// Constructors

RNSVector::RNSVector(const IRNSCrypter& crypter, uint32_t decNum) : _size(crypter.Size())
{
	_digits = crypter.Encode(decNum);
	_primes = new uint32_t[_size];

	memcpy(_primes, crypter.Primes(), _size * sizeof(uint32_t));
}

RNSVector::RNSVector(const RNSVector& src) : _size(src._size)
{
	_digits = new uint32_t[_size];
	_primes = new uint32_t[_size];

	memcpy(_digits, src._digits, _size * sizeof(uint32_t));
	memcpy(_primes, src._primes, _size * sizeof(uint32_t));
}


// Encoding and Decoding

uint32_t RNSVector::Decode(const IRNSCrypter& crypter) { return crypter.Decode(_digits); }

void RNSVector::Encode(const IRNSCrypter& crypter, uint32_t decNum) { crypter.Encode(_digits, decNum); }


// Arithmetical operations

void RNSVector::Add(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	for (int i = 0; i < _size; i++) 
	{
		_digits[i] = ((uint64_t)_digits[i] + rightRnsNum._digits[i]) % _primes[i];
	}
}

void RNSVector::Mul(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	for (int i = 0; i < _size; i++)
	{
		_digits[i] = ((uint64_t)_digits[i] * rightRnsNum._digits[i]) % _primes[i];
	}
}

RNSVector& RNSVector::Add(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Add(rightRnsNum);

	return *result;
}

RNSVector& RNSVector::Mul(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Mul(rightRnsNum);

	return *result;
}


// Deconstructor

RNSVector::~RNSVector()
{
	delete[] _digits;
	delete[] _primes;
}