#include <iostream>
#include "Matrix.h"

using namespace std;


// TESTING
int main()
{
    system("chcp 1251 > null");

    Matrix m1(3);
    Matrix m2(3);
    Matrix m3;

    m1.Randomize(0, 10);
    m2.Randomize(0, 10);

    cout << "Matrix A:\n";
    m1.Output();
    cout << "\nMatrix B:\n";
    m2.Output();

    m3 = Matrix::Mul(m1, m2);
    m1.Mul(m2);
    
    cout << "\nMatrix C1:\n";
    m1.Output();

    cout << "\nMatrix C2:\n";
    m3.Output();

    system("pause");
    return 0;
}

