#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h
#include <algorithm>
#include <climits>


using namespace std;
// write all values
void ReadWriter::writeValues(std::vector<std::vector<int>>& result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (i == j)
                continue;

            fout << i << " " << j << " ";

            if (result[i][j] == INT32_MAX)
                fout << -1;
            else
                fout << result[i][j];

            fout << "\n";
        }
    }
}

/// Returns easy-to-implement structure in this algo from vector of edges
vector<vector<int>> getMatrix(int N, vector<Edge>& edges)
{
    // initialization
    vector<vector<int>> matrix = vector<vector<int>>(N);
    for (int i = 0; i < N; ++i)
        matrix[i] = vector<int>(N);

    // placing all distances as intMax - similar to other tasks
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = INT32_MAX;

    // placing in matrix values that are passed in edges vector
    for (int i = 0; i < edges.size(); ++i)
        matrix[edges[i].A][edges[i].B] = edges[i].W;

    return matrix;
}

/// multiplication of matrix by itself
void getShortestPaths(vector<vector<int>>& D)
{
    int N = D.size();

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                if (D[i][k] != INT32_MAX && D[k][j] != INT32_MAX)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
}

void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& matrix)
{
    // getting NxN matrix from edges
    matrix = getMatrix(N, edges);

    /* using O (n3 * log n) variant
     * just multiplication of itself
     */
    for (int i = 1; i < N - 1; i *= 2)
    {
        getShortestPaths(matrix);
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}