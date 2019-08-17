////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::RBTree interfaces
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
/// Тестирование публичных методов, то есть "правильное" тестирование.
///
////////////////////////////////////////////////////////////////////////////////


#include <gtest/gtest.h>

#include "rbtree.h"
#include "def_dumper.h"



using namespace xi;

// Тестируем на целых числах.
typedef RBTree<int> RBTreeInt;


static const char* DUMP_EVENTLOG_FILE = "../../out/log.txt";
static const char* DUMP_IMAGES_DIR = "../../out/gv/";



/** \brief Тестовый класс для тестирования открытых интерфейсов классов КЧД в виде черного ящика. */
class RBTreePubTest : public ::testing::Test {
public:
    RBTreePubTest()
        : _dumper(DUMP_EVENTLOG_FILE, DUMP_IMAGES_DIR)
    {
    }

public:
    static const int STRUCT2_SEQ[];
    static const int STRUCT2_SEQ_NUM;


protected:
    RBTreeDefDumper<int, std::less<int>> _dumper;

    /** \brief Выводить в формате GraphViz. */
    RBTreeGvDumper<int, std::less<int>> _gvDumper;
}; // class RBTreePubTest


// Вынесенная инициализация массива
const int RBTreePubTest::STRUCT2_SEQ[] =
{ 4, 50, 10, 40, 17, 35, 20, 27, 37, 45, 60, 21, 1, 30 };
const int RBTreePubTest::STRUCT2_SEQ_NUM = sizeof(STRUCT2_SEQ) / sizeof(STRUCT2_SEQ[0]);


TEST_F(RBTreePubTest, Simplest)
{
    //RBTree<int> tree;
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());
}

TEST_F(RBTreePubTest, checkMyInsertNewNode)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(3);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);

    tree.insert(2);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 2);

    tree.insert(5);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 5);

    tree.insert(1);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 2);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getKey(), 1);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("insertNewNode.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, checkCase3LEFT)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(9);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 9);

    tree.insert(10);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 9);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 10);

    tree.insert(8);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 9);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 8);

    tree.insert(7);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 9);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 10);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 8);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getKey(), 7);

    tree.insert(6);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 9);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 10);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 7);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getKey(), 6);
    EXPECT_EQ(tree.getRoot()->getLeft()->getRight()->getKey(), 8);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("Case3checkLeft.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, checkCase2LEFT)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(15);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 15);

    tree.insert(16);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 15);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 16);

    tree.insert(11);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 15);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 11);

    tree.insert(3);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 15);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 16);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 11);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getKey(), 3);

    tree.insert(5);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 15);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 16);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 5);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getRight()->getKey(), 11);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("Case2checkLeft.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, checkCase3RIGHT)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(3);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);

    tree.insert(1);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);

    tree.insert(5);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 5);

    tree.insert(8);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 5);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight()->getKey(), 8);

    tree.insert(10);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 8);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight()->getKey(), 10);
    EXPECT_EQ(tree.getRoot()->getRight()->getLeft()->getKey(), 5);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("Case3checkRight.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, checkCase2RIGHT)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(3);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);

    tree.insert(1);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);

    tree.insert(5);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 5);

    tree.insert(8);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 5);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight()->getKey(), 8);

    tree.insert(7);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 7);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight()->getKey(), 8);
    EXPECT_EQ(tree.getRoot()->getRight()->getLeft()->getKey(), 5);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("Case2checkRight.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, RIGHTcheckSimple3ElementsInsert)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(10);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 10);

    tree.insert(30);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 10);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 30);

    tree.insert(20);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 20);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 30);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 10);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("ThreeSimpleElements.gv");
    _gvDumper.dump(fn1, tree);
}

TEST_F(RBTreePubTest, LEFTcheckSimple3ElementsInsert)
{
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());

    tree.insert(10);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 10);

    tree.insert(5);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 10);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 5);

    tree.insert(7);
    EXPECT_TRUE(!tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getKey(), 7);
    EXPECT_EQ(tree.getRoot()->getLeft()->getKey(), 5);
    EXPECT_EQ(tree.getRoot()->getRight()->getKey(), 10);

    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("ThreeSimpleElementsFROM_RIGHT.gv");
    _gvDumper.dump(fn1, tree);
}

// внешняя вставка элемента — добавление нода
TEST_F(RBTreePubTest, insert1)
{
    RBTreeInt tree;
    tree.setDumper(&_dumper);

    for (int i = 0; i < STRUCT2_SEQ_NUM; ++i)
    {
        tree.insert(STRUCT2_SEQ[i]);

        char fnBuf[255];
        sprintf(fnBuf, "%s\\Insert1_step_%03d.gv", DUMP_IMAGES_DIR, i);
        _gvDumper.dump(fnBuf, tree);
    }


    //std::string fn1(DUMP_IMGS_PUB_PATH);
    //fn1.append("Insert1.gv");
    //_gvDumper.dump(fn1, tree);
}

// поиск элемента
TEST_F(RBTreePubTest, find1)
{
    RBTreeInt tree;

    for (int i = 0; i < STRUCT2_SEQ_NUM; ++i)
        tree.insert(STRUCT2_SEQ[i]);

    const RBTreeInt::Node* n4 = tree.find(4);           // черный
    EXPECT_EQ(4, n4->getKey());

    const RBTreeInt::Node* n20 = tree.find(20);         // корень
    EXPECT_EQ(20, n20->getKey());

    const RBTreeInt::Node* n35 = tree.find(35);         // красный
    EXPECT_EQ(35, n35->getKey());

    const RBTreeInt::Node* n30 = tree.find(30);         // лист
    EXPECT_EQ(30, n30->getKey());

    const RBTreeInt::Node* n100 = tree.find(100);       // отсутствующий элемент
    EXPECT_EQ(nullptr, n100);
}

// поиск элемента
TEST_F(RBTreePubTest, find2)
{
    // пустое дерево
    RBTreeInt tree;

    const RBTreeInt::Node* n4 = tree.find(4);  
    EXPECT_EQ(nullptr, n4);

    const RBTreeInt::Node* n100 = tree.find(100);
    EXPECT_EQ(nullptr, n100);
}


#ifdef RBTREE_WITH_DELETION

class RemoveTest : public RBTreePubTest {};

// удаление нод
TEST_F(RemoveTest, delete1)
{
    RBTreeInt tree;
    
    for (int i = 0; i < STRUCT2_SEQ_NUM; ++i)
        tree.insert(STRUCT2_SEQ[i]);


    std::string fn1(DUMP_IMAGES_DIR);
    fn1.append("/delete1.gv");
   _gvDumper.dump(fn1, tree);

   // далее с пошаговой отладкой
   tree.setDumper(&_dumper);

   // удаляем в той же последовательности (а можно и в обратной попробовать)
   for (int i = 0; i < STRUCT2_SEQ_NUM; ++i)
       tree.remove(STRUCT2_SEQ[i]);

}
#endif // RBTREE_WITH_DELETION
