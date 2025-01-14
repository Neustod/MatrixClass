#pragma once
#include "Matrix.h"
#include "RNSCrypter.h"
#include "IntRandomizer.h"


#define TEST_AMOUNT 30

#define MIN_MATRIX_AMOUNT 2
#define MAX_MATRIX_AMOUNT 3

#define MIN_MATRIX_SIZE 28
#define MAX_MATRIX_SIZE 32

#define RIGHT_BORDER 256


int DecodeTest(const char* resultOutputFile, const char* perfomanceOutputFile,  const std::shared_ptr<RNSCrypter>& crypter);


int ArithmeticTest(
	const char* resultOutputFile, 
	const char* perfomanceOutputFile,
	const std::shared_ptr<RNSCrypter>& crypter,
	char cBinOperator
);
