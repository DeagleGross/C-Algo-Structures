//
// Created by DG Coach on 29.03.2019.
//

#ifndef KDZ_BORDERMAKER_H
#define KDZ_BORDERMAKER_H

#include <vector>
#include <iostream>

using namespace std;

class AlgoHelper
{
public:
    int getIstok(vector<vector<int>>& matrix)
    {
        vector<int> istoks = vector<int>();

        for (int i = 0; i < matrix.size(); ++i)
        {
            bool pathToIt = false;
            for (int j = 0; j < matrix.size(); ++j)
            {
                if (matrix[j][i] != 0)
                {
                    pathToIt = true;
                    break;
                }
            }

            if (!pathToIt)
                istoks.push_back(i);
        }

        if (istoks.empty()) // error
            return -1;

        if (istoks.size() == 1) // the only istok found
            return istoks[0];

        if (istoks.size() > 1) // variant for DISCO matrixes
        {
            int rowOfFakeIstok = matrix.size();
            // added row for istok but of
            // size N
            matrix.push_back(vector<int>(matrix.size(), 0));

            // added column for istok so now it is
            // size(N+1 x N+1)
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i].push_back(0);

            for (int i = 0; i < istoks.size(); ++i)
            {
                // making capacity of really big number
                matrix[rowOfFakeIstok][istoks[i]] = INT32_MAX; // for rows
                matrix[istoks[i]][rowOfFakeIstok] = INT32_MAX; // for columns
            }

            return (rowOfFakeIstok);
        }

        return -1;
    }

    int getFinal(vector<vector<int>>& matrix)
    {
        vector<int> stoki = vector<int>();

        for (int i = 0; i < matrix.size(); ++i)
        {
            bool pathFromIt = false;
            for (int j = 0; j < matrix.size(); ++j)
            {
                if (matrix[i][j] != 0)
                {
                    pathFromIt = true;
                    break;
                }
            }

            if (!pathFromIt)
                stoki.push_back(i);
        }

        if (stoki.empty()) // error
            return -1;

        if (stoki.size() == 1) // the only istok found
            return stoki[0];

        if (stoki.size() > 1) // variant for DISCO matrixes
        {
            int rowOfFakeStok = matrix.size();

            // added row for Stok but of
            // size N
            matrix.push_back(vector<int>(matrix.size(), 0));

            // added column for Stok so now it is
            // size(N+1 x N+1)
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i].push_back(0);

            for (int i = 0; i < stoki.size(); ++i)
            {
                // making capacity of really big number
                matrix[rowOfFakeStok][stoki[i]] = INT32_MAX; // for rows
                matrix[stoki[i]][rowOfFakeStok] = INT32_MAX; // for columns
            }

            return (rowOfFakeStok);
        }

        return -1;
    }

    void getResultMatrix(vector<vector<int>>& matrix, vector<vector<int>>& copy)
    {
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix.size(); ++j)
                matrix[i][j] = (copy[i][j] - matrix[i][j] < 0) ? 0 : copy[i][j] - matrix[i][j];
    }
};

#endif //KDZ_BORDERMAKER_H
