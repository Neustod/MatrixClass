#include <iostream>
#include <string>
#include "RNSVector.h"
#include "RNSMatrix.h"
#include "RNSRandomizer.h"
#include "Tests.h"
#include "RNSOverflowError.h"

#define TEST_FOLDER "../Tests/"


// TESTING
int main()
{
    uint8_t primes[] = { 7, 11, 13, 17, 19, 23, 29, 31 };
    size_t primesCount = sizeof(primes) / sizeof(uint8_t);
    size_t matrixSize = 3;

    RNSRandomizer rander;
    auto pCrypter = std::make_shared<RNSCrypter>(primes, primesCount);

    std::cout << "Add test: " << ArithmeticTest("../Tests/AddTest0.txt", "../Tests/AddTime0.txt", pCrypter, '+') << " errors." << std::endl;
    std::cout << "Sub test: " << ArithmeticTest("../Tests/SubTest0.txt", "../Tests/SubTime0.txt", pCrypter, '-') << " errors." << std::endl;
    std::cout << "Mul test: " << ArithmeticTest("../Tests/MulTest0.txt", "../Tests/MulTime0.txt", pCrypter, '*') << " errors." << std::endl;

    system("pause");
    return 0;
}
