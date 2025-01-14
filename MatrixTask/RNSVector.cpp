#include "RNSVector.h"
#include <xmemory>
#include <iostream>
#include <string>

#ifdef _DEBUG
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif // _DEBUG


// Constructors

RNSVector::RNSVector(const std::shared_ptr<RNSCrypter>& crypter, uint32_t decNum) : _crypter(crypter), RNSVectorLight(crypter.get()->Size())
{
	_crypter.get()->Encode(RNSVectorLight::Digits(), decNum);
}

RNSVector::RNSVector(const std::shared_ptr<RNSCrypter>& crypter, const RNSVectorLight& src) : _crypter(crypter), RNSVectorLight(src) {}

RNSVector::RNSVector(const std::shared_ptr<RNSCrypter>& crypter, RNSVectorLight&& src) : _crypter(crypter), RNSVectorLight(src) {}

RNSVector::RNSVector(const RNSVector& src) : _crypter(src._crypter), RNSVectorLight(src) {}

RNSVector::RNSVector(RNSVector&& src) noexcept : _crypter(std::move(src._crypter)), RNSVectorLight(src) {}

void RNSVector::operator=(const RNSVector& src)
{
	_crypter = src._crypter;
	RNSVectorLight::operator=(src);
}

void RNSVector::operator=(RNSVector&& src) noexcept
{
	_crypter = std::move(src._crypter);
	RNSVectorLight::operator=(src);
}


// Encoding and Decoding

uint32_t RNSVector::Decode() { return _crypter.get()->Decode(Digits()); }

void RNSVector::Encode(uint32_t decNum) { _crypter.get()->Encode(Digits(), decNum); }

//unsigned char RNSVector::DivisionDeep(unsigned int maxDeep) const
//{
//	return RNSVectorLight::DivisionDeep(_crypter.get()->OverflowErrorValue(), _crypter.get()->ReverseModuleOfTwo(), maxDeep);
//}


void RNSVector::Pow(uint32_t degree)
{
	if (degree == 0) { for (auto i = 0; i < Size(); i++) Digits()[i] = 1; return; };
	if (degree == 1) return;

	uint32_t tmp{ 0 };
	auto primes = _crypter.get()->Primes();

	for (auto i = 0; i < Size(); i++) 
	{
		tmp = Digits()[i];

		for (auto j = 0; j < degree - 1; j++) 
		{
			Digits()[i] = (Digits()[i] * tmp) % primes[i];
		}
	}
}

RNSVector& RNSVector::OverflowCorrection()
{
	RNSVectorLight::OverflowCorrection(_crypter.get()->OverflowErrorValue());
	return *this;
}

RNSVector& RNSVector::Normalize()
{
	auto primes = _crypter.get()->Primes();

	for (auto i = 0; i < Size(); i++) 
	{ 
		Digits()[i] %= primes[i];
	}

	return *this;
}
