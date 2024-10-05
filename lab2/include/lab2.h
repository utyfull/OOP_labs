#ifndef LAB2_H
#define LAB2_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <string>

class Array {
protected:
    unsigned char* _digits;
    size_t _capacity;
    size_t _size;

public:
    Array(); // Конструктор по умолчанию
    Array(size_t capacity); // Новый конструктор для инициализации массива определенной вместимости
    Array(const std::initializer_list<unsigned char>& digits);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;

    Array& operator+=(const Array& other);
    Array& operator-=(const Array& other);

    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    bool operator<(const Array& other) const;
    bool operator>(const Array& other) const;
};

class Hex : public Array {
public:
    // Конструкторы
    Hex();
    Hex(const std::string& hexStr);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    virtual ~Hex() noexcept;

    // Операторы присваивания
    Hex& operator=(const Hex& other);
    Hex& operator=(Hex&& other) noexcept;

    // Арифметические операции с присваиванием
    Hex& operator+=(const Hex& other);
    Hex& operator-=(const Hex& other);

    // Операторы сравнения
    bool operator==(const Hex& other) const;
    bool operator!=(const Hex& other) const;
    bool operator<(const Hex& other) const;
    bool operator>(const Hex& other) const;

    // Преобразование в строку
    std::string toString() const;

private:
    // Приватные методы для конвертации символов
    unsigned char charToHex(char c) const;
    char hexToChar(unsigned char hexVal) const;

    // Приватные методы для работы с числами
    std::string hexOperation(const std::string& hex1, const std::string& hex2, char operation);
    int hexCompare(const std::string& hex1, const std::string& hex2) const;
};

#endif