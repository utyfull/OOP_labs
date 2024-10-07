#ifndef LAB3_H
#define LAB3_H

#include <iostream>

class Figure {
protected:
    double _centerX;
    double _centerY;
public:
    Figure(): _centerX(0.0), _centerY(0.0) {}

    virtual void calculateFigureCenter() const {}

    friend std::ostream&operator<<(std::ostream& os, const Figure& figure) {}
    friend std::istream&operator>>(std::istream is, Figure& figure) {}
    virtual operator double() const {}

    virtual ~Figure() {}
};



class Array {
protected:
    Figure* _elements;
    size_t _capacity;
    size_t _size;

public:
    Array(); 
    Array(size_t capacity); 
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
};

class


#endif