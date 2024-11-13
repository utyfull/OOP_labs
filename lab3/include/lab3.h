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
public: // вот тут по-хорошему protected, но тогда нужно писать геттер и сеттер, а мне лень
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

// изначально код массива должен был быть не тут, но так вышло
template <class T>
class DynamicArray {
private:
    std::shared_ptr<T[]> data;  
    size_t size;                
    size_t capacity;            

public:
    DynamicArray() : size(0), capacity(10) {
        data = std::shared_ptr<T[]>(new T[capacity]);
    }

    void addFigure(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);  
        }

        for (size_t i = size; i > 0; --i) {
            data[i] = data[i - 1];
        }

        data[0] = value;
        ++size;
    }

    void removeFigure(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    void printFigures() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << *data[i] << std::endl;  
            }
        }
    }

    void printFigureCenters() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " center: " << data[i]->getFigureCenter().first << ", " << data[i]->getFigureCenter().second << std::endl;
            }
        }
    }

    void printVertices() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " vertices: ";
                for (const auto& vertex : (*data[i]).vertices) {
                    std::cout << "(" << vertex->first << ", " << vertex->second << ") ";
                }
                std::cout << std::endl;
            }
        }
    }

    void printAreas() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " area: " << data[i]->getArea() << std::endl;
            }
        }
    }

    double totalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                total += data[i]->getArea(); 
            }
        }
        return total;
    }

private:
    void resize(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }

        std::shared_ptr<T[]> new_data = std::shared_ptr<T[]>(new T[new_capacity]);

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        data = new_data;
        capacity = new_capacity;
    }
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

    Trapezoid(const Trapezoid&) = delete;
    Trapezoid& operator=(const Trapezoid&) = delete;

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

    Rhomb(const Rhomb&) = delete;
    Rhomb& operator=(const Rhomb&) = delete;

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

    Pentagon(const Pentagon&) = delete;
    Pentagon& operator=(const Pentagon&) = delete;

    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Pentagon<U>& pentagon);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Pentagon<U>& pentagon);
};

#endif
