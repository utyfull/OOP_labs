#include "lab3.h"

//Figure class methods
template <Scalar T>
T Figure<T>::getArea() const {
    if (!this->_areaCalculated) {
        this->_area = static_cast<double>(*this);  // Используем перегрузку оператора приведения типа
        this->_areaCalculated = true;  
    }
    return this->_area;
}

template <Scalar T>
Point<T> Figure<T>::getFigureCenter() const {
    if (!this->_centerCalculated) {
        calculateFigureCenter(); // Вычисление центра фигуры
        this->_centerCalculated = true; 
    }
    return Point<T>(this->_centerX, this->_centerY);  // Возвращаем центр как точку с double координатами
}

//Array class methods
template <class T>
void Array<T>::addFigure(T figure) {
        if (_size >= _capacity) {
            throw std::overflow_error("Array is full");
        }
        _elements[_size++] = figure;  // Добавляем фигуру и увеличиваем размер
    }

template <class T>
void Array<T>::removeFigure(size_t index) {
    if (index < _size) {
        for (size_t i = index; i < _size - 1; ++i) {
            _elements[i] = std::move(_elements[i + 1]); // Перемещаем элементы влево
        }
        --_size; // Уменьшаем размер
    }
}

template <class T>
void Array<T>::printFigures() const {
    for (size_t i = 0; i < _size; ++i) {
        if (_elements[i]) {
            std::cout << *_elements[i] << std::endl; // Выводим фигуры
        }
    }
}

template <class T>
double Array<T>::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < _size; ++i) {
        if (_elements[i]) {
            total += _elements[i]->getArea(); // Суммируем площади
        }
    }
    return total;
}

template <class T>
size_t Array<T>::size() const {
    return _size;
}

//Trapezoid class methods 
template <Scalar T>
void Trapezoid<T>::calculateFigureCenter() const {
    // Среднее арифметическое координат четырех вершин
    this->_centerX = (this->vertices[0]->first + this->vertices[1]->first +
                      this->vertices[2]->first + this->vertices[3]->first) / 4;
    this->_centerY = (this->vertices[0]->second + this->vertices[1]->second +
                      this->vertices[2]->second + this->vertices[3]->second) / 4;
    this->_centerCalculated = true;
}

template <Scalar T>
Trapezoid<T>::operator double() const {
    // Площадь трапеции: 0.5 * (высота1 + высота2) * ширина
    T height1 = std::abs(this->vertices[1]->second - this->vertices[0]->second);
    T height2 = std::abs(this->vertices[3]->second - this->vertices[2]->second);
    T width = std::abs(this->vertices[1]->first - this->vertices[0]->first);
    return 0.5 * (height1 + height2) * width;
}

template <Scalar U>
std::ostream& operator<<(std::ostream& os, const Trapezoid<U>& trapezoid) {
    os << "Trapezoid: ((" << trapezoid.vertices[0]->first << ", " << trapezoid.vertices[0]->second << "), ("
       << trapezoid.vertices[1]->first << ", " << trapezoid.vertices[1]->second << "), ("
       << trapezoid.vertices[2]->first << ", " << trapezoid.vertices[2]->second << "), ("
       << trapezoid.vertices[3]->first << ", " << trapezoid.vertices[3]->second << "))";
    return os;
}

template <Scalar U>
std::istream& operator>>(std::istream& is, Trapezoid<U>& trapezoid) {
    // Ввод координат четырех точек
    for (auto& vertex : trapezoid.vertices) {
        is >> vertex->first >> vertex->second;
    }
    return is;
}

//Rhomb class methods
template <Scalar T>
void Rhomb<T>::calculateFigureCenter() const {
    // Среднее арифметическое координат четырех вершин
    this->_centerX = (this->vertices[0]->first + this->vertices[1]->first +
                      this->vertices[2]->first + this->vertices[3]->first) / 4;
    this->_centerY = (this->vertices[0]->second + this->vertices[1]->second +
                      this->vertices[2]->second + this->vertices[3]->second) / 4;
    this->_centerCalculated = true;
}

template <Scalar T>
Rhomb<T>::operator double() const {
    // Площадь ромба: (диагональ1 * диагональ2) / 2
    T diagonal1 = std::abs(this->vertices[0]->first - this->vertices[2]->first);
    T diagonal2 = std::abs(this->vertices[1]->second - this->vertices[3]->second);
    return (diagonal1 * diagonal2) / 2;
}

template <Scalar U>
std::ostream& operator<<(std::ostream& os, const Rhomb<U>& rhomb) {
    os << "Rhomb: ((" << rhomb.vertices[0]->first << ", " << rhomb.vertices[0]->second << "), ("
       << rhomb.vertices[1]->first << ", " << rhomb.vertices[1]->second << "), ("
       << rhomb.vertices[2]->first << ", " << rhomb.vertices[2]->second << "), ("
       << rhomb.vertices[3]->first << ", " << rhomb.vertices[3]->second << "))";
    return os;
}

template <Scalar U>
std::istream& operator>>(std::istream& is, Rhomb<U>& rhomb) {
    // Ввод координат четырех точек
    for (auto& vertex : rhomb.vertices) {
        is >> vertex->first >> vertex->second;
    }
    return is;
}

//Pentagon class methods
template <Scalar T>
void Pentagon<T>::calculateFigureCenter() const {
    // Среднее арифметическое координат пяти вершин
    this->_centerX = (this->vertices[0]->first + this->vertices[1]->first + 
                      this->vertices[2]->first + this->vertices[3]->first + 
                      this->vertices[4]->first) / 5;
    this->_centerY = (this->vertices[0]->second + this->vertices[1]->second + 
                      this->vertices[2]->second + this->vertices[3]->second + 
                      this->vertices[4]->second) / 5;
    this->_centerCalculated = true;
}

template <Scalar T>
Pentagon<T>::operator double() const {
    // Площадь пятиугольника (приблизительная формула, например, через площадь треугольников)
    // Здесь используем пример формулы для площади регулярного пятиугольника
    T side = std::abs(this->vertices[0]->first - this->vertices[1]->first); // Пример: длина стороны
    return (5 * side * side) / (4 * std::tan(M_PI / 5)); // Площадь через сторону
}

template <Scalar U>
std::ostream& operator<<(std::ostream& os, const Pentagon<U>& pentagon) {
    os << "Pentagon: ((" << pentagon.vertices[0]->first << ", " << pentagon.vertices[0]->second << "), ("
       << pentagon.vertices[1]->first << ", " << pentagon.vertices[1]->second << "), ("
       << pentagon.vertices[2]->first << ", " << pentagon.vertices[2]->second << "), ("
       << pentagon.vertices[3]->first << ", " << pentagon.vertices[3]->second << "), ("
       << pentagon.vertices[4]->first << ", " << pentagon.vertices[4]->second << "))";
    return os;
}

template <Scalar U>
std::istream& operator>>(std::istream& is, Pentagon<U>& pentagon) {
    // Ввод координат пяти точек
    for (auto& vertex : pentagon.vertices) {
        is >> vertex->first >> vertex->second;
    }
    return is;
}

int main() {
    // Создаем массив для хранения фигур, используя shared_ptr для управления памятью
    Array<std::shared_ptr<Figure<double>>> array(10); 

    // Создаем фигуры с использованием shared_ptr
    auto trapezoid = std::make_shared<Trapezoid<double>>();
    auto rhomb = std::make_shared<Rhomb<double>>();
    auto pentagon = std::make_shared<Pentagon<double>>();

    // Ввод координат для трапеции
    std::cout << "Введите координаты для трапеции (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *trapezoid; 

    // Ввод координат для ромба
    std::cout << "Введите координаты для ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> *rhomb;

    // Ввод координат для пятиугольника
    std::cout << "Введите координаты для пятиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
    std::cin >> *pentagon;

    std::cout << "try to add\n";
    // Добавляем фигуры в массив
    array.addFigure(trapezoid); // Передаем указатели на фигуры
    array.addFigure(rhomb);
    array.addFigure(pentagon);
    std::cout << "try to use\n";
    // Печатаем все фигуры
    std::cout << "Все фигуры в массиве:" << std::endl;
    array.printFigures();

    // Выводим общую площадь фигур в массиве
    std::cout << "Общая площадь фигур в массиве: " << array.totalArea() << std::endl;

    // Удаляем фигуру с индексом 1
    array.removeFigure(1);

    std::cout << "После удаления фигуры с индексом 1:" << std::endl;
    array.printFigures();

    return 0;
}