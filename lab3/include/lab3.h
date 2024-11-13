#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <concepts>
#include <cmath>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    T first, second; 

    Point(T first = 0, T second = 0) : first(first), second(second) {}
};

template <Scalar T>
class Figure {
protected:
    mutable double _area;
    mutable bool _areaCalculated;
    mutable double _centerX, _centerY;
    mutable bool _centerCalculated;
    std::vector<std::unique_ptr<Point<T>>> vertices;

public:
    Figure() : _area(0), _areaCalculated(false), _centerX(0), _centerY(0), _centerCalculated(false) {}

    T getArea() const;  
    Point<T> getFigureCenter() const;  

    virtual void calculateFigureCenter() const = 0;
    virtual operator T() const = 0;

    virtual ~Figure() {}
};

template <class T>
class Array {
private:
    std::shared_ptr<T[]> _elements;
    size_t _capacity;   
    size_t _size;        

public:
    Array() : _capacity(10), _size(0), _elements(std::make_shared<T[]>(_capacity)) {}
    Array(size_t capacity) : _capacity(capacity), _size(0), _elements(std::make_shared<T[]>(_capacity)) {} 
    Array(const Array& other) : _capacity(other._capacity), _size(other._size), _elements(std::make_shared<T[]>(_capacity)) {
        for (size_t i = 0; i < _size; ++i) {
            _elements[i] = other._elements[i];
        }
    }
    Array(Array&& other) noexcept : _capacity(other._capacity), _size(other._size), _elements(std::move(other._elements)) {
        other._capacity = 0;
        other._size = 0;
    }
    virtual ~Array() noexcept = default;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;

    void addFigure(T figure);
    void removeFigure(size_t index);
    void printFigures() const;
    double totalArea() const;
};

template <Scalar T>
class Trapezoid: public Figure<T> {
public:
    Trapezoid() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    void calculateFigureCenter() const override;
    operator double() const override;

    // Удаляем конструкторы копирования и присваивания, если не нужны
    Trapezoid(const Trapezoid&) = delete;
    Trapezoid& operator=(const Trapezoid&) = delete;

    // Другие методы...
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<U>& trapezoid);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Trapezoid<U>& trapezoid);
};

template <Scalar T>
class Rhomb: public Figure<T> {
public:
    Rhomb() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    void calculateFigureCenter() const override;
    operator double() const override;

    // Удаляем конструкторы копирования и присваивания, если не нужны
    Rhomb(const Rhomb&) = delete;
    Rhomb& operator=(const Rhomb&) = delete;

    // Другие методы...
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Rhomb<U>& rhomb);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Rhomb<U>& rhomb);
};

template <Scalar T>
class Pentagon: public Figure<T> {
public:
    Pentagon() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    void calculateFigureCenter() const override;
    operator double() const override;

    // Удаляем конструкторы копирования и присваивания, если не нужны
    Pentagon(const Pentagon&) = delete;
    Pentagon& operator=(const Pentagon&) = delete;

    // Другие методы...
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Pentagon<U>& pentagon);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Pentagon<U>& pentagon);
};

#endif
