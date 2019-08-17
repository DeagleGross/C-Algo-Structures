    ////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::SafeArray class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "safearray.h"


TEST(StackArray, simplest)
{
    using namespace xi;

    SafeArray<int> sa;
    //SafeArray<void> st1;     // ошибка: тип void не может быть инстанцирован в объект!
}


TEST(StackArray, DefConstructor)
{
    using namespace xi;

    SafeArray<int> sa;
    EXPECT_EQ(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 0);
}


TEST(StackArray, InitConstructor1)
{
    using namespace xi;

    SafeArray<int> sa(3);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 3);
}


TEST(StackArray, IndexOper1)
{
    using namespace xi;

    SafeArray<int> sa(3);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 3);

    sa[0] = 0;
    sa[1] = 1;
    sa[2] = 2;

    // out of range:
    EXPECT_THROW(sa[3] = 3, std::out_of_range);
}


TEST(StackArray, IndexConstOper1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    sa[0] = 0;
    EXPECT_EQ(sa[0], 0);

    const int el0 = sa[0];
    EXPECT_EQ(el0, sa[0]);

    // out of range:
    EXPECT_THROW(sa[1], std::out_of_range); // да, это тоже выражение!
}

TEST(StackArray, CopyConstr1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    SafeArray<int> sb = sa;
    EXPECT_NE(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 1);

    // корректность конструктора копирования
    ASSERT_NE(sa.getRawPtr(), sb.getRawPtr());
}


TEST(StackArray, AssignOper1)
{
    using namespace xi;

    SafeArray<int> sa(1);
    EXPECT_NE(sa.getRawPtr(), nullptr);
    EXPECT_EQ(sa.getCapacity(), 1);

    SafeArray<int> sb;
    EXPECT_EQ(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 0);

    // копируем
    sb = sa;

    EXPECT_NE(sb.getRawPtr(), nullptr);
    EXPECT_EQ(sb.getCapacity(), 1);

    // корректность операции копирования
    ASSERT_NE(sa.getRawPtr(), sb.getRawPtr());
}

