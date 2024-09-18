#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int x = 3;
    int y = 4;

    std::cout << "Summ " << x << " and " << y << " equal " << add(x, y) << std::endl;

    return 0;
}