#include <iostream>
#include <fstream>
#include <vector>

#ifndef KDZ_DEBUGHELPER_H
#define KDZ_DEBUGHELPER_H

class DebugHelper
{
public:
    void logMatrix(const vector<vector<int>>& matrix)
    {
        std::cout << "\nMatrix::\n";
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
                std::cout << matrix[i][j] << " ";

            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void logVectorStrings(const vector<string> strings)
    {
        std::cout << "\nStrings;\n";
        for (int i = 0; i < strings.size(); ++i)
            std::cout << strings[i] << endl;
        std::cout << "\n";
    }
};


#endif //KDZ_DEBUGHELPER_H