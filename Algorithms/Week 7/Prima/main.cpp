#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

class Node
{
public:
    int id;
    int path; // like in Deikstra - value of node
    bool isUsed = false;
    vector<Edge> lines;

    Node(int path, int id)
    {
        this->id = id;
        this->path = path;
        lines = vector<Edge>();
    }

    /// for debug
    void toString()
    {
        cout << "Node (" << id << "), path = " << path << ";" << endl;
    }
};

/// comparing by path values
bool comparePtrToNode(Node* a, Node* b) { return (a->path < b->path); }

/// initializes vector of nodes
vector<Node*> initializeNodes(int N)
{
    vector<Node*> nodes = vector<Node*>(N);
    nodes[0] = new Node(0, 0);
    for (int i = 1; i < N; ++i)
        nodes[i] = new Node(-1, i);

    return nodes;
}

/// filling edges of nodes - making list in every object
void rewriteEdgesToNodes(vector<Node*>& nodes, vector<Edge> edges)
{
    for (int i = 0; i < edges.size(); ++i)
    {
        nodes[edges[i].A]->lines.push_back(edges[i]);
        nodes[edges[i].B]->lines.push_back(edges[i]);
    }
}

void currentNodeObxod(int& pos, vector<Node*>& nodes, vector<Node*>& queue, vector<Edge>& result)
{
    // incrementing pos for queue sort from needed position
    Node* current = queue[pos++];
    current->isUsed = true;

    for (int i = 0; i < current->lines.size(); ++i)
    {
        // taking current edge
        Edge* edge = &current->lines[i];
        int a = edge->A;
        int b = edge->B;

        // if edge is --->
        if (current->id == a)
        {
            if (!nodes[b]->isUsed)
            {
                // if not visited still - adding to queue
                // and continue
                if (nodes[b]->path == -1)
                {
                    nodes[b]->path = edge->W;
                    result[b - 1] = *edge;
                    queue.push_back(nodes[b]);
                    continue;
                }

                // else just fill path and result
                if (edge->W < nodes[b]->path)
                {
                    nodes[b]->path = edge->W;
                    result[b - 1] = *edge;
                }
            }
        }

        // if edge is <---
        if (current->id == b)
        {
            if (!nodes[a]->isUsed)
            {
                // if not visited still - adding to queue
                // and continue
                if (nodes[a]->path == -1)
                {
                    nodes[a]->path = edge->W;
                    result[a - 1] = *edge;
                    queue.push_back(nodes[a]);
                    continue;
                }

                if (edge->W < nodes[a]->path)
                {
                    nodes[a]->path = edge->W;
                    result[a - 1] = *edge;
                }
            }
        }
    }

    // sorting from POS to end of queue to take next element with
    // MIN PATH
    sort(queue.begin() + pos, queue.end(), comparePtrToNode);
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

    result.clear();
    result = vector<Edge>(N - 1);

    vector<Node*> nodes = initializeNodes(N);
    rewriteEdgesToNodes(nodes, edges);

    vector<Node*> queue = vector<Node*>();
    queue.push_back(nodes[0]);

    int pos = 0;

    // surely pos will reach N value
    while (pos != N)
        currentNodeObxod(pos, nodes, queue, result);
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