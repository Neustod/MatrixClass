#pragma once
#include "SimpleMatrix.h"
#include "RNSMatrix.h"
#include "IntRandomizer.h"

#define TEST_AMOUNT 100

#define RIGHT_BORDER 10001


int DecodeTest(const char* outputFile, const RNSCrypter& crypter);


int ArithmeticTest(
	const char* outputFile, 
	const RNSCrypter& crypter, 
	char cBinOperator
);