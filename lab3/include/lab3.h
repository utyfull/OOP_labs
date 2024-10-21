#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

class Figure {
protected:
    mutable double _area;
    mutable bool _areaCalculated;
    mutable double _centerX, _centerY;
    mutable bool _centerCalculated;

public:
    Figure() : _area(0), _areaCalculated(false), _centerX(0), _centerY(0), _centerCalculated(false) {}
    double getArea() const;
    double getFigureCenter() const;

    virtual void calculateFigureCenter() const = 0;
    virtual operator double() const = 0;

    virtual ~Figure() {}
};


class Array {
protected:
    Figure** _elements;  
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

    void addFigure(Figure* figure);
    void removeFigure(size_t index);
    void printFigures() const;
    double totalArea() const;
};

class Trapezoid: public Figure {
private:
    double __x1, __x2, __x3, __x4, __y1, __y2, __y3, __y4;
public:
    Trapezoid(): __x1(0), __x2(0), __x3(0), __x4(0), __y1(0), __y2(0), __y3(0), __y4(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    bool operator==(const Trapezoid& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid);
    friend std::istream& operator>>(std::istream& is, Trapezoid& trapezoid);
};

class Rhomb: public Figure {
private:
    double __x1, __x2, __x3, __x4, __y1, __y2, __y3, __y4;
public:
    Rhomb(): __x1(0), __x2(0), __x3(0), __x4(0), __y1(0), __y2(0), __y3(0), __y4(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;
    bool operator==(const Rhomb& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rhomb& rhomb);
    friend std::istream& operator>>(std::istream& is, Rhomb& rhomb);
};

class Pentagon: public Figure {
private:
    double __x1, __x2, __x3, __x4, __x5, __y1, __y2, __y3, __y4, __y5;
public:
    Pentagon(): __x1(0), __x2(0), __x3(0), __x4(0), __x5(0), __y1(0), __y2(0), __y3(0), __y4(0), __y5(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
    bool operator==(const Pentagon& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon);
    friend std::istream& operator>>(std::istream& is, Pentagon& pentagon);
};



#endif