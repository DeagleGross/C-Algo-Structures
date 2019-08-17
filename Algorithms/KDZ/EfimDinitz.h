//
// Created by DG Coach on 27.03.2019.
//

#ifndef KDZ_EFIMDINITZ_H
#define KDZ_EFIMDINITZ_H

#include "Debugger.h"
#include "AlgoHelper.h"

#include <vector>
#include <stdexcept>
#include <queue>
#include <chrono>

using namespace std;

class EfimDinitz
{
private:
    const int amountOfTests = 10;
    const string path = "../output/EfimDinitz/";
    const string CSV = "../output/Dinitz.csv";

private:
    bool bfs(vector<vector<int>>& matrix, int istok, int final, vector<int>& levels)
    {
        // in BFS using queue structure
        queue<int> q;
        levels[istok] = 0;
        q.push(istok);

        while (!q.empty())
        {
            int u = q.front(); q.pop();

            for (int v = 0; v < matrix.size(); ++v)
            {
                int uv = matrix[u][v];
                if (uv > 0 && levels[v] == INT32_MAX)
                {
                    levels[v] = levels[u] + 1;
                    q.push(v);
                }
            }
        }

        return (levels[final] != INT32_MAX);
    }

    int dfs(vector<vector<int>>& matrix, int istok, int final, int flow, vector<int>& p, vector<int>& levels)
    {
        if (istok == final || flow == 0)
            return flow;

        for (int v = p[istok]; v < matrix.size(); ++v)
        {
            if (levels[v] == levels[istok] + 1)
            {
                int delta = dfs(matrix, v, final, min(flow, matrix[istok][v]), p, levels);
                if (delta != 0)
                {
                    matrix[istok][v] -= delta;
                    matrix[v][istok] += delta;
                    return delta;
                }
            }

            // deleting istok
            p[istok]++;
        }

        return 0;
    }

public:
    int getAmountOfTests() { return this->amountOfTests; }
    string getPathToWrite(){ return this->path; }
    string getCSVToWrite(){ return this->CSV; }

    int algorithm(vector<vector<int>> matrix, long long& time)
    {
        // time start count
        auto start = std::chrono::high_resolution_clock::now();

        DebugHelper debugHelper;
        AlgoHelper algoHelper;

        int N = matrix.size();

        int istok = algoHelper.getIstok(matrix);
        int final = algoHelper.getFinal(matrix);

        // making a copy to find ABS(COPY - MATRIX) later as a result
        vector<vector<int>> copy = matrix;

        int max_flow = 0;

        // ALGO HERE

        vector<int> d = vector<int>(matrix.size(), INT32_MAX);
        while(bfs(matrix, istok, final, d))
        {
            /*
             * "p[u] = номер первого неудалённого ребра, идущего из u" (C)
             */
            vector<int> p = vector<int>(matrix.size(), 0);
            int flow = dfs(matrix, istok, final, INT32_MAX, p, d);
            while (flow != 0)
            {
                max_flow += flow;
                flow = dfs(matrix, istok, final, INT32_MAX, p, d);
            }

            d = vector<int>(matrix.size(), INT32_MAX);
        }

        // time finish count
        auto diff = std::chrono::high_resolution_clock::now() - start;
        auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        time = nsec.count();

        algoHelper.getResultMatrix(matrix, copy);

        return max_flow;
    }
};

#endif //KDZ_EFIMDINITZ_H
