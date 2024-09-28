#include "RNSVector.h"
#include <xmemory>
#include <iostream>


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

RNSVector::RNSVector(RNSVector&& src) noexcept : _size(src._size)
{
	_digits = NULL;
	_primes = NULL;

	std::swap(_digits, src._digits);
	std::swap(_primes, src._primes);
}


size_t RNSVector::Size() const { return _size; }

const uint32_t* RNSVector::Primes() const { return _primes; }


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

void RNSVector::Sub(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	for (int i = 0; i < _size; i++)
	{
		_digits[i] = ((uint64_t)_digits[i] + (_primes[i] - rightRnsNum._digits[i])) % _primes[i];
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

void RNSVector::Div(const RNSVector& rightRnsNum)
{
	// TODO: Div method
}

void RNSVector::Mod(const RNSVector& rightRnsNum)
{
	// TODO: Mod method
}

RNSVector& RNSVector::Add(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Add(rightRnsNum);

	return *result;
}

RNSVector& RNSVector::Sub(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Sub(rightRnsNum);

	return *result;
}

RNSVector& RNSVector::Mul(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Mul(rightRnsNum);

	return *result;
}

RNSVector& RNSVector::Div(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Div(rightRnsNum);

	return *result;
}

RNSVector& RNSVector::Mod(const RNSVector& leftRnsNum, const RNSVector& rightRnsNum)
{
	RNSVector* result = new RNSVector(leftRnsNum);
	result->Mod(rightRnsNum);

	return *result;
}


void RNSVector::Input()
{
	for (int i = 0; i < _size; i++) scanf_s("%u", &_digits[i]);
}

void RNSVector::Output() const
{
	for (int i = 0; i < _size; i++) printf_s("%u ", _digits[i]);
}

void RNSVector::Input(std::ifstream& fin)
{
	for (int i = 0; i < _size; i++) fin >> _digits[i];
}

void RNSVector::Output(std::ofstream& fout) const
{
	for (int i = 0; i < _size; i++)
	{
		fout << _digits[i];

		if (i < _size - 1) fout << " ";
	}
}

void RNSVector::operator=(const RNSVector& src)
{
	_size = src._size;

	_digits = new uint32_t[_size];
	_primes = new uint32_t[_size];

	memcpy(_digits, src._digits, _size * sizeof(uint32_t));
	memcpy(_primes, src._primes, _size * sizeof(uint32_t));
}

void RNSVector::operator=(RNSVector&& src) noexcept
{
	_size = src._size;

	std::swap(_digits, src._digits);
	std::swap(_primes, src._primes);
}


// Deconstructor

RNSVector::~RNSVector()
{
	if (_digits != NULL) delete[] _digits;
	if (_primes != NULL) delete[] _primes;
}