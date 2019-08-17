////////////////////////////////////////////////////////////////////////////////
/// MY OWN TESTS FOR S01-POINT

/// STORED BELOW FOR EXAMPLE
/*
 * TEST(XiPointArray, initByArray)
{

    using namespace xi;

    Point testAr[] = { Point(1, 1), Point(2, 2), Point(3, 3) };
    PointArray::Uint testArSize = sizeof(testAr) / sizeof(testAr[0]);

    PointArray ar1(testAr, testArSize);
    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(testArSize, ar1.getSize());

    EXPECT_EQ(1, ar1.get(0)->getX());
    EXPECT_EQ(2, ar1.get(1)->getX());
}
 */
////////////////////////////////////////////////////////////////////////////////




#include <gtest/gtest.h>


#include "xipoint.h"

TEST(MyOwnTest_Point, initialization)
{
    using namespace xi;

    Point p = Point();
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(MyOwnTest_Point, properties_change)
{
    using namespace xi;

    Point p = Point(3,5);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 5);

    p.setX(10);
    p.setY(10);
    EXPECT_EQ(p.getX(), 10);
    EXPECT_EQ(p.getY(), 10);
}

TEST(MyOwnTest_Point, shift_1arg)
{
    using namespace xi;

    Point p = Point(3,4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);

    p.shift(5);
    EXPECT_EQ(p.getX(), 8);
    EXPECT_EQ(p.getY(), 9);
}

TEST(MyOwnTest_Point, shift_2arg)
{
    using namespace xi;

    Point p = Point(3,4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);

    p.shift(5, 3);
    EXPECT_EQ(p.getX(), 8);
    EXPECT_EQ(p.getY(), 7);
}

TEST(MyOwnTest_Point, shift_pt)
{
    using namespace xi;

    Point p = Point(3,4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);

    Point p2 = Point(1,1);
    p.shift(p2);
    EXPECT_EQ(p.getX(), 4);
    EXPECT_EQ(p.getY(), 5);
}

TEST(MyOwnTest_Point, pyfagor)
{
    using namespace xi;

    Point p1 = Point(0,4);
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 4);

    Point p2 = Point(3,0);
    EXPECT_EQ(p2.getX(), 3);
    EXPECT_EQ(p2.getY(), 0);

    EXPECT_EQ(p1.dist(p2), 5);

    p1.setX(0); p1.setY(0);
    p2.setX(0); p2.setY(0);
    EXPECT_EQ(p1.dist(p2), 0);

    p1.setX(-3); p1.setY(0);
    p2.setX(0); p2.setY(4);
    EXPECT_EQ(p1.dist(p2), 5);
}

/////////// TESTING POINT_ARRAY
/////////// TESTING POINT_ARRAY
/////////// TESTING POINT_ARRAY
/////////// TESTING POINT_ARRAY
/////////// TESTING POINT_ARRAY

TEST(MyOwnTest_PointArray, append)
{
    using namespace xi;

    PointArray ar1;
    ar1.append(Point(1,1));
    EXPECT_EQ(ar1.getSize(), 1);
}