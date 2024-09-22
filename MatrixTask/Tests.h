#pragma once
#include "SimpleMatrix.h"
#include "RNSMatrix.h"
#include "IntRandomizer.h"

#define TEST_AMOUNT 1000

#define RIGHT_BORDER 10001


int DecodeTest(const std::string& outputFile, const RNSCrypter& crypter);


int AddTest(const std::string& outputFile, const RNSCrypter& crypter);


int MulTest(const std::string& outputFile, const RNSCrypter& crypter);