#include "ReadWriter.h"
#include <limits.h>
#include <queue>
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

// used for list smejnosti
// matrix vector<vector<int>> was tested and is too slow
class Node
{
public:
    vector<Edge> edges;
};

vector<Node> toListSmejnosti(int N, int M, vector<Edge>& edges)
{
    vector<Node> nodes = vector<Node>(N);
    for(int i = 0; i < M; ++i)
        nodes[edges[i].A].edges.push_back(edges[i]);

    return nodes;
}

void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    if (result.size() == 0)
        return;

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result[i].size(); ++j)
        {
            // ignoring diagonal elements
            if (i == j)
                continue;

            fout << i << " " << j << " ";

            // writing -1 if no road
            if (result[i][j] == INT32_MAX)
                fout << -1 << "\n";
            else
                fout << result[i][j] << "\n";
        }
    }
}

// returns true if not found -cikl
bool solveFord(int N, int M, vector<Edge> edges, vector<int>& result)
{
    // just copied fordBellman algo from task 2 //
    // now with new tests - returning false //

    bool foundAnyPath = false;
    // through all Nodes
    for (int i = 0; i < N - 1; ++i)
    {
        foundAnyPath = false;
        // through all Edges
        for (int j = 0; j < M; ++j)
            // if distance to J node less than INF
            if (result[edges[j].A] < INT32_MAX)
            {
                // trying to relax to other node - to B through edge A-B with weight W
                if (result[edges[j].A] + edges[j].W < result[edges[j].B])
                {
                    result[edges[j].B] = result[edges[j].A] + edges[j].W;
                    foundAnyPath = true;
                }
                //result[edges[j].B] = min(result[edges[j].B], result[edges[j].A] + edges[j].W);
            }
    }

    // deleting that fake node
    result.pop_back();

    return foundAnyPath;
}

void deikstra(int start, vector<Node>& matrix, vector<int>& result)
{
    // standart initialization in deikstra
    /* queue:
     * (used fast deikstra with use of priority-queue)
     *      int key - weight of edge
     *      int value - id of node
     */
    priority_queue<pair<int, int>> q;
    result[start] = 0;
    q.push(make_pair(0, start));

    while(!q.empty())
    {
        // get first valuable from queue
        int weight = -q.top().first;
        int curId = q.top().second;
        q.pop();

        // checking if this concrete node is the needed one
        if(weight > result[curId])
            continue;

        // going through all edges from this node
        for(int j = 0; j < matrix[curId].edges.size(); ++j)
        {
            int destination = matrix[curId].edges[j].B;
            int W = matrix[curId].edges[j].W;

            // minimizing weight to this node
            if (result[curId] + W < result[destination])
            {
                result[destination] = result[curId] + W;
                q.push(make_pair(-result[destination], destination));
            }
        }
    }
}

/// fake node addition
vector<Edge> getEdgesWithFakeNodeToEachNode(int N, vector<Edge> edges)
{
    Edge fake = Edge();
    fake.A = N;
    fake.W = 0;
    for (int curr = 0; curr < N; ++curr)
    {
        fake.B = curr;
        edges.push_back(fake);
    }

    return edges;
}

/// sets vector of weights of each node
vector<int> getFordBellmanResultVector(int N)
{
    vector<int> fordRes = vector<int>(N + 1, INT32_MAX);

    // stated that fordRes of NEW ADDED NODE is ZERO - fake node
    fordRes[N] = 0;

    return fordRes;
}

/// initialization of final vector-vector with only INT32_MAXes
vector<vector<int>> getResultInitialized(int N)
{
    vector<vector<int>> result = vector<vector<int>>(N);
    for (int i = 0; i < N; ++i)
        result[i] = vector<int>(N, INT32_MAX);

    return result;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    // vector of distance to every node
    vector<int> fordRes = getFordBellmanResultVector(N);

    // ford bellman from THAT NEW ADDED NODE
    // using N + 1 nodes
    // using M + N (to each node we add edge)
    // using new created vector with added N nodes in the end
    // using new fordRes vector of distances to nodes
    if (solveFord(N + 1, M + N, getEdgesWithFakeNodeToEachNode(N, edges), fordRes))
    {
        result = vector<vector<int>>();
        return;
    }

    // in Johnson algo using this formula to delete all negative edges
    for(int i = 0; i < M; ++i)
        edges[i].W = edges[i].W + fordRes[edges[i].A] - fordRes[edges[i].B];

    // finally reached deikstra algorithm
    result = getResultInitialized(N);

    // using list of nodes because matrix is too slow - tested last times
    vector<Node> matrix = toListSmejnosti(N, M, edges);
    for (int i = 0; i < N; ++i)
    {
        // launching deikstra from i Node
        deikstra(i, matrix, result[i]);

        // making obratnoe preobrazovanie - Johnson part
        for(int j = 0; j < N; ++j)
            result[i][j] = result[i][j] + fordRes[j] - fordRes[i];
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

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<vector<int>> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeValues(result);

    return 0;
}