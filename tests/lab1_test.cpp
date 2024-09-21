#include <gtest/gtest.h>
#include "lab1.h"

TEST(GcdTest, PositiveNumbers)
{
    int n{48};
    int m{18};

    int result = CalculateGcd(n, m);

    ASSERT_TRUE(result == 9);
    
}

TEST(GcdTest, SameNumbers)
{
    int n{25};
    int m{25};

    int result = CalculateGcd(n, m);

    ASSERT_TRUE(result == 25);
}

TEST(GcdTest, ZeroInput)
{
    int n{0};
    int m{0};

    int result = CalculateGcd(n, m);

    ASSERT_TRUE(result == 0);
}

TEST(GcdTest, OneInput)
{
    int n{1};
    int m{5};

    int result = CalculateGcd(n, m);

    ASSERT_TRUE(result == 1);
}

TEST(GcdTest, LargeNumbers)
{
    int n{123456789};
    int m{987654321};

    int result = CalculateGcd(n, m);

    ASSERT_TRUE(result == 9);
}
