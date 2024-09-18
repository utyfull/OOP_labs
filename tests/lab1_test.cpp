#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(AddTest, HadlesPositiveNumbers)
{
    EXPECT_EQ(add(3, 4), 7);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}