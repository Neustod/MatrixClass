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

    RNSVector a{ pCrypter, 28 }, b{ pCrypter, 28 }, err{ pCrypter, 256 };

    for (auto i = 0; i < 100; i++) 
    {
        int cmpResult{ a.DeepCompare(b) };

        std::cout << a.Decode() << "\t" << (cmpResult > 0 ? ">" : cmpResult < 0 ? "<" : "=") << "\t" << b.Decode() << std::endl;

        a.Encode(rander.RandInt16(0, 256));
        b.Encode(rander.RandInt16(0, 256));
    }

    system("pause");
    return 0;
}
