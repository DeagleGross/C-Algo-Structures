#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

/// Returns easy-to-implement structure in this algo from vector of edges
vector<vector<pair<int,int>>> getListSmejnosti(int N, int M, vector<Edge>& edges)
{
    vector<vector<pair<int,int>>> list = vector<vector<pair<int,int>>>();
    for (int i = 0; i < N; ++i)
        list.push_back(vector<pair<int,int>>());

    for (int i = 0; i < M; ++i)
        list[edges[i].A].push_back(pair<int,int>(edges[i].B, edges[i].W));

    return list;
}

void initializeStartingVectors(vector<bool>& used, vector<int>& result, int N)
{
    result = vector<int>(N);
    used = vector<bool>(N);

    result[0] = 0;
    for (int i = 1; i < N; ++i)
        result[i] = INT32_MAX;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    vector<vector<pair<int,int>>> list = getListSmejnosti(N, M, edges);
    vector<bool> used;
    initializeStartingVectors(used, result, N);

    // through all nodes
    for (int i=0; i < N; ++i) {
        // searching the node with minimal DISTANCE to it
        int minNode = -1; // found node
        for (int j = 0; j < N; ++j)
        {
            bool tmpBool = used[j];
            int tmpInt = result[j];

            if (!used[j] && (minNode == -1 || result[j] < result[minNode]))
                minNode = j;
        }

        // stopping if didnt find anything
        if (result[minNode] == INT32_MAX)
            break;

        // placing flag
        used[minNode] = true;

        // going through all edges of that node
        for (int j = 0; j < list[minNode].size(); ++j)
        {
            int to = list[minNode][j].first;
            int len = list[minNode][j].second;
            if (result[minNode] + len < result[to])
                result[to] = result[minNode] + len;
        }
    }

    // deleting first one in result vector
    for (int i = 0; i < N - 1; ++i)
        result[i] = result[i+1];
    result.pop_back();
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

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}