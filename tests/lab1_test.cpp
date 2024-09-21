#include <gtest/gtest.h>
#include "lab1.h"

TEST(GcdTest, PositiveNumbers)
{
    EXPECT_EQ(CalculateGcd(48, 18), 6);
    EXPECT_EQ(CalculateGcd(101, 10), 1);
    EXPECT_EQ(CalculateGcd(56, 98), 14);
    EXPECT_EQ(CalculateGcd(123, 456), 3);
}

TEST(GcdTest, SameNumbers)
{
    EXPECT_EQ(CalculateGcd(25, 25), 25);
    EXPECT_EQ(CalculateGcd(1000, 1000), 1000);
}

TEST(GcdTest, ZeroInput)
{
    EXPECT_EQ(CalculateGcd(0, 5), 5);
    EXPECT_EQ(CalculateGcd(5, 0), 5);
    EXPECT_EQ(CalculateGcd(0, 0), 0);
}

TEST(GcdTest, OneInput)
{
    EXPECT_EQ(CalculateGcd(1, 5), 1);
    EXPECT_EQ(CalculateGcd(5, 1), 1);
    EXPECT_EQ(CalculateGcd(1, 1), 1);
}

TEST(GcdTest, LargeNumbers)
{
    EXPECT_EQ(CalculateGcd(123456789, 987654321), 9);
    EXPECT_EQ(CalculateGcd(1000000000, 500000000), 500000000);
}

TEST(GcdTest, OneNumberGreater)
{
    EXPECT_EQ(CalculateGcd(7, 14), 7);
    EXPECT_EQ(CalculateGcd(100, 25), 25);
    EXPECT_EQ(CalculateGcd(500, 1000), 500);
    EXPECT_EQ(CalculateGcd(2000, 500), 500);
}