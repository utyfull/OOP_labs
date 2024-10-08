#include "lab3.h"

int main() {
    Array array(10);  

    Trapezoid* trapezoid = new Trapezoid();
    Rhomb* rhomb = new Rhomb();
    Pentagon* pentagon = new Pentagon();

    std::cout << "Введите координаты для трапеции (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *trapezoid; 

    std::cout << "Введите координаты для ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *rhomb;

    std::cout << "Введите координаты для пятиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
    std::cin >> *pentagon;

    array.addFigure(trapezoid);
    array.addFigure(rhomb);
    array.addFigure(pentagon);

    array.printFigures();

    std::cout << "Общая площадь фигур в массиве: " << array.totalArea() << std::endl;

    array.removeFigure(1);

    std::cout << "После удаления фигуры с индексом 1:" << std::endl;
    array.printFigures();

    return 0;
}