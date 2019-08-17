////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit test for xi::PointArray class
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

TEST(XiPointArray, simplest)
{
    using namespace xi;

    PointArray ar1;    
}


TEST(XiPointArray, properInit)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());
}



TEST(XiPointArray, initByArray)
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




TEST(XiPointArray, clear1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    Point p1(10, 15);
    ar1.append(p1);

    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(1, ar1.getSize());
    
    ar1.clear();

}


TEST(XiPointArray, remove1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());
    
    ar1.append(Point(0, 0));
    ar1.append(Point(1, 1));
    ar1.append(Point(2, 2));
    ar1.append(Point(3, 3));
    ar1.append(Point(4, 4));
    

    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(5, ar1.getSize());

    // trying to remove a non existing element
    ar1.remove(5);
    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(5, ar1.getSize());

}

TEST(XiPointArray, get1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    EXPECT_EQ(nullptr, ar1.get(0));
    EXPECT_EQ(nullptr, ar1.get(1));
}


TEST(XiPointArray, insert1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(nullptr, ar1.getRawPtr());
    EXPECT_EQ(0, ar1.getSize());

    Point p1(10, 15);
    ar1.insert(p1, 0);

    EXPECT_NE(nullptr, ar1.getRawPtr());
    EXPECT_EQ(1, ar1.getSize());
}



TEST(XiPointArray, computePath)
{
    using namespace xi;

    PointArray ar1;
    ar1.append(Point(0, 0));
    ar1.append(Point(0, 2));
    ar1.append(Point(1, 2));
    ar1.append(Point(1, 1));
    
    EXPECT_EQ(4, ar1.computePath());
}

