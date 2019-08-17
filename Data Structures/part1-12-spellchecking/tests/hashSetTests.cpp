// - author: Kostyuchenko Ilya
// - date: 13.12.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
//
// # Gtest-based unit test.
// The naming conventions imply the name of a unit-test module is the same as
// the name of the corresponding tested module with _test suffix

#include <gtest/gtest.h>

#include "dictionary.h"

#include <vector>
#include <functional>

using namespace std;

template <typename T, typename S>
void insertElements(S& set, vector<T> elements)
{
    for (T e : elements)
        set.insert(e);
}

template <typename T, typename S>
void removeElements(S& set, vector<T> elements)
{
    for (T e : elements)
        set.remove(e);
}

template <typename T, typename S>
void containsElements(S& set, vector<T> elements)
{
    for (T e : elements)
        ASSERT_TRUE(set.search(e));
}

using DefaultSet = HashSet<string, hash_function, equality>;

TEST(HashSetTest, simple)
{
    DefaultSet set;
    
    ASSERT_FALSE(set.search("a"));
    ASSERT_FALSE(set.search("b"));
    ASSERT_FALSE(set.search("c"));
    
    insertElements<string, DefaultSet>(set, {"a", "b", "c"});
    containsElements<string, DefaultSet>(set, {"a", "b", "c"});
    removeElements<string, DefaultSet>(set, {"a", "b", "c"});
    
    ASSERT_FALSE(set.search("a"));
    ASSERT_FALSE(set.search("b"));
    ASSERT_FALSE(set.search("c"));
}
