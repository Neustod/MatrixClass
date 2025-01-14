#include "Tests.h"
#include <fstream>
#include <chrono>
#include "RNSVector.h"
#include "RNSMatrix.h"

#define TEST_RATIO std::chrono::nanoseconds


int DecodeTest(const char* resultOutputFile, const char* perfomanceOutputFile, const std::shared_ptr<RNSCrypter>& crypter)
{
    std::ofstream fout{ resultOutputFile };
    std::ofstream ftime{ perfomanceOutputFile };

    uint32_t encoded, decoded;
    IntRandomizer rander;

    int errNumber = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;


    for (size_t i = 0; i < crypter.get()->Size(); i++) 
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
    size_t matrixCount = 0;
    uint32_t tmp = 0;

    RNSVectorLight error{ crypter.get()->OverflowErrorValue(), crypter.get()->Size() };

    for (size_t i = 0; i < crypter.get()->Size(); i++) fout << (uint16_t)crypter.get()->Primes()[i] << " ";
    fout << "\n";

    ftime << "PrimesCount : Matrix size : Operation : Operations amount : Time for simple type (ns) : Time for RNS (ns)" << std::endl;

    for (size_t i = 0; i < TEST_AMOUNT; i++)
    {
        matrixSize = rander.RandInt32(MIN_MATRIX_SIZE, MAX_MATRIX_SIZE + 1);
        matrixCount = rander.RandInt32(MIN_MATRIX_AMOUNT, MAX_MATRIX_AMOUNT + 1);

        bInnerError = false;

        std::vector<Matrix<uint32_t>> simpMatrixes(matrixCount, Matrix<uint32_t>{ 0, matrixSize });
        std::vector<RNSMatrixLight> rnsMatrixes(matrixCount, RNSMatrixLight{ crypter.get()->Size(), matrixSize });

        fout << i << ":\nsize=" << matrixSize << ":\n";

        size_t part{ matrixCount };

        for (size_t index = 0; index < matrixCount; index++) 
        {
            for (size_t row = 0; row < matrixSize; row++)
            {
                for (size_t col = 0; col < matrixSize; col++)
                {
                    if (cBinOperator != '-')
                    {
                        simpMatrixes[index][row][col] = rander.RandInt32(0, RIGHT_BORDER);
                    }
                    else
                    {
                        simpMatrixes[index][row][col] = rander.RandInt32(RIGHT_BORDER / matrixCount * (part - 1), RIGHT_BORDER / matrixCount * part);
                    }

                    crypter.get()->Encode(rnsMatrixes[index][row][col].Digits(), simpMatrixes[index][row][col]);
                }
            }

            --part;
        }

        for (size_t j = 0; j < matrixCount; j++) 
        {
            fout << "Matrix " << j + 1 << ":\n" << simpMatrixes[j].ToString();
            fout << "RNSMatrix " << j + 1 << ":\n" << rnsMatrixes[j].ToString();
        }


        switch (cBinOperator)
        {
        case '+':
            start = std::chrono::high_resolution_clock::now();

            for (size_t j = 1; j < matrixCount; j++) 
            {
                simpMatrixes[0].Add(simpMatrixes[j]);
            }

            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << matrixSize << " : + : " << matrixCount - 1 << " : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();
            
            for (size_t j = 1; j < matrixCount; j++)
            {
                rnsMatrixes[0].Add(rnsMatrixes[j]);
            }
            rnsMatrixes[0].OverflowCorrection(error);

            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

            break;
        case '-':
            start = std::chrono::high_resolution_clock::now();

            for (size_t j = 1; j < matrixCount; j++)
            {
                simpMatrixes[0].Sub(simpMatrixes[j]);
            }

            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << matrixSize << " : - : " << matrixCount - 1 << " : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();

            for (size_t j = 1; j < matrixCount; j++)
            {
                rnsMatrixes[0].Sub(rnsMatrixes[j]);
            }
            rnsMatrixes[0].SingleOverflowCorrection(error);

            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

            break;
        case '*':
            start = std::chrono::high_resolution_clock::now();

            for (size_t j = 1; j < matrixCount; j++)
            {
                simpMatrixes[0].Mul(simpMatrixes[j]);
            }

            end = std::chrono::high_resolution_clock::now();

            ftime << crypter.get()->Size() << " : " << matrixSize << " : * : " << matrixCount - 1 << " : " << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << " : ";

            start = std::chrono::high_resolution_clock::now();

            for (size_t j = 1; j < matrixCount; j++)
            {
                rnsMatrixes[0].Mul(rnsMatrixes[j], error);
                rnsMatrixes[0].OverflowCorrection(error);
            }

            end = std::chrono::high_resolution_clock::now();

            ftime << std::chrono::duration_cast<TEST_RATIO>(end - start).count() << std::endl;

            break;
        default:
            fout.close();
            return -1;
        }

        fout << matrixCount - 1 << " " << cBinOperator << "operations for RNSMatrix:\n" << rnsMatrixes[0].ToString();
        fout << matrixCount - 1 << " " << cBinOperator << "operations for IntMatrix:\n" << simpMatrixes[0].ToString();

        fout << "Decoded RNSMatrix:\n";
        for (size_t row = 0; row < matrixSize; row++)
        {
            for (size_t col = 0; col < matrixSize; col++)
            {
                tmp = (RNSVector{ crypter, rnsMatrixes[0][row][col] }).Normalize().Decode();

                if (tmp != simpMatrixes[0][row][col]) bInnerError = true;

                if (col + 1 == matrixSize)
                    fout << tmp;
                else
                    fout << tmp << ":";
            }
            fout << "\n";
        }

        fout << (bInnerError ? "false" : "true") << ";\n\n";

        errNumber += bInnerError;
    }

    fout.close();
    ftime.close();

    return errNumber;

    return 0;
}
