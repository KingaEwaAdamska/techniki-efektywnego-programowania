#include <iostream>
#include "Number.hpp"

int main() {
    Number a, b, c;
    a = 123; b = 456; c = a + b;
    std::cout << "123 + 456 = " << c.toStr() << " (579)" << std::endl;

    a = 789; b = -123; c = a + b;
    std::cout << "789 + (-123) = " << c.toStr() << " (666)" << std::endl;

    a = -456; b = 789; c = a + b;
    std::cout << "-456 + 789 = " << c.toStr() << " (333)" << std::endl;

    a = 987; b = 654; c = a - b;
    std::cout << "987 - 654 = " << c.toStr() << " (333)" << std::endl;

    a = 321; b = -123; c = a - b;
    std::cout << "321 - (-123) = " << c.toStr() << " (444)" << std::endl;

    a = -555; b = 222; c = a - b;
    std::cout << "-555 - 222 = " << c.toStr() << " (-777)" << std::endl;

    a = 111; b = 9; c = a * b;
    std::cout << "111 * 9 = " << c.toStr() << " (999)" << std::endl;

    a = 250; b = -4; c = a * b;
    std::cout << "250 * (-4) = " << c.toStr() << " (-1000)" << std::endl;

    a = -125; b = -8; c = a * b;
    std::cout << "-125 * (-8) = " << c.toStr() << " (1000)" << std::endl;

    a = 999; b = -3; c = a / b;
    std::cout << "999 / 3 = " << c.toStr() << " (333)" << std::endl;

    a = 888; b = -4; c = a / b;
    std::cout << "888 / (-4) = " << c.toStr() << " (-222)" << std::endl;

    a = -750; b = 5; c = a / b;
    std::cout << "-750 / 5 = " << c.toStr() << " (-150)" << std::endl;

    a = -750; b = -5; c = a / b;
    std::cout << "-750 / -5 = " << c.toStr() << " (150)" << std::endl;

    return 0;
}

