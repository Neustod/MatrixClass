#include <iostream>
#include <string>
#include "RNSVector.h"
#include "Matrix.h"
#include "RNSRandomizer.h"
#include "Tests.h"

#define TEST_FOLDER "../Tests/"


// TESTING
int main()
{
    uint8_t primes[] = { 7, 11, 13, 17, 19, 23, 29, 31 };

    auto pCrypter = std::make_shared<RNSCrypter>(primes, 8);
    RNSRandomizer rander;

    RNSVector a{ pCrypter, 50 }, b{ pCrypter, 7 };

    std::cout << (a - b - b - b - b).Normalize().Decode() << std::endl;
    std::cout << (a - b - b - b - b).Normalize().ToString() << std::endl;

    system("pause");
    return 0;
}
