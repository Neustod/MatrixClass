#include "Tests.h"
#include <fstream>


int DecodeTest(const char* outputFile, const RNSCrypter& crypter)
{
    std::ofstream fout{ outputFile };
    uint32_t encoded, decoded;
    IntRandomizer rander;

    int errNumber = 0;

    for (int i = 0; i < crypter.Size(); i++) 
    {
        fout << crypter.Primes()[i] << " ";
    }
    fout << "\n";

    for (int i = 0; i < TEST_AMOUNT; i++)
    {
        encoded = rander.RandInt32();
        RNSVector test{ crypter, encoded };
        decoded = test.Decode(crypter);

        fout << i << "\n:encoded=" << encoded << "\n:decoded=" << decoded << "\n:RNS= ";

        test.Output(fout);

        if (encoded == decoded)
        {
            fout << "\ntrue";
        }
        else
        {
            fout << "\nfalse";
            errNumber++;
        }
        fout << ";\n\n";
    }

    fout.close();

    return errNumber;
}


int ArithmeticTest(
    const char* outputFile, 
    const RNSCrypter& crypter, 
    char cBinOperator)
{
    if (cBinOperator != '+' && cBinOperator != '-' && cBinOperator != '*') return -1;

    std::ofstream fout{ outputFile };
    IntRandomizer rander;

    int errNumber = 0;
    bool bInnerError = false;
    int matrixSize = 0;
    uint32_t tmp = 0;

    for (int i = 0; i < crypter.Size(); i++) fout << crypter.Primes()[i] << " ";
    fout << "\n";

    for (int i = 0; i < TEST_AMOUNT; i++)
    {
        matrixSize = rander.RandInt32(3, 11);

        bInnerError = false;

        SimpleMatrix<uint32_t> a{ matrixSize, 0 }, b{ matrixSize, 0 };
        RNSMatrix rnsA{ matrixSize, RNSVector{crypter} }, rnsB{ matrixSize, RNSVector{crypter} };

        fout << i << ":\nsize=" << matrixSize << ":\n";

        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                if (cBinOperator != '-') 
                {
                    a[row][col] = rander.RandInt32(0, RIGHT_BORDER);
                    b[row][col] = rander.RandInt32(0, RIGHT_BORDER);
                }
                else 
                {
                    a[row][col] = rander.RandInt32(RIGHT_BORDER / 2, RIGHT_BORDER);
                    b[row][col] = rander.RandInt32(0, RIGHT_BORDER / 2);
                }

                rnsA[row][col].Encode(crypter, a[row][col]);
                rnsB[row][col].Encode(crypter, b[row][col]);
            }
        }

        fout << "m1:\n";
        a.Output(fout);

        fout << "m2:\n";
        b.Output(fout);

        fout << "(rns)m1:\n";
        rnsA.Output(fout);

        fout << "(rns)m2:\n";
        rnsB.Output(fout);

        switch (cBinOperator)
        {
        case '+':
            a.Add(b);
            rnsA.Add(rnsB);
            break;
        case '-':
            a.Sub(b);
            rnsA.Sub(rnsB);
            break;
        case '*':
            a.Mul(b);
            rnsA.Mul(rnsB);
            break;
        default:
            fout.close();
            return -1;
        }

        fout << "(rns)m1*m2:\n";
        rnsA.Output(fout);

        fout << "m1*m2:\n";
        a.Output(fout);

        fout << "(decoded)m1*m2:\n";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                tmp = rnsA[row][col].Decode(crypter);

                if (tmp != a[row][col]) bInnerError = true;

                if (col + 1 == matrixSize)
                    fout << tmp;
                else
                    fout << tmp << " ";
            }
            fout << ":\n";
        }

        fout << (bInnerError ? "false" : "true") << ";\n\n";

        errNumber += bInnerError;
    }

    fout.close();

    return errNumber;
}
