#include "gtest/gtest.h"
#include "dna_repairer.h"

using namespace std;
using xi::LinkedList;
using xi::Node;

// Only 3 ids are allowed in the DNA Repairing testing
class TestParam {
public:
    const string input;
    const string output;

    TestParam(const string input, const string output) : input(input), output(output){}
};

class DNARepairerTestFixture : public ::testing::TestWithParam<TestParam> { };

INSTANTIATE_TEST_CASE_P(DNARepairerTestSuite, DNARepairerTestFixture, ::testing::Values(
        TestParam("a1:T a5:A a4:G a3:A a2:G\n"
                  "b1:G a6:A\n"
                  "c1:A"
                  , // output should be sorted alphabetically (not required in DNAStorage)
                  "a1:T  a2:G  a3:A  a4:G  a5:A  a6:A  \n"
                  "b1:G  \n"
                  "c1:A  \n")
        
        , TestParam("a1:T c2:T a2:C a4:A b3:A b7:G \n"
                    "b1:G a6:G b4:T c4:C b5:C a5:T a3:C \n"
                    "c1:A b6:T c3:G b2:T"
                    , // output should be sorted alphabetically (not required in DNAStorage)
                    "a1:T  a2:C  a3:C  a4:A  a5:T  a6:G  \n"
                    "b1:G  b2:T  b3:A  b4:T  b5:C  b6:T  b7:G  \n"
                    "c1:A  c2:T  c3:G  c4:C  \n")
        
        , TestParam("a1:T  c2:T  a2:C  a4:A  d1:A  d2:A  b3:A  b7:G\n"
                    "b1:G  a6:G  b4:T  c4:C  b5:C  d3:T  d4:A  a5:T  a3:C\n"
                    "c1:A  b6:T  c3:G  b2:T  d5:A  d6:A"
                    , // output should be sorted alphabetically (not required in DNAStorage)
                    "a1:T  a2:C  a3:C  a4:A  a5:T  a6:G  \n"
                    "b1:G  b2:T  b3:A  b4:T  b5:C  b6:T  b7:G  \n"
                    "c1:A  c2:T  c3:G  c4:C  \n"
                    "d1:A  d2:A  d3:T  d4:A  d5:A  d6:A  \n")
        
        , TestParam("d3:A  a1:T  a2:C\n"
                    "a5:T  d4:G"
                    , // output should be sorted alphabetically (not required in DNAStorage)
                    "a1:T  a2:C  a5:T  \n"
                    "d3:A  d4:G  \n")

));

TEST_P(DNARepairerTestFixture, complex) {

    stringstream ssin(GetParam().input);
    
    DNARepairer repairer;
    repairer.readFromStream(ssin);
    repairer.repairDNA();
    cout << "unsorted result:\n";
    repairer.printDNAStorage();
    cout << endl;

    vector<string> chains;
    
    Node<xi::LinkedList<DNAElement>>* it = repairer.getDNAStorage().getPreHead();
    while (it->next) {
        it = it->next;
        chains.push_back(repairer.dnaChainToString(it));
    }
    
    sort(chains.begin(), chains.end());
    
    stringstream ssout;

    for (auto&& chain : chains)
        ssout << chain << endl;
    
    cout << "sorted result:\n" << ssout.str() << endl;
    ASSERT_EQ(ssout.str(), GetParam().output);
}