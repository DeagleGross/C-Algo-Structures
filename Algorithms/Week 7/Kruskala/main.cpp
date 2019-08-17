#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

class Node
{
public:
    int id;
    int component;

    Node(int id)
    {
        this->id = id;
        this->component = id;
    }

    /// for debug
    void toString()
    {
        cout << "Node (" << id << "), component = " << component << endl;
    }
};

/// initialization of vector
vector<Node*> getNodesInitialized(int N)
{
    vector<Node*> nodes = vector<Node*>(N);
    for (int i = 0; i < N; ++i)
        nodes[i] = new Node(i);

    return nodes;
}

/// Sort and custom Comparator
bool compareEdgeByWeight(Edge a, Edge b) { return (a.W < b.W); }
void sortEdgesByWeight(vector<Edge>& edges) { sort(edges.begin(), edges.end(), compareEdgeByWeight); }

/// Connection of components - rewriting component field in nodes
void connectComponents(vector<Node*>& nodes, int compONE, int compTWO)
{
    for (Node* node : nodes)
        if (node->component == compONE)
            node->component = compTWO;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    //Советую разделить решение на логические блоки
    //Можно использовать любые другие структуры, но затем скопировать ответ в структуру Edge для записи результата в файл.
    //Также можно добавить любые необходимые компараторы для предложенного класса Edge, так как все методы и поля публичные.

    vector<Node*> nodes = getNodesInitialized(N);

    // sorting edges by weight as in kruskala
    sortEdgesByWeight(edges);

    // it is filled - i watched it in debug
    // i want it empty to use push_back
    result.clear();

    for (Edge edge : edges)
    {
        // dont need to connect components if edge is going from component N to component N
        if (nodes[edge.A]->component != nodes[edge.B]->component)
        {
            connectComponents(nodes, nodes[edge.A]->component, nodes[edge.B]->component);
            result.push_back(edge);
        }
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
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}