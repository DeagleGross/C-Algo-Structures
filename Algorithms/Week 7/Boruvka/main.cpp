#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

class component
{
public:
    // id of component
    int numer;
    // its lvl from root in a tree MOD
    int lvl;
};

// returns number recursively
int getNumerOfComponent(component *components, int i)
{
    if (components[i].numer != i)
        components[i].numer = getNumerOfComponent(components, components[i].numer);

    return components[i].numer;
}

// connects components numered a and b
void connectionOfComponents(component* components, int a, int b)
{
    int aPar = getNumerOfComponent(components, a);
    int bPar = getNumerOfComponent(components, b);

    // connection of number to B parent tree
    if (components[aPar].lvl < components[bPar].lvl)
    {
        components[aPar].numer = bPar;
        return;
    }

    // connection of number to A parent tree
    if (components[aPar].lvl > components[bPar].lvl)
    {
        components[bPar].numer = aPar;
        return;
    }

    // connecting to a par tree and increasing lvl if this lvl isn't formed
    components[bPar].numer = aPar;
    ++components[aPar].lvl;
}

void initialize(component *components, int *cheapest, int N, bool atStart = false)
{
    for (int v = 0; v < N; ++v)
    {
        if (atStart)
        {
            components[v].numer = v;
            components[v].lvl = 0;
        }

        cheapest[v] = -1;
    }
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

    // number of components at start is N
    int amountOfComponents = N;

    // watched in debug - result vector is not empty at start
    // we have to clear it just to use push_back when edge is needed to be added
    result.clear();

    // at start there are N components
    component* components = new component[N];

    // vector storing cheapest edge of components
    int* cheapest = new int[N];

    // initialize at start
    initialize(components, cheapest, N, true);

    // MOD connects all nodes - we wait until components amount isn't 1
    while (amountOfComponents != 1)
    {
        // initialize only cheapest
        initialize(components, cheapest, N);

        /*
         * doin as in lecture pseudo-algo
         * going through all edges in graph
         */

        // going through all edges
        for (int i = 0; i < M; ++i)
        {
            // gettings numers of components of current edge
            int a = getNumerOfComponent(components, edges[i].A);
            int b = getNumerOfComponent(components, edges[i].B);

            // if edge is between 2 nodes of same component already - ignore
            if (a == b)
                continue;

            else
            {
                /* If not initialized
                 * path = INF == -1
                 */
                if (cheapest[a] == -1)
                    cheapest[a] = i;

                if (cheapest[b] == -1)
                    cheapest[b] = i;

                /* If is less than stored value
                 * Path != INF != -1
                 */
                if (edges[cheapest[a]].W > edges[i].W)
                    cheapest[a] = i;

                if (edges[cheapest[b]].W > edges[i].W)
                    cheapest[b] = i;
            }
        }

        // adding components to MOD
        for (int i = 0; i < N; ++i)
        {
            // if not formed cheapest value - do nothing
            if (cheapest[i] != -1)
            {
                int a = getNumerOfComponent(components, edges[cheapest[i]].A);
                int b = getNumerOfComponent(components, edges[cheapest[i]].B);

                // if edge is between 2 nodes of same component already - ignore
                if (a == b)
                    continue;

                // pushing edge to result - it was cleared before
                result.push_back(edges[cheapest[i]]);

                // connection of components numered a and b
                // amount of components decreased also
                connectionOfComponents(components, a, b);
                --amountOfComponents;
            }
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