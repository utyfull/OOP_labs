#define LAB5_H
#ifndef LAB5_H

#include <memory_resource>
#include <list>
#include <cstddef>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>

// Мне лень разделять на несколько файлов, искренне прошу прощения

/* 
    description: Общая идея
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





#endif LAB5_H