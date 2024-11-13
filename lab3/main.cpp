#include "lab3.h"

// int main() {
//     // Создаем массив для хранения фигур, используя shared_ptr для управления памятью
//     Array<std::shared_ptr<Figure<double>>> array(10); 

//     // Создаем фигуры с использованием shared_ptr
//     auto trapezoid = std::make_shared<Trapezoid<double>>();
//     auto rhomb = std::make_shared<Rhomb<double>>();
//     auto pentagon = std::make_shared<Pentagon<double>>();

//     // Ввод координат для трапеции
//     std::cout << "Введите координаты для трапеции (x1 y1 x2 y2 x3 y3 x4 y4): ";
//     std::cin >> *trapezoid; 

//     // Ввод координат для ромба
//     std::cout << "Введите координаты для ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
//     std::cin >> *rhomb;

//     // Ввод координат для пятиугольника
//     std::cout << "Введите координаты для пятиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
//     std::cin >> *pentagon;

//     // Добавляем фигуры в массив
//     array.addFigure(trapezoid); // Передаем указатели на фигуры
//     array.addFigure(rhomb);
//     array.addFigure(pentagon);

//     // Печатаем все фигуры
//     std::cout << "Все фигуры в массиве:" << std::endl;
//     array.printFigures();

//     // Выводим общую площадь фигур в массиве
//     std::cout << "Общая площадь фигур в массиве: " << array.totalArea() << std::endl;

//     // Удаляем фигуру с индексом 1
//     array.removeFigure(1);

//     std::cout << "После удаления фигуры с индексом 1:" << std::endl;
//     array.printFigures();

//     return 0;
// }