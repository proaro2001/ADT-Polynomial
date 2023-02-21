//-------------------------------------- PolynomialDriver.cpp--------------------------------------
// 
// PolynomialDriver.cpp CSS 343
// 
// Jan 14 2023
// 
// Jan 14 2023
// 
// ------------------------------------------------------------------------------------------------
// 
// Purpose - Test if the polynomial.cpp functions meet the requirement
// 
// ------------------------------------------------------------------------------------------------
// 
// Notes on specifications, special algorithms, and assumptions.
// assumptions: I assume this is the only driver to test ( comment out the
// driver.cpp before use )
// 
// ------------------------------------------------------------------------------------------------
#include "polynomial.h"
#include <iostream>

using namespace std;

int main() 
{
    // Test default constructor
    Polynomial p1;
    cout << "p1(default constructor): " << p1 << endl;
    cout << "p1 degree: " << p1.degree() << endl;
    cout << "p1 coefficient at power 2: " << p1.coefficient(2) << endl;

    // Test changeCoefficient
    p1.changeCoefficient(5, 2);
    p1.changeCoefficient(-3, 0);
    cout << "p1(after changeCoefficient): " << p1 << endl;

    // Test copy constructor
    Polynomial p2(p1);
    cout << "p2(copy constructor from p1): " << p2 << endl;

    // Test degree and coefficient
    cout << "p2 degree: " << p2.degree() << endl;
    cout << "p2 coefficient at power 2: " << p2.coefficient(2) << endl;

    // Test arithmetic operators
    Polynomial p3;
    p3.changeCoefficient(3, 2);
    p3.changeCoefficient(2, 1);
    cout << "p3: " << p3 << endl;
    Polynomial p4 = p2 + p3;
    cout << "p4 = p2 + p3: " << p4 << endl;
    p4 = p2 - p3;
    cout << "p4 = p2 - p3: " << p4 << endl;

    // Test boolean comparison operators
    cout << "p2 == p3: " << (p2 == p3) << endl;
    cout << "p2 != p3: " << (p2 != p3) << endl;

    // Test assignment operators
    Polynomial p5;
    p5 += p3;
    cout << "p5 += p3: " << p5 << endl;
    p5 -= p2;
    cout << "p5 -= p2: " << p5 << endl;
    p5 = p2;
    cout << "p5 = p2: " << p5 << endl;
}