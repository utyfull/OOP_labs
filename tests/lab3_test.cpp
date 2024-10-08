#include "lab3.h"
#include <gtest/gtest.h>

TEST(FigureTest, PentagonAssignment) {
    Pentagon* pentagon1 = new Pentagon();
    Pentagon* pentagon2 = new Pentagon();
    pentagon1 = pentagon2; 
    ASSERT_TRUE(pentagon1 == pentagon2);
}


TEST(FigureTest, TrapezoidOutputStream) {
    Trapezoid* trapezoid = new Trapezoid();
    std::ostringstream os;
    os << *trapezoid;
    std::string expectedOutput = "Trapezoid: ((0, 0), (0, 0), (0, 0), (0, 0))";
    ASSERT_EQ(os.str(), expectedOutput);
}

TEST(FigureTest, RhombInputStream) {
    Rhomb* rhomb = new Rhomb();
    std::istringstream is("1 2 3 4 5 6 7 8"); 
    is >> *rhomb;
    double area = (* rhomb).getArea();
    ASSERT_NEAR(area, 16, 0.5); 
}


TEST(FigureTest, PentagonOperatorDouble) {
    Pentagon* pentagon = new Pentagon();
    std::istringstream is("1 2 3 4 5 6 7 8 9 10"); 
    is >> *pentagon;
    double value = static_cast<double>(*pentagon);
    ASSERT_NEAR(value, 5, 0.5); 
}