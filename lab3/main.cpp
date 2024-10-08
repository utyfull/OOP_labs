#include "lab3.h"

int main() {
    Array array(10);  // Создаем массив с максимальной вместимостью 10 фигур

    // Создаем фигуры
    Trapezoid* trapezoid = new Trapezoid();
    Rhomb* rhomb = new Rhomb();
    Pentagon* pentagon = new Pentagon();

    // Инициализируем фигуры (например, с помощью оператора >>)
    std::cout << "Введите координаты для трапеции (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *trapezoid; // предполагаем, что оператор >> перегружен

    std::cout << "Введите координаты для ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *rhomb;

    std::cout << "Введите координаты для пятиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
    std::cin >> *pentagon;

    // Добавляем фигуры в массив
    array.addFigure(trapezoid);
    array.addFigure(rhomb);
    array.addFigure(pentagon);

    // Печатаем геометрические центры и площади
    array.printFigures();

    // Печатаем общую площадь
    std::cout << "Общая площадь фигур в массиве: " << array.totalArea() << std::endl;

    // Удаляем фигуру по индексу (например, удаляем фигуру с индексом 1)
    array.removeFigure(1);

    // Печатаем фигуры после удаления
    std::cout << "После удаления фигуры с индексом 1:" << std::endl;
    array.printFigures();

    // Очистка памяти (необходимо, если используется raw указатели)
    // Поскольку удаление происходит в деструкторе массива, мы можем просто выйти из программы

    return 0;
}