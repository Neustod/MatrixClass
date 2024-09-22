#include <iostream>
#include <fstream>
#include "Tests.h"


using namespace std;


// TESTING
int main()
{
    std::vector<uint32_t> prime1 = { 7, 11, 13, 17, 19, 23, 29, 31 };
    std::vector<uint32_t> prime2 = { 255, 256, 257, 511 };
    std::vector<uint32_t> prime3 = { 3, 7, 8, 13, 29, 31, 43, 53 };
    std::vector<uint32_t> prime4 = { 7, 11, 13, 15, 31, 127, 128 };
    std::vector<uint32_t> prime5 = { 16, 17, 31, 63, 65, 127 };
    std::vector<uint32_t> prime6 = { 5, 17, 19, 23, 31, 61, 63 };
    std::vector<uint32_t> prime7 = { 17, 19, 23, 25, 26, 29, 31 };

    RNSCrypter coder1{ prime1.data(),prime1.size() };
    RNSCrypter coder2{ prime2.data(),prime2.size() };
    RNSCrypter coder3{ prime3.data(),prime3.size() };
    RNSCrypter coder4{ prime4.data(),prime4.size() };
    RNSCrypter coder5{ prime5.data(),prime5.size() };
    RNSCrypter coder6{ prime6.data(),prime6.size() };
    RNSCrypter coder7{ prime7.data(),prime7.size() };

    cout << "AddTest: " << AddTest("AddTest0.txt", coder1) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest1.txt", coder2) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest2.txt", coder3) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest3.txt", coder4) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest4.txt", coder5) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest5.txt", coder6) << " errors." << endl;
    cout << "AddTest: " << AddTest("AddTest6.txt", coder7) << " errors." << endl;

    cout << "MulTest: " << MulTest("MulTest0.txt", coder1) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest1.txt", coder2) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest2.txt", coder3) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest3.txt", coder4) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest4.txt", coder5) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest5.txt", coder6) << " errors." << endl;
    cout << "MulTest: " << MulTest("MulTest6.txt", coder7) << " errors." << endl;

    system("pause");
    return 0;
}

