#pragma once
#include "IntRandomizer.h"
#include "RNSVector.h"
#include "IRNSCrypter.h"


// RNS values randomizer.
// Rands uint value and then encodes it to RNS.
class RNSRandomizer : public IntRandomizer
{
public:
	RNSRandomizer();

	RNSVector& RandRNS(int32_t lBorder, int32_t rBorder, const IRNSCrypter& crypter);
};

