#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

/// to debug
void showVector(vector<vector<int>>& A)
{
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < A[i].size(); ++j)
        {
            cout << A[i][j] << " ";
        }

        cout << endl;
    }
}

/// returns vector table
vector<vector<int>> getTableOfRocksWeights(int N, int W, int* stones)
{
    vector<vector<int>> A = vector<vector<int>>(N + 1, vector<int>(W + 1, 0));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < W + 1; ++j)
        {
            // added check on > 0 for exception avoid
            if (j - stones[i] >= 0)
                A[i + 1][j] = max(A[i][j], A[i][j - stones[i]] + stones[i]);
            else
                A[i + 1][j] = A[i][j];
        }
    }

    return A;
}

/// returns collection of result-weights used
void Way(vector<vector<int>>& A, vector<int>& res, int* stones, int i, int j)
{
    if (A[i][j] == 0)
        return;

    if (A[i][j] != A[i-1][j])
    {
        Way(A, res, stones, i-1, j-stones[i - 1]);
        res.push_back(stones[i - 1]);
    }
    else
        Way(A, res, stones, i-1, j);
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int* stones, vector<int>& res)
{
    res = vector<int>();
    vector<vector<int>> A = getTableOfRocksWeights(N, W, stones);

    //showVector(A);

    Way(A, res, stones, N, W);
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int* arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}