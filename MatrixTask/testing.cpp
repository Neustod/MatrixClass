#include <iostream>
#include "Tests.h"
#include <string>


using namespace std;


// TESTING
int main()
{
    vector<RNSCrypter> cryps;
    string filename;

    vector<vector<uint32_t>> primes
    {
        { 7, 11, 13, 17, 19, 23, 29, 31 },
        { 255, 256, 257, 511 },
        { 3, 7, 8, 13, 29, 31, 43, 53 },
        { 7, 11, 13, 15, 31, 127, 128 },
        { 16, 17, 31, 63, 65, 127 },
        { 5, 17, 19, 23, 31, 61, 63 },
        { 17, 19, 23, 25, 26, 29, 31 }
    };

    for (int i = 0; i < primes.size(); i++)
    {
        cryps.push_back({ primes[i].data(), primes[i].size() });
    }

    for (int i = 0; i < cryps.size(); i++)
    {
        filename = "DecodeTest" + to_string(i) + ".txt";
        cout << "DecodeTest errors: " << DecodeTest(filename.c_str(), cryps[i]) << endl;

        filename = "AddTestTest" + to_string(i) + ".txt";
        cout << "AddTest errors: " << ArithmeticTest(filename.c_str(), cryps[i], '+') << endl;

        filename = "SubTest" + to_string(i) + ".txt";
        cout << "SubTest errors: " << ArithmeticTest(filename.c_str(), cryps[i], '-') << endl;

        filename = "MulTest" + to_string(i) + ".txt";
        cout << "MulTest errors: " << ArithmeticTest(filename.c_str(), cryps[i], '*') << "\n\n";
    }

    system("pause");
    return 0;
}
