#include "RNSCrypter.h"
#include "RNSVector.h"
#include <memory>


// Constructors

RNSCrypter::RNSCrypter(const uint8_t* primes, size_t size) : _size(size)
{
	_primes = new uint8_t[_size];
	_multiplications = new uint64_t[_size];

	memcpy(_primes, primes, _size * sizeof(uint8_t));

	CalcConsts();
}

RNSCrypter::RNSCrypter(const RNSCrypter& src)  : _size(src._size), _P(src._P)
{
	_primes = new uint8_t[_size];
	_multiplications = new uint64_t[_size];

	memcpy(_primes, src._primes, _size * sizeof(uint8_t));
	memcpy(_multiplications, src._multiplications, _size * sizeof(uint32_t));
}

RNSCrypter::RNSCrypter(RNSCrypter&& src) noexcept : _size(src._size), _P(src._P)
{
	_primes = NULL;
	_multiplications = NULL;

	std::swap(_primes, src._primes);
	std::swap(_multiplications, src._multiplications);
}


// Constants calculation

void RNSCrypter::CalcConsts() {
	_P = _primes[0];

	for (size_t i = 1; i < _size; i++) 
	{
		_P *= _primes[i];
	}

	for (size_t i = 0; i < _size; i++)
	{
		_multiplications[i] = _P / _primes[i];

		for (auto j = 1; j < _primes[i]; j++) {
			if (_multiplications[i] * j % _primes[i] == 1) 
			{
				_multiplications[i] *= j;
				break;
			}
		}
	}
}


// Encoders

void RNSCrypter::Encode(uint8_t* dst, uint32_t decNum) const
{
	for (size_t i = 0; i < _size; i++)
		dst[i] = decNum % _primes[i];
}


// Decoders

uint32_t RNSCrypter::Decode(const uint8_t* rnsNum) const 
{
	uint64_t preresult = 0;

	for (size_t i = 0; i < _size; i++)
	{
		if (rnsNum[i] == 0) continue;
		
		preresult += rnsNum[i] * _multiplications[i];
	}

	return (uint32_t)(preresult % _P);
}

uint32_t RNSCrypter::DeepDecode(const uint8_t* rnsNum) const
{
	RNSVector tmp{ std::make_shared<RNSCrypter>(*this) };
	RNSVector two{ std::make_shared<RNSCrypter>(*this), 2 };

	uint64_t result{ 0 };
	uint32_t deep{ 0 };

	auto IsZero = [](const RNSVector& rns)
	{
		for (size_t i = 0; i < rns.Size(); i++) if (rns.Digits()[i] != 0) return false;
		return true;
	};

	for (size_t i = 0; i < _size; i++) tmp[i] = rnsNum[i];

	while (!IsZero(tmp))
	{
		deep = tmp.DivisionDeep();
		result |= (uint64_t)1 << deep;

		two.Pow(deep);
		two.Normalize();

		tmp -= two;
		tmp.Normalize();

		for (size_t i = 0; i < _size; i++) two[i] = 2;
	}

	return (uint32_t)result;
}


// Operators

void RNSCrypter::operator=(const RNSCrypter& src)
{
	if (_size != src._size)
	{
		delete[] _primes;
		delete[] _multiplications;

		_primes = new uint8_t[src._size];
		_multiplications = new uint64_t[src._size];
	}

	_size = src._size;
	_P = src._P;

	memcpy(_primes, src._primes, _size * sizeof(uint8_t));
	memcpy(_multiplications, src._multiplications, _size * sizeof(uint32_t));
}

void RNSCrypter::operator=(RNSCrypter&& src) noexcept
{
	_size = src._size;
	_P = src._P;

	std::swap(_primes, src._primes);
	std::swap(_multiplications, src._multiplications);
}