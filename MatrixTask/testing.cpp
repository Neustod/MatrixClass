#include <iostream>
#include "Matrix.h"
#include "RNSVector.h"
#include "RNSCrypter.h"
#include "RNSMatrix.h"
#include "RNSRandomizer.h"

using namespace std;


// TESTING
int main()
{
    std::vector<uint32_t> prime1 = { 7, 11, 13, 17, 19, 23, 29, 31 };

    RNSCrypter coder1{ prime1.data(),prime1.size() };
    RNSRandomizer rander;

    int size = 3;
    uint32_t tmp = 0;

    RNSMatrix testMatrix1{ size, RNSVector{ coder1, 0 } };

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            testMatrix1[row][col] = rander.RandRNS(105, 32767, coder1);
        }
    }

    testMatrix1.Output();
    
    system("pause");
    return 0;
}

