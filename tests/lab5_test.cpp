#include <gtest/gtest.h>
#include "lab5.h"

// Тесты для ListMemoryResource
TEST(ListMemoryResourceTest, AllocateAndDeallocate) {
    ListMemoryResource memory_resource;
 
    void* ptr1 = memory_resource.allocate(100);
    ASSERT_NE(ptr1, nullptr);

    memory_resource.deallocate(ptr1, 100);
}

TEST(ListMemoryResourceTest, ReuseDeallocatedMemory) {
    ListMemoryResource memory_resource;

    void* ptr1 = memory_resource.allocate(50);
    memory_resource.deallocate(ptr1, 50);

    void* ptr2 = memory_resource.allocate(50);
    ASSERT_NE(ptr2, nullptr);
    memory_resource.deallocate(ptr2, 50);
}

// Тесты для DynamicArray
TEST(DynamicArrayTest, PushBackAndAccess) {
    ListMemoryResource memory_resource;
    DynamicArray<int> arr{&memory_resource};

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    ASSERT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArrayTest, CapacityExpansion) {
    ListMemoryResource memory_resource;
    DynamicArray<int> arr{&memory_resource};

    for (int i = 0; i < 100; ++i) {
        arr.push_back(i);
    }

    ASSERT_EQ(arr.get_size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(DynamicArrayTest, PopBack) {
    ListMemoryResource memory_resource;
    DynamicArray<int> arr{&memory_resource};

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    arr.pop_back();
    ASSERT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);

    arr.pop_back();
    arr.pop_back();
    ASSERT_EQ(arr.get_size(), 0);
}

TEST(DynamicArrayTest, IteratorFunctionality) {
    ListMemoryResource memory_resource;
    DynamicArray<int> arr{&memory_resource};

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    int expected_values[] = {10, 20, 30};
    int i = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        EXPECT_EQ(*it, expected_values[i++]);
    }
}

TEST(DynamicArrayTest, WorksWithComplexTypes) {
    struct ComplexType {
        int a;
        std::string b;
    };

    ListMemoryResource memory_resource;
    DynamicArray<ComplexType> arr{&memory_resource};

    arr.push_back(ComplexType{1, "test1"});
    arr.push_back(ComplexType{2, "test2"});

    ASSERT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0].a, 1);
    EXPECT_EQ(arr[0].b, "test1");
    EXPECT_EQ(arr[1].a, 2);
    EXPECT_EQ(arr[1].b, "test2");
}