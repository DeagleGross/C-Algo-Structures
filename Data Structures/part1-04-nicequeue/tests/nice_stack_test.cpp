////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit test for NiceStack class
/// \author    Alexander Toptunov
/// \version   0.1
/// \date      30.09.2018
///            This is a part of the course "Algorithms and Data Structures"
///            provided by the School of Software Engineering of the Faculty
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
#include "NiceStack.h"


TEST(NiceStack, simplest)
{
    NiceStack<int> niceStack(10);
}

TEST(NiceStack, create)
{
    NiceStack<int> niceStack(10);
    ASSERT_EQ(niceStack.capacity(), 10);
}

TEST(NiceStack, pushAndTop)
{
    NiceStack<int> niceStack(10);
    niceStack.push(2);
    ASSERT_EQ(niceStack.top(), 2);
    niceStack.push(3);
    niceStack.push(5);
    ASSERT_EQ(niceStack.top(), 5);
    ASSERT_EQ(niceStack.top(), 5);
}


TEST(NiceStack, pop)
{
    NiceStack<int> niceStack(10);
    niceStack.push(2);
    EXPECT_EQ(niceStack.pop(), 2);
    niceStack.push(3);
    niceStack.push(4);
    EXPECT_EQ(niceStack.top(), 4);
    EXPECT_EQ(niceStack.pop(), 4);
    EXPECT_EQ(niceStack.top(), 3);
    EXPECT_EQ(niceStack.pop(), 3);
}

TEST(NiceStack, getMin)
{
    NiceStack<int> niceStack(20);

    niceStack.push(10);
    ASSERT_EQ(niceStack.getMinimum(), 10);

    niceStack.push(5);
    ASSERT_EQ(niceStack.getMinimum(), 5);

}

TEST(NiceStack, sizeTest)
{
    NiceStack<int> niceStack(20);
    ASSERT_EQ(niceStack.size(), 0);

    niceStack.push(1);
    niceStack.push(2);
    ASSERT_EQ(niceStack.size(), 2);
    ASSERT_EQ(niceStack.capacity(), 20);

}

