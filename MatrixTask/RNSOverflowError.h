#pragma once
#include "RNSVector.h"
#include "RNSCrypter.h"


class RNSOverflowError : public RNSVector 
{
public:
	RNSOverflowError() = delete;

	RNSOverflowError(const std::shared_ptr<RNSCrypter>& crypter) : RNSVector(crypter, 256) {};
};