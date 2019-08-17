//
// Created by DG Coach on 24.03.2019.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class ConstValues
{
    /// FIELDS
private:
    const unsigned int amount = 10;
    const string subPath = "../input/input_";
    vector<int> nums;

    const string rarefied = "_0.0.txt";
    const string medium = "_0.5.txt";
    const string tight = "_1.0.txt";
    const string disco = "_disco.txt";

    /// METHODS - PRIVATE
private:
    vector<string> getFiles(string type)
    {
        vector<string> files = vector<string>(amount);
        for (int i = 0; i < amount; ++i)
            files[i] = subPath + to_string(nums[i]) + type;
        return files;
    }

    /// CONSTRUCTOR
public:
    ConstValues(){
        nums = vector<int>(amount);

        for (int i = 0; i < amount; ++i)
            nums[i] = 10 + 300*i;
    }

    /// METHODS - PUBLIC
public:
    vector<string> getRarefiedInputFiles() { return getFiles(rarefied); }
    vector<string> getMediumInputFiles() { return getFiles(medium); }
    vector<string> getTightInputFiles() { return getFiles(tight); }
    vector<string> getDiscoInputFiles() { return getFiles(disco); }
    vector<int> getNumAmount() { return nums; }
};
