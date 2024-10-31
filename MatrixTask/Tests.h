#pragma once
#include "Matrix.h"
#include "RNSCrypter.h"
#include "IntRandomizer.h"


#define TEST_AMOUNT 10

#define RIGHT_BORDER 10001


int DecodeTest(const char* resultOutputFile, const char* perfomanceOutputFile,  const std::shared_ptr<RNSCrypter>& crypter);


int ArithmeticTest(
	const char* resultOutputFile, 
	const char* perfomanceOutputFile,
	const std::shared_ptr<RNSCrypter>& crypter,
	char cBinOperator
);
