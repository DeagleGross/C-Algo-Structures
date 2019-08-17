//
// Created by DG Coach on 25.03.2019.
//
#include <iostream>
#include <stack>
#include <cstring>
#include <chrono>

#include "AlgoHelper.h"

using namespace std;

class FordFulkerson
{
private:
    const int amountOfTests = 6;
    const string path = "../output/FordFulkerson/";
    const string CSV = "../output/Ford.csv";

private:
    /// DFS used in FordFulkerson
    int dfs(int flow, vector<vector<int>>& matrix, int istok, int final, vector<int>& fullPath)
    {
        vector<bool> visited = vector<bool>(matrix.size());

        // in BFS using queue structure
        stack<int> q;
        q.push(istok);
        visited[istok] = true;

        while (!q.empty())
        {
            int current = q.top();
            q.pop();

            // going through all of current's edges
            for (int i = 0; i < matrix.size(); ++i)
            {
                if (!visited[i] && matrix[current][i] > 0)
                {
                    q.push(i);
                    fullPath[i] = current;
                    visited[i] = true;
                }
            }
        }

        if (visited[final])
        {
            int path_flow = INT32_MAX;
            for (int v = final; v != istok; v = fullPath[v])
                path_flow = min(path_flow, matrix[fullPath[v]][v]);

            // update residual capacities of the edges and reverse edges
            // along the path
            for (int v = final; v != istok; v = fullPath[v])
            {
                matrix[fullPath[v]][v] -= path_flow;
                matrix[v][fullPath[v]] += path_flow;
            }

            return path_flow;
        }

        // if reached final from istok - true
        // else - false
        return 0;
    }

public:
    int getAmountOfTests() { return this->amountOfTests; }
    string getPathToWrite(){ return this->path; }
    string getCSVToWrite(){ return this->CSV; }

    /// returns max_flow in graph
    /// used BFS in this algorithm
    int algorithm(vector<vector<int>>& matrix, long long& time)
    {
        // time start count
        auto start = std::chrono::high_resolution_clock::now();

        AlgoHelper algoHelper;

        int istok = algoHelper.getIstok(matrix);
        int final = algoHelper.getFinal(matrix);

        if (istok == -1 || final == -1)
            throw invalid_argument("Not found istok and final in matrix.");

        int N = matrix.size();

        // making a copy to find ABS(COPY - MATRIX) later as a result
        vector<vector<int>> copy = matrix;

        // initialization
        vector<int> fullPath = vector<int>(N);
        int fullFlow = 0;
        int pathIndex = 0;

        int subFlow = dfs(INT32_MAX, matrix, istok, final, fullPath);
        fullFlow += subFlow;

        while (subFlow != 0)
        {
            subFlow = dfs(INT32_MAX, matrix, istok, final, fullPath);
            fullFlow += subFlow;
        }

        // time finish count
        auto diff = std::chrono::high_resolution_clock::now() - start;
        auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        time = nsec.count();

        algoHelper.getResultMatrix(matrix, copy);

        // returning full flow
        return fullFlow;
    }
};