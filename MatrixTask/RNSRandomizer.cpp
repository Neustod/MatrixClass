#include "RNSRandomizer.h"
#include <exception>


// Constructors

RNSRandomizer::RNSRandomizer() {}


// Rand methods

RNSVector& RNSRandomizer::RandRNS(int32_t lBorder, int32_t rBorder, const std::shared_ptr<RNSCrypter>& crypter)
{
	if (lBorder < 0) throw std::exception("Error: RNSRandomizer.RandRNS: negative value.");

	RNSVector* result = new RNSVector{ crypter, (uint32_t)RandInt32(lBorder, rBorder) };
	
	return *result;
}