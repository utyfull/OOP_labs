#include "lab3.h"
#include <gtest/gtest.h>

TEST(FigureTest, ArrayTotalArea) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;

    auto trapezoid = std::make_shared<Trapezoid<double>>();
    auto rhomb = std::make_shared<Rhomb<double>>();
    auto pentagon = std::make_shared<Pentagon<double>>();
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

    ASSERT_NEAR(totalArea, 19, 0.5);
}


TEST(FigureTest, ArrayTotalAreaWithDeleteElement) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;

    auto trapezoid = std::make_shared<Trapezoid<double>>();
    auto rhomb = std::make_shared<Rhomb<double>>();
    auto pentagon = std::make_shared<Pentagon<double>>();
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

    ASSERT_NEAR(totalArea, 11, 0.5);
}


TEST(FigureTest, PentagonAssignment) {
    auto pentagon1 = std::make_shared<Pentagon<double>>();
    auto pentagon2 = std::make_shared<Pentagon<double>>();
    pentagon1 = pentagon2; 
    ASSERT_TRUE(pentagon1 == pentagon2);
}

