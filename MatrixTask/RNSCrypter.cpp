#include "RNSCrypter.h"


#ifdef _DEBUG
#include<iostream>
#define DEBUG(x)
#else
#define DEBUG(x)
#endif // _DEBUG


// Constructors

RNSCrypter::RNSCrypter() : _size(8)
{
	_primes = new uint32_t[_size]{ 7, 11, 13, 17, 19, 23, 29, 31 }; // It'll allow you to encode any UINT32
	_multiplications = new uint64_t[_size];

	CalcConsts();
}

RNSCrypter::RNSCrypter(const uint32_t* primes, size_t _size) : _size(_size)
{
	_primes = new uint32_t[_size];
	_multiplications = new uint64_t[_size];

	memcpy(_primes, primes, _size * sizeof(uint32_t));

	CalcConsts();
}

RNSCrypter::RNSCrypter(const RNSCrypter& src)  : _size(src._size), _P(src._P)
{
	_primes = new uint32_t[_size];
	_multiplications = new uint64_t[_size];

	memcpy(_primes, src._primes, _size * sizeof(uint32_t));
	memcpy(_multiplications, src._multiplications, _size * sizeof(uint32_t));
}


// Constants calculation

void RNSCrypter::CalcConsts() {
	_P = _primes[0];

	for (int i = 1; i < _size; i++)
		_P *= _primes[i];

	for (int i = 0; i < _size; i++)
	{
		_multiplications[i] = _P / _primes[i];

		for (int j = 1; j < _primes[i]; j++) {
			if (_multiplications[i] * j % _primes[i] == 1)
				_multiplications[i] *= j;
		}
	}

	DEBUG(
		std::cout << "[DEBUG] RNSCrypter.RNSCrypter:\n\tOrtoBases: ";
		for (int i = 0; i < _size; i++) std::cout << _multiplications[i] % _primes[i] << " ";
		std::cout << std::endl;)
}


// Getters

const uint32_t* RNSCrypter::Primes() const { return _primes; }

size_t RNSCrypter::Size() const { return _size; }


// Encoders

uint32_t* RNSCrypter::Encode(uint32_t decNum) const
{
	uint32_t* result = new uint32_t[_size];

	for (int i = 0; i < _size; i++)
		result[i] = decNum % _primes[i];

	return result;
}

void RNSCrypter::Encode(uint32_t* dst, uint32_t decNum) const
{
	for (int i = 0; i < _size; i++)
		dst[i] = decNum % _primes[i];
}


// Decoders

uint32_t RNSCrypter::Decode(const uint32_t* rnsNum) const 
{
	uint64_t preresult = 0;
	
	DEBUG(
		std::cout << "[DEBUG] RNSCrypter.Decode: \n\tRNS: ";
		for (int i = 0; i < _size; i++) std::cout << rnsNum[i] << " ";
		std::cout << "\n\tPrimes: ";
		for (int i = 0; i < _size; i++) std::cout << _primes[i] << " ";
		std::cout << "\n\t_P: " << _P << std::endl;)

	for (int i = 0; i < _size; i++)
	{
		if (rnsNum[i] == 0) continue;
		
		preresult += rnsNum[i] * _multiplications[i];
	}

	DEBUG(std::cout << "\tResult: " << preresult % _P << std::endl;)

	return preresult % _P;
}


// Deconstructor

RNSCrypter::~RNSCrypter() 
{
	delete[] _primes;
	delete[] _multiplications;
}