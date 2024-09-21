#include <iostream>
#include "lab1.h"

int main()
{
    int a, b;
    std::cout << "Enter two integers: ";
    std::cin >> a >> b;

    if (std::cin.fail())
    {
        std::cerr << "Invalid input. Please enter integers only." << std::endl;
        return 1;
    }

    if (a < 0 || b < 0)
    {
        std::cerr << "Both numbers must be positive integers." << std::endl;
        return 1;
    }

    int gcd = CalculateGcd(a, b);
    std::cout << "The greatest common divisor is: " << gcd << std::endl;

    return 0;
}