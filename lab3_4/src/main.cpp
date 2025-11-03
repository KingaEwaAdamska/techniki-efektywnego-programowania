#include <iostream>
#include "Number.hpp"

int main() {
    Number a, b, c;
    a = 9001234;
    b = 213;
    a = a - b;
    std::cout << "a: " << a.toStr() << std::endl;
    // std::cout << "=== TESTY DODAWANIA ===" << std::endl;
    //
    // // Dodatnie + dodatnie
    // a = 5; b = 3; c = a + b;
    // std::cout << "5 + 3 = " << c.toStr() << " (8)" << std::endl;
    //
    // // Ujemne + ujemne
    // a = -5; b = -3; c = a + b;
    // std::cout << "-5 + -3 = " << c.toStr() << " (-8)" << std::endl;
    //
    // // Ujemna + dodatnia (dodatnia większa)
    // a = -3; b = 5; c = a + b;
    // std::cout << "-3 + 5 = " << c.toStr() << " (2)" << std::endl;
    //
    // // Ujemna + dodatnia (ujemna większa)
    // a = -5; b = 3; c = a + b;
    // std::cout << "-5 + 3 = " << c.toStr() << " (-2)" << std::endl;
    //
    // // Dodatnia + ujemna (dodatnia większa)
    // a = 5; b = -3; c = a + b;
    // std::cout << "5 + -3 = " << c.toStr() << " (2)" << std::endl;
    //
    // // Dodatnia + ujemna (ujemna większa)
    // a = 3; b = -5; c = a + b;
    // std::cout << "3 + -5 = " << c.toStr() << " (-2)" << std::endl;
    //
    // // Zera i kombinacje z zerem
    // a = 0; b = 5; c = a + b;
    // std::cout << "0 + 5 = " << c.toStr() << " (5)" << std::endl;
    //
    // a = 5; b = 0; c = a + b;
    // std::cout << "5 + 0 = " << c.toStr() << " (5)" << std::endl;
    //
    // a = 0; b = 0; c = a + b;
    // std::cout << "0 + 0 = " << c.toStr() << " (0)" << std::endl;
    //
    //
    // std::cout << "\n=== TESTY ODEJMOWANIA ===" << std::endl;
    //
    // // Dodatnie - dodatnie (większa - mniejsza)
    // a = 5; b = 3; c = a - b;
    // std::cout << "5 - 3 = " << c.toStr() << " (2)" << std::endl;
    //
    // // Dodatnie - dodatnie (mniejsza - większa)
    // a = 3; b = 5; c = a - b;
    // std::cout << "3 - 5 = " << c.toStr() << " (-2)" << std::endl;
    //
    // // Ujemne - ujemne (większa wartość bezwzględna)
    // a = -5; b = -3; c = a - b;
    // std::cout << "-5 - -3 = " << c.toStr() << " (-2)" << std::endl;
    //
    // // Ujemne - ujemne (mniejsza wartość bezwzględna)
    // a = -3; b = -5; c = a - b;
    // std::cout << "-3 - -5 = " << c.toStr() << " (2)" << std::endl;
    //
    // // Ujemna - dodatnia
    // a = -5; b = 3; c = a - b;
    // std::cout << "-5 - 3 = " << c.toStr() << " (-8)" << std::endl;
    //
    // // Dodatnia - ujemna
    // a = 5; b = -3; c = a - b;
    // std::cout << "5 - -3 = " << c.toStr() << " (8)" << std::endl;
    //
    // // Kombinacje z zerem
    // a = 0; b = 5; c = a - b;
    // std::cout << "0 - 5 = " << c.toStr() << " (-5)" << std::endl;
    //
    // a = 5; b = 0; c = a - b;
    // std::cout << "5 - 0 = " << c.toStr() << " (5)" << std::endl;
    //
    // a = 0; b = 0; c = a - b;
    // std::cout << "0 - 0 = " << c.toStr() << " (0)" << std::endl;
    //
    //
    // std::cout << "\n=== TESTY DUŻYCH LICZB ===" << std::endl;
    //
    // a = 1000000; b = 999999; c = a + b;
    // std::cout << "1000000 + 999999 = " << c.toStr() << " (1999999)" << std::endl;
    //
    // a = -1000000; b = -999999; c = a + b;
    // std::cout << "-1000000 + -999999 = " << c.toStr() << " (-1999999)" << std::endl;
    //
    // a = 1000000; b = -999999; c = a + b;
    // std::cout << "1000000 + -999999 = " << c.toStr() << " (1)" << std::endl;
    //
    // a = -1000000; b = 999999; c = a + b;
    // std::cout << "-1000000 + 999999 = " << c.toStr() << " (-1)" << std::endl;
    //
    return 0;
}

