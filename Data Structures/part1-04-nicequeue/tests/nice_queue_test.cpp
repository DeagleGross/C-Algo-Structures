////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit test for NiceQueue class
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
#include "NiceQueue.h"


TEST(NiceQueue, simplest)
{
    NiceQueue<int> niceQueue(10);
}

TEST(NiceQueue, create)
{
    NiceQueue<int> niceQueue(20);
    ASSERT_EQ(niceQueue.capacity(), 20);
}

TEST(NiceQueue, enqAndDeq)
{
    NiceQueue<int> niceQueue(10);
    niceQueue.enq(10);
    ASSERT_EQ(niceQueue.deq(), 10);
    niceQueue.enq(3);
    niceQueue.enq(5);
    niceQueue.enq(7);
    ASSERT_EQ(niceQueue.deq(), 3);
    ASSERT_EQ(niceQueue.deq(), 5);

}

TEST(NiceQueue, myTest1)
{
    NiceQueue<int> niceQueue(10);
    niceQueue.enq(7);
    ASSERT_EQ(niceQueue.getMinimum(), 7);
    niceQueue.enq(15);
    ASSERT_EQ(niceQueue.getMinimum(), 7);
    niceQueue.enq(13);
    ASSERT_EQ(niceQueue.getMinimum(), 7);
    ASSERT_EQ(niceQueue.deq(), 7);
    ASSERT_EQ(niceQueue.getMinimum(), 13);
    ASSERT_EQ(niceQueue.deq(), 15);
    ASSERT_EQ(niceQueue.getMinimum(), 13);
//    ASSERT_EQ(niceQueue.deq(), 13);
//    ASSERT_THROW(niceQueue.deq(), std::out_of_range);
    niceQueue.enq(5);
    ASSERT_EQ(niceQueue.getMinimum(), 5);
    ASSERT_EQ(niceQueue.deq(), 13);
    ASSERT_EQ(niceQueue.getMinimum(), 5);
}


TEST(NiceQueue, getMin)
{
    NiceQueue<int> niceQueue(20);

    niceQueue.enq(10);
    ASSERT_EQ(niceQueue.getMinimum(), 10);

    niceQueue.enq(5);
    ASSERT_EQ(niceQueue.getMinimum(), 5);

}

TEST(NiceQueue, sizeAndCapacityTest)
{
    NiceQueue<int> niceQueue(20);
    ASSERT_EQ(niceQueue.size(), 0);

    niceQueue.enq(1);
    niceQueue.enq(2);
    ASSERT_EQ(niceQueue.size(), 2);
    ASSERT_EQ(niceQueue.capacity(), 20);

}

