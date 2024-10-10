#include "lab3.h"
#include <gtest/gtest.h>

TEST(FigureTest, ArrayTotalArea) {
    Array array(10);  
    Trapezoid* trapezoid = new Trapezoid();
    Rhomb* rhomb = new Rhomb();
    Pentagon* pentagon = new Pentagon();
    std::istringstream is1("1 2 3 4 5 6 7 8");
    std::istringstream is2("1 2 3 4 5 6 7 8");
    std::istringstream is3("1 2 3 4 5 6 7 8 9 10");
    is1 >> *rhomb;
    is2 >> *trapezoid;
    is3 >> *pentagon;
    array.addFigure(trapezoid);
    array.addFigure(rhomb);
    array.addFigure(pentagon);

    double totalArea = array.totalArea();

    ASSERT_NEAR(totalArea, 25, 0.5);
}


TEST(FigureTest, ArrayTotalAreaWithDeleteElement) {
    Array array(10);  
    Trapezoid* trapezoid = new Trapezoid();
    Rhomb* rhomb = new Rhomb();
    Pentagon* pentagon = new Pentagon();
    std::istringstream is1("1 2 3 4 5 6 7 8");
    std::istringstream is2("1 2 3 4 5 6 7 8");
    std::istringstream is3("1 2 3 4 5 6 7 8 9 10");
    is1 >> *rhomb;
    is2 >> *trapezoid;
    is3 >> *pentagon;
    array.addFigure(trapezoid);
    array.addFigure(rhomb);
    array.addFigure(pentagon);
    array.removeFigure(1);
    
    double totalArea = array.totalArea();

    ASSERT_NEAR(totalArea, 9, 0.5);
}


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