#define LAB5_H
#ifndef LAB5_H

#include <memory_resource>
#include <list>
#include <cstddef>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <string>

// Мне лень разделять на несколько файлов, искренне прошу прощения

/* 
    description: ListMemoryResource
    ListMemoryResource служит для управления выделением и освобождением памяти. Он должен:

    1. Выделять память, которую можно многократно использовать.
    2. Освобождать память, но при этом помнить об освобождённых блоках, чтобы не терять их из-под управления.
    3. Очищать неосвобождённую память при уничтожении объекта, чтобы избежать утечек памяти.
*/

class ListMemoryResource : public std::pmr::memory_resource {
private:
    std::list<void*> allocated_blocks;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* ptr = ::operator new(bytes);  
        allocated_blocks.push_back(ptr);
        std::cout << "Allocated " << bytes << " bytes\n";
        return ptr;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        allocated_blocks.remove(p);  
        ::operator delete(p);       
        std::cout << "Deallocated " << bytes << " bytes\n";
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;  
    }

public:
    ~ListMemoryResource() {
        for (void* ptr : allocated_blocks) {
            ::operator delete(ptr);
            std::cout << "Cleaned up memory\n";
        }
    }
};


/* 
    description: Dynamic array

    Класс DynamicArray реализует функциональность контейнера,
    который может динамически увеличивать свою ёмкость при добавлении новых элементов.
    Он также использует итераторы для обхода элементов,
    а аллокатор std::pmr::polymorphic_allocator управляет памятью.
*/

template <typename T>
class DynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

private:
    allocator_type allocator;
    T* data;
    std::size_t capacity;
    std::size_t size;

    void expand_capacity() {
        std::size_t new_capacity = capacity ? capacity * 2 : 1;
        T* new_data = allocator.allocate(new_capacity);
        std::uninitialized_copy_n(data, size, new_data);
        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

public:
    explicit DynamicArray(allocator_type alloc = {}) 
        : allocator(alloc), data(nullptr), capacity(0), size(0) {}

    void push_back(const T& value) {
        if (size == capacity) {
            expand_capacity();
        }
        allocator.construct(data + size, value);
        ++size;
    }

    void pop_back() {
        if (size > 0) {
            allocator.destroy(data + size - 1);
            --size;
        }
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    std::size_t get_size() const { return size; }

    ~DynamicArray() {
        for (std::size_t i = 0; i < size; ++i) {
            allocator.destroy(data + i);
        }
        allocator.deallocate(data, capacity);
    }

    /*
        description: forward_iterator
        Этот итератор реализует следующие методы:

        1. Доступ к элементу (operator*): Возвращает ссылку на элемент, на который указывает итератор.
        2. Доступ к указателю (operator->): Предоставляет доступ к членам объекта.
        3. Префиксный и постфиксный инкремент (operator++, operator++(int)): Перемещают итератор к следующему элементу.
        4. Операторы сравнения (operator== и operator!=): Проверяют, равны ли два итератора.
    */

    class Iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr == b.ptr;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr != b.ptr;
        }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
};




#endif