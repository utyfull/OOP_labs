#include "lab2.h"

unsigned char charToHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    throw std::invalid_argument("Неверный символ шестнадцатеричного числа");
}

char hexToChar(unsigned char c) {
    if (c <= 9) return '0' + c;
    if (c >= 10 && c <= 15) return 'A' + (c - 10);
    throw std::invalid_argument("Неверное значение для шестнадцатеричной цифры");
}

//Array class methods
// Конструктор по умолчанию
Array::Array() : _digits(nullptr), _capacity(0), _size(0) {
    std::cout << "Array: Вызван конструктор по умолчанию\n";
}

//конструктор определенного размера
Array::Array(size_t size) : _digits(new unsigned char[size]), _capacity(size), _size(size) {
    std::cout << "Array: Вызван конструктор с размером " << size << std::endl;
    // Инициализируем массив нулями или другими значениями по умолчанию
    std::fill(_digits, _digits + size, '0');  
}

// Конструктор с инициализатором
Array::Array(const std::initializer_list<unsigned char>& digits) 
    : _capacity(digits.size()), _size(digits.size()) {
    std::cout << "Array: Вызван конструктор с инициализатором\n";
    _digits = new unsigned char[_capacity];
    std::copy(digits.begin(), digits.end(), _digits);
}

// Копирующий конструктор
Array::Array(const Array& other) : _capacity(other._capacity), _size(other._size) {
    std::cout << "Array: Вызван копирующий конструктор\n";
    _digits = new unsigned char[_capacity];
    std::copy(other._digits, other._digits + _size, _digits);
}

// Конструктор перемещения
Array::Array(Array&& other) noexcept : _digits(other._digits), _capacity(other._capacity), _size(other._size) {
    std::cout << "Array: Вызван конструктор перемещения\n";
    other._digits = nullptr;
    other._capacity = 0;
    other._size = 0;
}

// dеструктор
Array::~Array() noexcept {
    std::cout << "Array: Вызван деструктор\n";
    delete[] _digits;
}

// Оператор присваивания (копирование)
Array& Array::operator=(const Array& other) {
    std::cout << "Array: Вызван копирующий оператор присваивания\n";
    if (this == &other) return *this;

    delete[] _digits;

    _capacity = other._capacity;
    _size = other._size;
    _digits = new unsigned char[_capacity];
    std::copy(other._digits, other._digits + _size, _digits);

    return *this;
}

// Оператор присваивания (перемещение)
Array& Array::operator=(Array&& other) noexcept {
    std::cout << "Array: Вызван оператор присваивания (перемещение)\n";
    if (this == &other) return *this;

    delete[] _digits;

    _digits = other._digits;
    _capacity = other._capacity;
    _size = other._size;

    other._digits = nullptr;
    other._capacity = 0;
    other._size = 0;

    return *this;
}

// Метод получения размера
size_t Array::size() const {
    return _size;
}

// oператоры доступа к элементам
unsigned char& Array::operator[](size_t index) {
    if (index >= _size) throw std::out_of_range("Индекс вне диапазона");
    return _digits[index];
}

const unsigned char& Array::operator[](size_t index) const {
    if (index >= _size) throw std::out_of_range("Индекс вне диапазона");
    return _digits[index];
}

// aрифметические операции с присваиванием
Array& Array::operator+=(const Array& other) {
    if (_size != other._size) throw std::invalid_argument("Размеры массивов не совпадают");

    for (size_t i = 0; i < _size; ++i) {
        _digits[i] += other._digits[i];
    }

    return *this;
}

Array& Array::operator-=(const Array& other) {
    if (_size != other._size) throw std::invalid_argument("Размеры массивов не совпадают");

    for (size_t i = 0; i < _size; ++i) {
        _digits[i] -= other._digits[i];
    }

    return *this;
}

// Операторы сравнения
bool Array::operator==(const Array& other) const {
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size; ++i) {
        if (_digits[i] != other._digits[i]) return false;
    }
    return true;
}

bool Array::operator!=(const Array& other) const {
    return !(*this == other);
}

bool Array::operator<(const Array& other) const {
    size_t minSize = std::min(_size, other._size);
    for (size_t i = 0; i < minSize; ++i) {
        if (_digits[i] < other._digits[i]) return true;
        if (_digits[i] > other._digits[i]) return false;
    }
    return _size < other._size;
}

bool Array::operator>(const Array& other) const {
    return other < *this;
}


//Hex class methods
// Конструктор по умолчанию
Hex::Hex() : Array() {
    std::cout << "Hex: Вызван конструктор по умолчанию\n";
}

// Конструктор от строки
Hex::Hex(const std::string& hexStr) : Array(hexStr.size()) {
    std::cout << "Hex: Вызван конструктор от строки\n";
    for (size_t i = 0; i < hexStr.size(); ++i) {
        _digits[i] = charToHex(hexStr[i]);
    }
}

// Копирующий конструктор
Hex::Hex(const Hex& other) : Array(other) {
    std::cout << "Hex: Вызван копирующий конструктор\n";
}

// Конструктор перемещения
Hex::Hex(Hex&& other) noexcept : Array(std::move(other)) {
    std::cout << "Hex: Вызван конструктор перемещения\n";
}

// Деструктор
Hex::~Hex() noexcept {
    std::cout << "Hex: Вызван деструктор\n";
}

// Оператор присваивания
Hex& Hex::operator=(const Hex& other) {
    Array::operator=(other);
    return *this;
}

Hex& Hex::operator=(Hex&& other) noexcept {
    Array::operator=(std::move(other));
    return *this;
}

Hex& Hex::operator+=(const Hex& other) {
    // Преобразуем текущий объект в строку
    std::string hexStr1 = this->toString();
    std::string hexStr2 = other.toString();

    // Определяем максимальную длину для сложения
    size_t maxLength = std::max(hexStr1.size(), hexStr2.size());

    // Переворачиваем строки для удобного сложения младших разрядов
    std::string revHex1 = hexStr1;
    std::string revHex2 = hexStr2;
    std::reverse(revHex1.begin(), revHex1.end());
    std::reverse(revHex2.begin(), revHex2.end());

    // Дополняем строки нулями до одинаковой длины
    while (revHex1.size() < maxLength) revHex1 += '0';
    while (revHex2.size() < maxLength) revHex2 += '0';

    int carry = 0;  // Перенос разряда
    std::string result = "";

    // Основной цикл сложения
    for (size_t i = 0; i < maxLength; ++i) {
        unsigned char digit1 = charToHex(revHex1[i]);
        unsigned char digit2 = charToHex(revHex2[i]);
        int sum = digit1 + digit2 + carry;
        carry = sum / 16;  // Перенос разряда
        result += hexToChar(sum % 16);  // Остаток
    }

    // Добавляем перенос, если остался после сложения
    if (carry > 0) {
        result += hexToChar(carry);
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    // Переворачиваем результат обратно
    std::reverse(result.begin(), result.end());

    // Обновляем _digits текущего объекта на результат
    size_t newSize = result.size();
    if (newSize > _capacity) {
        throw std::overflow_error("Hex: Переполнение массива после сложения.");
    }
    _size = newSize;  // обновляем размер

    // Записываем результат в _digits
    for (size_t i = 0; i < newSize; ++i) {
        _digits[i] = charToHex(result[i]);
    }

    return *this;
}

Hex& Hex::operator-=(const Hex& other) {
    // Преобразуем текущий объект в строку
    std::string hexStr1 = this->toString();
    std::string hexStr2 = other.toString();

    // Определяем максимальную длину для вычитания
    size_t maxLength = std::max(hexStr1.size(), hexStr2.size());

    // Переворачиваем строки для удобного вычитания младших разрядов
    std::string revHex1 = hexStr1;
    std::string revHex2 = hexStr2;
    std::reverse(revHex1.begin(), revHex1.end());
    std::reverse(revHex2.begin(), revHex2.end());

    // Дополняем строки нулями до одинаковой длины
    while (revHex1.size() < maxLength) revHex1 += '0';
    while (revHex2.size() < maxLength) revHex2 += '0';

    bool borrow = false;  // Заём разряда
    std::string result = "";

    // Основной цикл вычитания
    for (size_t i = 0; i < maxLength; ++i) {
        unsigned char digit1 = charToHex(revHex1[i]);
        unsigned char digit2 = charToHex(revHex2[i]);

        if (borrow) {
            if (digit1 > 0) {
                digit1 -= 1;
                borrow = false;
            } else {
                digit1 = 15;  // Переводим в 15, так как это 0 с заёмом
                borrow = true;
            }
        }

        if (digit1 < digit2) {
            digit1 += 16;
            borrow = true;
        }

        result += hexToChar(digit1 - digit2);  // Добавляем результат текущего разряда
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    // Переворачиваем результат обратно
    std::reverse(result.begin(), result.end());

    // Обновляем _digits текущего объекта на результат
    size_t newSize = result.size();
    if (newSize > _capacity) {
        throw std::overflow_error("Hex: Переполнение массива после вычитания.");
    }
    _size = newSize;  // обновляем размер

    // Записываем результат в _digits
    for (size_t i = 0; i < newSize; ++i) {
        _digits[i] = charToHex(result[i]);
    }

    return *this;
}


// Операторы сравнения
bool Hex::operator==(const Hex& other) const {
    return this->toString() == other.toString();
}

bool Hex::operator!=(const Hex& other) const {
    return !(*this == other);
}

bool Hex::operator<(const Hex& other) const {
    return hexCompare(this->toString(), other.toString()) < 0;
}

bool Hex::operator>(const Hex& other) const {
    return hexCompare(this->toString(), other.toString()) > 0;
}

// Перевод в строку
std::string Hex::toString() const {
    std::ostringstream oss;
    for (size_t i = size(); i > 0; --i) {
        oss << hexToChar(_digits[i - 1]);
    }
    return oss.str();
}

// Приватный метод для перевода символа в шестнадцатеричное значение
unsigned char Hex::charToHex(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    throw std::invalid_argument("Неверный символ шестнадцатеричного числа");
}

// Приватный метод для перевода шестнадцатеричного значения в символ
char Hex::hexToChar(unsigned char hexVal) const {
    if (hexVal < 10) return '0' + hexVal;
    return 'A' + (hexVal - 10);
}

std::string hexOperation(const std::string& hex1, const std::string& hex2, char operation) {
    std::string result = "";

    // Определяем максимальную длину для операций
    size_t maxLength = std::max(hex1.size(), hex2.size());

    // Переворачиваем строки для удобного сложения/вычитания младших разрядов
    std::string revHex1 = hex1;
    std::string revHex2 = hex2;
    std::reverse(revHex1.begin(), revHex1.end());
    std::reverse(revHex2.begin(), revHex2.end());

    // Дополняем строки нулями до одинаковой длины
    while (revHex1.size() < maxLength) revHex1 += '0';
    while (revHex2.size() < maxLength) revHex2 += '0';

    int carry = 0;  // Перенос разряда (для сложения)
    bool borrow = false;  // Заём разряда (для вычитания)

    // Основной цикл сложения/вычитания
    for (size_t i = 0; i < maxLength; ++i) {
        int digit1 = charToHex(revHex1[i]);
        int digit2 = charToHex(revHex2[i]);
        int res = 0;

        if (operation == '+') {
            res = digit1 + digit2 + carry;
            carry = res / 16;  // переносим разряд
            res %= 16;  // остаток
        } else if (operation == '-') {
            if (borrow) {
                digit1 -= 1;
                borrow = false;
            }

            if (digit1 < digit2) {
                digit1 += 16;
                borrow = true;
            }
            res = digit1 - digit2;
        }

        result += hexToChar(res);  // добавляем результат текущего разряда
    }

    // Добавляем перенос, если остался после сложения
    if (operation == '+' && carry > 0) {
        result += hexToChar(carry);
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    // Переворачиваем результат обратно
    std::reverse(result.begin(), result.end());

    return result;
}

int Hex::hexCompare(const std::string& hex1, const std::string& hex2) const { // И здесь
    if (hex1.size() > hex2.size()) return 1;  // hex1 больше, если длина больше
    if (hex1.size() < hex2.size()) return -1; // hex1 меньше, если длина меньше

    // Если длины одинаковы, сравниваем по символам
    for (size_t i = 0; i < hex1.size(); ++i) {
        if (hex1[i] > hex2[i]) return 1;
        if (hex1[i] < hex2[i]) return -1;
    }

    return 0;  // Числа равны
}
