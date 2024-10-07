#include <gtest/gtest.h>
#include "lab2.h"

TEST(HexTest, Addition) {
    Hex hex1("A3F5");
    Hex hex2("1B4");

    hex1 += hex2;  

    std::string result = hex1.toString();
    ASSERT_TRUE(result == "BE36");  
}

TEST(HexTest, Subtraction) {
    Hex hex1("A3F5");
    Hex hex2("A3F5");

    hex1 -= hex2; 

    std::string result = hex1.toString();
    ASSERT_TRUE(result == "0");  
}

TEST(HexTest, ComparisonEqual) {
    Hex hex1("A3F5");
    Hex hex2("A3F5");

    ASSERT_TRUE(hex1 == hex2);  
}

TEST(HexTest, ComparisonNotEqual) {
    Hex hex1("A3F5");
    Hex hex2("1B4");

    ASSERT_TRUE(hex1 != hex2);  
}

TEST(HexTest, ComparisonLess) {
    Hex hex1("1B4");
    Hex hex2("A3F5");

    ASSERT_TRUE(hex1 < hex2);  
}

TEST(HexTest, ComparisonGreater) {
    Hex hex1("A3F5");
    Hex hex2("1B4");

    ASSERT_TRUE(hex1 > hex2);  
}

TEST(HexTest, AddingWithZero) {
    Hex hex1("A3F5");
    Hex hexZero("0");

    hex1 += hexZero;  

    std::string result = hex1.toString();
    ASSERT_TRUE(result == "A3F5"); 
}

TEST(HexTest, SubtractingFromZero) {
    Hex hexZero("0");
    Hex hexLarge("FFFFFFF");

    hexZero -= hexLarge; 

    std::string result = hexZero.toString();
    ASSERT_TRUE(result == "1");  
}