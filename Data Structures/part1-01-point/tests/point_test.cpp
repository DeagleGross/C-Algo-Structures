////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::Point class
/// \author    Sergey Shershakov
/// \version   0.2.1
/// \date      08.09.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
/// Note the issue about including point modules here (ask the trainer about).
/// 
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>


#include "xipoint.h"

TEST(XiPoint, simplest)
{
    using namespace xi;

    Point p1;
    Point p2(1, 1);
}


TEST(XiPoint, constructorDef)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

}

TEST(XiPoint, set1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    p1.setX(42);
    p1.setY(13);
    EXPECT_EQ(42, p1.getX());
    EXPECT_EQ(13, p1.getY());

}


TEST(XiPoint, shift1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    p1.shift(15);
    EXPECT_EQ(15, p1.getX());
    EXPECT_EQ(15, p1.getY());
}



TEST(XiPoint, shift4)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(0, p1.getX());
    EXPECT_EQ(0, p1.getY());

    Point p2(5, 10);
    EXPECT_EQ(5, p2.getX());
    EXPECT_EQ(10, p2.getY());

}

TEST(XiPoint, dist)
{
    using namespace xi;
    
    Point p1(0, 0);
    Point p2(0, 3);
    Point p3(4, 0);
    
    EXPECT_EQ(0, p1.dist(p1));
    
    EXPECT_EQ(3, p1.dist(p2));
    EXPECT_EQ(4, p1.dist(p3));
    EXPECT_EQ(5, p2.dist(p3));
}

