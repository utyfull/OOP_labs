#include "lab3.h"

//Figure class methods
double Figure::getArea() const {
    if (!_areaCalculated) {
        _area = static_cast<double>(*this); 
        _areaCalculated = true;  
    }
    return _area;
}

double Figure::getFigureCenter() const {
    if (!_centerCalculated) {
        calculateFigureCenter();
        _centerCalculated = true; 
    }
    return _centerX; 
}

//Array class methods
Array::Array() : _capacity(10), _size(0) {
    _elements = new Figure*[_capacity];
}

Array::Array(size_t capacity) : _capacity(capacity), _size(0) {
    _elements = new Figure*[_capacity];
}

Array::~Array() noexcept {
    for (size_t i = 0; i < _size; ++i) {
        delete _elements[i];  
    }
    delete[] _elements; 
}

void Array::addFigure(Figure* figure) {
    if (_size >= _capacity) {
        _capacity *= 2;
        Figure** newElements = new Figure*[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newElements[i] = _elements[i];
        }
        delete[] _elements;
        _elements = newElements;
    }
    _elements[_size++] = figure; 
}

void Array::removeFigure(size_t index) {
    if (index < _size) {
        delete _elements[index]; 
        for (size_t i = index; i < _size - 1; ++i) {
            _elements[i] = _elements[i + 1]; 
        }
        --_size; 
    }
}

void Array::printFigures() const {
    for (size_t i = 0; i < _size; ++i) {
        std::cout << *_elements[i] << std::endl; 
    }
}

double Array::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < _size; ++i) {
        total += _elements[i]->getArea(); 
    }
    return total;
}

//Trapezoid class methods 
void Trapezoid::calculateFigureCenter() const {
    _centerX = (__x1 + __x2 + __x3 + __x4) / 4;
    _centerY = (__y1 + __y2 + __y3 + __y4) / 4;
    _centerCalculated = true; 
}

Trapezoid::operator double() const {
    return 0.5 * (abs(__y2 - __y1) + abs(__y3 - __y4)) * abs(__x2 - __x1);
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid) {
    os << "Trapezoid: ((" << trapezoid.__x1 << ", " << trapezoid.__y1 << "), ("
       << trapezoid.__x2 << ", " << trapezoid.__y2 << "), ("
       << trapezoid.__x3 << ", " << trapezoid.__y3 << "), ("
       << trapezoid.__x4 << ", " << trapezoid.__y4 << "))";
    return os;
}

std::istream& operator>>(std::istream& is, Trapezoid& trapezoid) {
    is >> trapezoid.__x1 >> trapezoid.__y1
       >> trapezoid.__x2 >> trapezoid.__y2
       >> trapezoid.__x3 >> trapezoid.__y3
       >> trapezoid.__x4 >> trapezoid.__y4;
    return is;
}

//Rhomb class methods
void Rhomb::calculateFigureCenter() const {
    _centerX = (__x1 + __x2 + __x3 + __x4) / 4;
    _centerY = (__y1 + __y2 + __y3 + __y4) / 4;
    _centerCalculated = true;
}

Rhomb::operator double() const {
    return (abs(__x1 - __x3) * abs(__y2 - __y4));
}

std::ostream& operator<<(std::ostream& os, const Rhomb& rhomb) {
    os << "Rhomb: ((" << rhomb.__x1 << ", " << rhomb.__y1 << "), ("
       << rhomb.__x2 << ", " << rhomb.__y2 << "), ("
       << rhomb.__x3 << ", " << rhomb.__y3 << "), ("
       << rhomb.__x4 << ", " << rhomb.__y4 << "))";
    return os;
}

std::istream& operator>>(std::istream& is, Rhomb& rhomb) {
    is >> rhomb.__x1 >> rhomb.__y1
       >> rhomb.__x2 >> rhomb.__y2
       >> rhomb.__x3 >> rhomb.__y3
       >> rhomb.__x4 >> rhomb.__y4;
    return is;
}

//Pentagon class methods
void Pentagon::calculateFigureCenter() const {
    _centerX = (__x1 + __x2 + __x3 + __x4 + __x5) / 5;
    _centerY = (__y1 + __y2 + __y3 + __y4 + __y5) / 5;
    _centerCalculated = true;
}

Pentagon::operator double() const {
    return (5 * __x1 * __y1) / 2; 
}

std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon) {
    os << "Pentagon: ((" << pentagon.__x1 << ", " << pentagon.__y1 << "), ("
       << pentagon.__x2 << ", " << pentagon.__y2 << "), ("
       << pentagon.__x3 << ", " << pentagon.__y3 << "), ("
       << pentagon.__x4 << ", " << pentagon.__y4 << "), ("
       << pentagon.__x5 << ", " << pentagon.__y5 << "))";
    return os;
}

std::istream& operator>>(std::istream& is, Pentagon& pentagon) {
    is >> pentagon.__x1 >> pentagon.__y1
       >> pentagon.__x2 >> pentagon.__y2
       >> pentagon.__x3 >> pentagon.__y3
       >> pentagon.__x4 >> pentagon.__y4
       >> pentagon.__x5 >> pentagon.__y5;
    return is;
}