#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"
#include <vector>

using namespace std;


//Можно добавлять любые вспомогательные методы и классы для решения задачи.

/// for debug
void show(vector<vector<long long>>& d)
{
    for (int i = 0; i < d.size(); ++i)
    {
        for (int j = 0; j < d[i].size(); ++j)
        {
            if (d[i][j] == -1)
                cout << "x ";
            else
                cout << d[i][j] << " ";
        }

        cout << "\n";
    }
}

// recursive getting index
long long getIndex(int& N, int& M, vector<vector<long long>>& d, int i, int j)
{
    if (i >= N || j >= M || i < 0 || j < 0)
        return 0;

    if (d[i][j] == -1)
    {
        long long ind_1 = getIndex(N, M, d, i+1, j-2);
        long long ind_2 = getIndex(N, M, d, i-1, j-2);
        long long ind_3 = getIndex(N, M, d, i-2, j-1);
        long long ind_4 = getIndex(N, M, d, i-2, j+1);

        d[i][j] = ind_1 + ind_2 + ind_3 + ind_4;
    }

    return d[i][j];
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    vector<vector<long long>> d = vector<vector<long long>>(N, vector<long long>(M, -1));
    d[0][0] = 1;

    long long res = getIndex(N, M, d, N-1, M-1);
    //show(d);
    return res;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}