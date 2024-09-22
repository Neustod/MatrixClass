#include "Tests.h"
#include <fstream>


int DecodeTest(const std::string& outputFile, const RNSCrypter& crypter)
{
    std::ofstream fout{ outputFile };
    uint32_t encoded, decoded;
    IntRandomizer rander;

    int errNumber = 0;

    for (int i = 0; i < crypter.Size(); i++) fout << crypter.Primes()[i] << " ";
    fout << "\n";

    for (int i = 0; i < TEST_AMOUNT; i++)
    {
        encoded = rander.RandInt32();
        RNSVector test{ crypter, encoded };
        decoded = test.Decode(crypter);

        fout << i << ":encoded=" << encoded << ":decoded=" << decoded << ":";
        if (encoded == decoded)
        {
            fout << "true";
        }
        else
        {
            fout << "false";
            errNumber++;
        }
        fout << ";\n";
    }

    fout.close();

    return errNumber;
}


int AddTest(const std::string& outputFile, const RNSCrypter& crypter)
{
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

        fout << i <<":size="<< matrixSize << ":m1:";
        for (int row = 0; row < matrixSize; row++) 
        {
            for (int col = 0; col < matrixSize; col++)
            {
                a[row][col] = rander.RandInt32(0, RIGHT_BORDER);

                if (col + 1 == matrixSize)
                    fout << a[row][col];
                else
                    fout << a[row][col] << " ";

                rnsA[row][col].Encode(crypter, a[row][col]);
            }
            fout << ":";
        }

        fout << "m2:";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                b[row][col] = rander.RandInt32(0, RIGHT_BORDER);

                if (col + 1 == matrixSize)
                    fout << b[row][col];
                else
                    fout << b[row][col] << " ";

                rnsB[row][col].Encode(crypter, b[row][col]);
            }
            fout << ":";
        }

        a.Add(b);
        rnsA.Add(rnsB);

        fout << "m1+m2:";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                if (col + 1 == matrixSize)
                    fout << a[row][col];
                else
                    fout << a[row][col] << " ";
            }
            fout << ":";
        }

        fout << "(rns)m1+m2:";
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
            fout << ":";
        }

        if (bInnerError)
            fout << "false" << std::endl;
        else
            fout << "true" << std::endl;

        errNumber += bInnerError;
    }

    fout.close();

    return errNumber;
}


int MulTest(const std::string& outputFile, const RNSCrypter& crypter)
{
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

        fout << i << ":size=" << matrixSize << ":m1:";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                a[row][col] = rander.RandInt32(0, RIGHT_BORDER);

                if (col + 1 == matrixSize)
                    fout << a[row][col];
                else
                    fout << a[row][col] << " ";

                rnsA[row][col].Encode(crypter, a[row][col]);
            }
            fout << ":";
        }

        fout << "m2:";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                b[row][col] = rander.RandInt32(0, RIGHT_BORDER);

                if (col + 1 == matrixSize)
                    fout << b[row][col];
                else
                    fout << b[row][col] << " ";

                rnsB[row][col].Encode(crypter, b[row][col]);
            }
            fout << ":";
        }

        a.Mul(b);
        rnsA.Mul(rnsB);

        fout << "m1*m2:";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                if (col + 1 == matrixSize)
                    fout << a[row][col];
                else
                    fout << a[row][col] << " ";
            }
            fout << ":";
        }

        fout << "(rns)m1*m2:";
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
            fout << ":";
        }

        if (bInnerError)
            fout << "false" << std::endl;
        else
            fout << "true" << std::endl;

        errNumber += bInnerError;
    }

    fout.close();

    return errNumber;
}