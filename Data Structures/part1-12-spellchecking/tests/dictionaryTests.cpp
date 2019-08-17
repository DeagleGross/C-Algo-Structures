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
#include <iostream>
#include <fstream>
#include <string>

namespace MainDict {
    #include "main.cpp"
}

using namespace std;

void testWord(const string& word, const vector<string>& dictionary, const vector<string> expect)
{
    ofstream dictFile("dict");
    
    for (string w : dictionary)
        dictFile << w << endl;

    dictFile.close();
    
    Dictionary dict("dict");
    
    ofstream wordFile(word);
    wordFile << "   " << word << ".";
    wordFile.close();
    
    streambuf* oldCoutStreamBuf = cout.rdbuf();
    ostringstream spellIn;
    cout.rdbuf(spellIn .rdbuf());
    
    ifstream input(word);
    
    MainDict::checkSpelling(input, dict);
    
    input.close();

    // Restore old cout.
    cout.rdbuf( oldCoutStreamBuf );
    
    stringstream spellOut;
    
    spellOut << spellIn.str();
    
    string t;
    getline(spellOut, t);
    getline(spellOut, t);

    int count = 0;
    
    for (spellOut >> t; !spellOut.eof() && !spellOut.fail(); spellOut >> t)
    {
        count += 1;
        
        bool contains = false;
        
        for (string w : expect)
            if (w == t)
            {
                contains = true;
                break;
            }
        
        ASSERT_TRUE(contains);
    }
    
    ASSERT_EQ(count, expect.size());
};

TEST(DictionaryTest, simpleInsert)
{
    testWord("helo", {"henlo"}, {"henlo"});
}

TEST(DictionaryTest, simpleReplace)
{
    testWord("hello", {"henlo"}, {"henlo"});
}

TEST(DictionaryTest, simpleTranspose)
{
    testWord("helno", {"henlo"}, {"henlo"});
}

TEST(DictionaryTest, simpleRemove)
{
    testWord("henllo", {"henlo"}, {"henlo"});
}
