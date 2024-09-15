#include <iostream>
#include "Matrix.h"
#include "RNSVector.h"
#include "RNSCrypter.h"

using namespace std;


// TESTING
int main()
{
    uint32_t prime1[] = { 3, 5, 7 };
    uint32_t prime2[] = { 255, 256, 257, 511 };

    RNSCrypter coder1{ prime1, 3 }, coder2{ prime2, 4 };

    RNSVector v1{ coder1, 102 }, v2{coder2, v1.Decode(coder1)};

    v2.Mul(v2);
    v2.Decode(coder2);

    system("pause");
    return 0;
}

