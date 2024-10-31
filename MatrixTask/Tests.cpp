#include "Tests.h"
#include <fstream>
#include <chrono>
#include "RNSVector.h"

#define TEST_RATIO std::chrono::nanoseconds


int DecodeTest(const char* resultOutputFile, const char* perfomanceOutputFile, const std::shared_ptr<RNSCrypter>& crypter)
{
    std::ofstream fout{ resultOutputFile };
    std::ofstream ftime{ perfomanceOutputFile };

    uint32_t encoded, decoded;
    IntRandomizer rander;

    int errNumber = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;


    for (int i = 0; i < crypter.get()->Size(); i++) 
    {
        fout << (uint32_t)crypter.get()->Primes()[i] << " ";
    }
    fout << "\n";

    ftime << "PrimesCount : Encoded/decoded : Value : Time (ns)" << std::endl;

    for (int i = 0; i < TEST_AMOUNT; i++)
    {
        encoded = rander.RandInt32();

        RNSVector test{ crypter };

        start = std::chrono::high_resolution_clock::now();
        test.Encode(encoded);
        end = std::chrono::high_resolution_clock::now();

        ftime << crypter.get()->Size() << " : " << "Encoded : " << encoded << " : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        decoded = test.Normalize().Decode(); 
        end = std::chrono::high_resolution_clock::now();

        ftime << crypter.get()->Size() << " : " << "Decoded : " << encoded << " : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

        fout << i << "\n:encoded=" << encoded << "\n:decoded=" << decoded << "\n:RNS= ";
        fout << test.ToString() << ":";

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
    ftime.close();

    return errNumber;

    return 0;
}


int ArithmeticTest(
    const char* resultOutputFile, 
    const char* perfomanceOutputFile,
    const std::shared_ptr<RNSCrypter>& crypter,
    char cBinOperator)
{
    if (cBinOperator != '+' && cBinOperator != '-' && cBinOperator != '*') return -1;

    std::ofstream fout{ resultOutputFile };
    std::ofstream ftime{ perfomanceOutputFile };

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    IntRandomizer rander;

    int errNumber = 0;
    bool bInnerError = false;
    size_t matrixSize = 0;
    uint32_t tmp = 0;

    for (int i = 0; i < crypter.get()->Size(); i++) fout << crypter.get()->Primes()[i] << " ";
    fout << "\n";

    ftime << "PrimesCount : Matrix size : Operation : Time for simple type (ns) : Time for RNS (ns)" << std::endl;

    for (int i = 0; i < TEST_AMOUNT; i++)
    {
        matrixSize = rander.RandInt32(3, 11);

        bInnerError = false;

        Matrix<uint32_t> a{ matrixSize, 0 }, b{ matrixSize, 0 };
        Matrix<RNSVector> rnsA{ matrixSize, RNSVector{crypter} }, rnsB{ matrixSize, RNSVector{crypter} };

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

                rnsA[row][col].Encode(a[row][col]);
                rnsB[row][col].Encode(b[row][col]);
            }
        }

        fout << "m1:\n" << a.ToString();
        fout << "m2:\n" << b.ToString();
        fout << "(rns)m1:\n" << rnsA.ToString();
        fout << "(rns)m2:\n" << rnsB.ToString();

        switch (cBinOperator)
        {
        case '+':
            start = std::chrono::high_resolution_clock::now();
            a.Add(b);
            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << a.size() << " : + : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();
            rnsA.Add(rnsB);
            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

            break;
        case '-':
            start = std::chrono::high_resolution_clock::now();
            a.Sub(b);
            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << a.size() << " : - : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();
            rnsA.Sub(rnsB);
            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

            break;
        case '*':
            start = std::chrono::high_resolution_clock::now();
            a.Mul(b);
            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << a.size() << " : * : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();
            rnsA.Mul(rnsB);
            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;
            
            break;
        default:
            fout.close();
            return -1;
        }

        fout << "(rns)m1"<< cBinOperator <<"m2:\n" << rnsA.ToString();
        fout << "(rns)m1" << cBinOperator << "m2:\n" << rnsA.ToString();
        fout << "m1"<< cBinOperator <<"m2:\n" << a.ToString();

        fout << "(decoded)m1"<< cBinOperator <<"m2:\n";
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                tmp = rnsA[row][col].Normalize().Decode();

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
    ftime.close();

    return errNumber;

    return 0;
}
