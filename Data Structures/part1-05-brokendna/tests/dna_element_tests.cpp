#include "gtest/gtest.h"
#include "dna_element.h"
#include <exception>

DNAElement createSystemUnderTestForDNA() {
    DNAElement sut;
    return sut;
}

TEST(dna_element_tests, basic_test1) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("a5:T");
    ASSERT_EQ("a", sut.id);
    ASSERT_EQ(5, sut.number);
    ASSERT_EQ("T", sut.base);
}

TEST(dna_element_tests, basic_test2) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("z2:T");
    ASSERT_EQ("z", sut.id);
    ASSERT_EQ(2, sut.number);
    ASSERT_EQ("T", sut.base);
}

TEST(dna_element_tests, basic_test3) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("x7:G");
    ASSERT_EQ("x", sut.id);
    ASSERT_EQ(7, sut.number);
    ASSERT_EQ("G", sut.base);
}

// iterating the base
TEST(dna_element_tests, base1) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("a5:T");
    ASSERT_EQ("T", sut.base);
}

TEST(dna_element_tests, base2) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("a5:C");
    ASSERT_EQ("C", sut.base);
}

TEST(dna_element_tests, base3) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("a5:A");
    ASSERT_EQ("A", sut.base);
}

TEST(dna_element_tests, base4) {
    DNAElement sut = createSystemUnderTestForDNA();
    sut.readFromString("a5:G");
    ASSERT_EQ("G", sut.base);
}

TEST(dna_element_tests, not_appropriate_base1) {
    DNAElement sut = createSystemUnderTestForDNA();
    ASSERT_THROW(sut.readFromString("a5:X"), std::invalid_argument);
}








TEST(dna_element_tests, inappropriate_id1) {
    ASSERT_THROW(createSystemUnderTestForDNA().readFromString("н7:G"), std::invalid_argument);
}


