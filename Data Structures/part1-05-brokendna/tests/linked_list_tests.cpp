#include <array>
#include "gtest/gtest.h"
#include "linked_list.h"

using xi::LinkedList;
using xi::Node;

#include "gtest/gtest.h"
#include "linked_list.h"

using xi::LinkedList;
using xi::Node;



TEST(linked_list_tests, TestGetOperator) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);

    ASSERT_THROW(list[-25], std::out_of_range);
    ASSERT_THROW(list[-1], std::out_of_range);
    ASSERT_EQ(list[0], 2);
    ASSERT_EQ(list[1], 3);
    ASSERT_EQ(list[2], 4);
    ASSERT_THROW(list[3], std::out_of_range);
    ASSERT_THROW(list[25], std::out_of_range);


    list.addElementToEnd(a = 5);
    ASSERT_EQ(list[3], 5);
    ASSERT_THROW(list[4], std::out_of_range);
}

// will be enabled only if you decided to explicitly implement copy constructor and assign operator
// !!!do not define TEST_COPY_CONSTR_ASSIGN_OP in this file!!! it will be overwritten on the server
#ifdef TEST_COPY_CONSTR_ASSIGN_OP
TEST(linked_list_cc_ao, CopyConstructor) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);

    LinkedList<int> copy(list);

    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47;

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(copy.size(), 4);

    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);

    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(77, copy[3]);
}


TEST(linked_list_cc_ao, AssignOperator) {
    LinkedList<int> list;
    int a;
    list.addElementToEnd(a = 2);
    list.addElementToEnd(a = 3);
    list.addElementToEnd(a = 4);

    LinkedList<int> copy;
    ASSERT_EQ(copy.size(), 0);

    copy = list = copy = list;

    copy[0] = 24;
    copy.addElementToEnd(a = 77);
    list[2] = 47;

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(copy.size(), 4);

    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);

    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
    ASSERT_EQ(77, copy[3]);
}

#endif // TEST_COPY_CONSTR_ASSIGN_OP

TEST(linked_list_tests, CreatedEmptyList_HasSizeZero1) {
    LinkedList<int> list;
    ASSERT_EQ(0, list.size());
}



TEST(linked_list_tests, AddingOneElementToEmptyList_HasSizeOne1) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(1, list.size());
}

TEST(linked_list_tests, AddingTwoElementsToEmptyList_HasSizeTwo1) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    int inserted_element_2 = 56;
    list.addElementToEnd(inserted_element_2);

    ASSERT_EQ(2, list.size());
}

TEST(linked_list_tests, AddingOneElementToEmptyList_ReturnFirstElement_ReturnsInsertedElement1) {
    LinkedList<int> list;
    int inserted_element = 234;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(inserted_element, list.getPreHead()->next->value);
}

TEST(linked_list_tests, CreatedEmptyList_HasSizeZero) {
    LinkedList<int> list;
    ASSERT_EQ(0, list.size());
}

TEST(linked_list_tests, AddingOneElementToEmptyList_HasSizeOne) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(1, list.size());
    ASSERT_EQ(list.getNodeByIndex(0)->value, inserted_element);
    ASSERT_EQ(list.getNodeByIndex(0)->next, nullptr);
}

TEST(linked_list_tests, AddingTwoElementsToEmptyList_HasSizeTwo) {
    LinkedList<int> list;
    int inserted_element = 2;
    list.addElementToEnd(inserted_element);

    int inserted_element_2 = 56;
    list.addElementToEnd(inserted_element_2);

    ASSERT_EQ(2, list.size());

    ASSERT_EQ(list.getNodeByIndex(0)->value, inserted_element);
    ASSERT_EQ(list.getNodeByIndex(1)->value, inserted_element_2);

}

TEST(linked_list_tests, AddingOneElementToEmptyList_ReturnFirstElement_ReturnsInsertedElement) {
    LinkedList<int> list;
    int inserted_element = 234;
    list.addElementToEnd(inserted_element);

    ASSERT_EQ(inserted_element, list.getPreHead()->next->value);
}

TEST(linked_list_tests, DeleteNodes) {
    LinkedList<int> list;
    int elements[4] = { 0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
        list.addElementToEnd(elements[i]);

    list.deleteNodes(list.getPreHead(), list.getNodeByIndex(1));
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.getNodeByIndex(0)->value, 2);
    ASSERT_EQ(list.getNodeByIndex(1)->value, 3);
}

TEST(linked_list_tests, DeleteNodes2) {
    LinkedList<int> list;
    int elements[4] = { 0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
        list.addElementToEnd(elements[i]);

    list.deleteNodes(list.getNodeByIndex(1), list.getNodeByIndex(2));
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.getNodeByIndex(0)->value, 0);
    ASSERT_EQ(list.getNodeByIndex(1)->value, 1);
    ASSERT_EQ(list.getNodeByIndex(2)->value, 3);
}

TEST(linked_list_tests, DeleteNodes3) {
    LinkedList<int> list;
    int elements[4] = { 0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
        list.addElementToEnd(elements[i]);

    EXPECT_THROW(list.deleteNodes(list.getNodeByIndex(2), list.getNodeByIndex(5)), std::out_of_range);
    ASSERT_EQ(list.size(), 4);

    list.deleteNodes(list.getNodeByIndex(1), list.getTailNode());
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.getNodeByIndex(0)->value, 0);
    ASSERT_EQ(list.getNodeByIndex(1)->value, 1);
    ASSERT_EQ(list.getTailNode()->value, 1);
}

TEST(linked_list_tests, DeleteNextNode) {
    LinkedList<int> list;
    int elements[4] = { 0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
        list.addElementToEnd(elements[i]);

    EXPECT_EQ(list.size(), 4);
    list.deleteNextNode(list.getTailNode());
    EXPECT_EQ(list.size(), 4);

    EXPECT_EQ(list.size(), 4);
    EXPECT_THROW(list.deleteNextNode(list.getNodeByIndex(6)), std::out_of_range);
    EXPECT_EQ(list.size(), 4);

    list.deleteNextNode(list.getNodeByIndex(2));
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getTailNode()->value, 2);

    list.deleteNextNode(list.getPreHead());
    EXPECT_EQ(list.getNodeByIndex(0)->value, 1);
    EXPECT_EQ(list.size(), 2);
}

TEST(linked_list_tests, MoveNodesToEnd) {
    LinkedList<int> list1;
    int elements1[4] = { 0, 1, 2, 3};

    LinkedList<int> list2;
    int elements2[4] = { 4, 5, 6, 7};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
        list2.addElementToEnd(elements2[i]);
    }

    list2.moveNodesToEnd(list1.getNodeByIndex(0), list1.getNodeByIndex(2));
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 3);
    EXPECT_EQ(list2.size(), 6);
    EXPECT_EQ(list2[0], 4);
    EXPECT_EQ(list2[1], 5);
    EXPECT_EQ(list2[2], 6);
    EXPECT_EQ(list2[3], 7);
    EXPECT_EQ(list2[4], 1);
    EXPECT_EQ(list2[5], 2);
}

TEST(linked_list_tests, MoveNodesToEnd2) {
    LinkedList<int> list1;
    int elements1[4] = { 0, 1, 2, 3};

    LinkedList<int> list2;
    int elements2[4] = { 4, 5, 6, 7};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
        list2.addElementToEnd(elements2[i]);
    }

    list1.moveNodesToEnd(list2.getPreHead(), list2.getTailNode());
    EXPECT_EQ(list2.size(), 0);
    EXPECT_EQ(list1.size(), 8);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 4);
    EXPECT_EQ(list1[5], 5);
    EXPECT_EQ(list1[6], 6);
    EXPECT_EQ(list1[7], 7);

    list2.moveNodesToEnd(list1.getPreHead(), list1.getNodeByIndex(0));
    EXPECT_EQ(list2.size(), 1);
    EXPECT_EQ(list2[0], 0);
    EXPECT_EQ(list1.size(), 7);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_EQ(list1[4], 5);
    EXPECT_EQ(list1[5], 6);
    EXPECT_EQ(list1[6], 7);
}

TEST(linked_list_tests, MoveNodeToEnd) {
    LinkedList<int> list1;
    int elements1[4] = { 0, 1, 2, 3};

    LinkedList<int> list2;
    int elements2[4] = { 4, 5, 6, 7};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
        list2.addElementToEnd(elements2[i]);
    }

    list1.moveNodeToEnd(list2.getPreHead());
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 7);

    list2.moveNodeToEnd(list1.getNodeByIndex(3));
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 7);
    EXPECT_EQ(list2[3], 4);

    list2.moveNodeToEnd(list1.getNodeByIndex(1));
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list2.size(), 5);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 7);
    EXPECT_EQ(list2[3], 4);
    EXPECT_EQ(list2[4], 2);
}

TEST(linked_list_tests, MoveNodeAfter) {
    LinkedList<int> list1;
    int elements1[4] = { 0, 1, 2, 3};
    LinkedList<int> list2;
    int elements2[4] = { 4, 5, 6, 7};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
        list2.addElementToEnd(elements2[i]);
    }

    list1.moveNodeAfter(list1.getTailNode(), list2.getPreHead());
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 7);

    list2.moveNodeAfter(list2.getNodeByIndex(1), list1.getNodeByIndex(1));
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 2);
    EXPECT_EQ(list2[3], 7);
}

TEST(linked_list_tests, MoveNodesAfter) {
    LinkedList<int> list1;
    int elements1[4] = { 0, 1, 2, 3};

    LinkedList<int> list2;
    int elements2[4] = { 4, 5, 6, 7};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
        list2.addElementToEnd(elements2[i]);
    }
    list1.moveNodesAfter(list1.getTailNode(), list2.getPreHead(), list2.getNodeByIndex(0));
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 5);
    EXPECT_EQ(list2[1], 6);
    EXPECT_EQ(list2[2], 7);

    list1.moveNodesAfter(list1.getTailNode(), list2.getPreHead(), list2.getTailNode());
    EXPECT_EQ(list1.size(), 8);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 4);
    EXPECT_EQ(list1[5], 5);
    EXPECT_EQ(list1[6], 6);
    EXPECT_EQ(list1[7], 7);
    EXPECT_EQ(list2.size(), 0);

    list2.moveNodesAfter(list2.getPreHead(), list1.getNodeByIndex(2), list1.getNodeByIndex(5));
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 6);
    EXPECT_EQ(list1[4], 7);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 3);
    EXPECT_EQ(list2[1], 4);
    EXPECT_EQ(list2[2], 5);

    EXPECT_THROW(list2.moveNodesAfter(list2.getNodeByIndex(10), list1.getNodeByIndex(2), list1.getNodeByIndex(5)), std::out_of_range);
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 6);
    EXPECT_EQ(list1[4], 7);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 3);
    EXPECT_EQ(list2[1], 4);
    EXPECT_EQ(list2[2], 5);

    EXPECT_THROW(list2.moveNodesAfter(list2.getPreHead(), list1.getNodeByIndex(8), list1.getNodeByIndex(5)), std::out_of_range);
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 6);
    EXPECT_EQ(list1[4], 7);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[0], 3);
    EXPECT_EQ(list2[1], 4);
    EXPECT_EQ(list2[2], 5);
}

TEST(linked_list_tests, CopyConstructor) {
    LinkedList<int> list;
    int a = 2;
    list.addElementToEnd(a);
    a = 3;
    list.addElementToEnd(a);
    a = 4;
    list.addElementToEnd(a);

    LinkedList<int> copy(list);

    copy[0] = 24;

    list[2] = 47;

    ASSERT_EQ(2, list[0]);
    ASSERT_EQ(3, list[1]);
    ASSERT_EQ(47, list[2]);

    ASSERT_EQ(24, copy[0]);
    ASSERT_EQ(3, copy[1]);
    ASSERT_EQ(4, copy[2]);
}


TEST(linked_list_tests, getOperator) {
    LinkedList<int> list1;
    EXPECT_THROW(list1[0], std::out_of_range);

    int elements1[4] = { 0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
    {
        list1.addElementToEnd(elements1[i]);
    }


    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1[0], 0);
    EXPECT_EQ(list1[1], 1);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_THROW(list1[-1], std::out_of_range);
    EXPECT_THROW(list1[4], std::out_of_range);
}