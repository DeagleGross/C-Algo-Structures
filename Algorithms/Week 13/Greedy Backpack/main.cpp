#include "ReadWriter.h"
//vector, string, iostream, algorithm included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

class Obj
{
public:
    int weight;
    int coins;

    Obj(int weight, int coins)
        : weight(weight), coins(coins)
    {}

    /// for debug
    void toString() { cout << "obj: w= " << weight << ", c= " << coins << "\n" ; }
};

vector<Obj> rewriteToVector(int N, pair<int, int>* items)
{
    vector<Obj> objs = vector<Obj>();

    for (int i = 0; i < N; ++i)
        objs.push_back(Obj(items[i].first, items[i].second));

    return objs;
}

// to sort specifically
bool sortSpecific(Obj const& lhs, Obj const& rhs)
{
    double l = (double)lhs.coins / lhs.weight;
    double r = (double)rhs.coins / rhs.weight;

    if (l < r)
        return true;
    else if (r < l)
        return false;
    else // if unit-cost is the same - comparing weights
        return lhs.weight < rhs.weight;
}

//Задача реализовать этот метод (жадный алгоритм)
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
{
    res = vector<pair<int, int>>();
    vector<Obj> objs = rewriteToVector(N, items);

    // sorts by unit-cost and then by minimum weight
    sort(objs.begin(), objs.end(), sortSpecific);

    int sum_weight = 0;
    for (int i = objs.size()-1; i >= 0; --i)
    {
        if (sum_weight + objs[i].weight <= W)
        {
            sum_weight += objs[i].weight;
            res.push_back(pair<int, int>(objs[i].weight, objs[i].coins));
        }
    }
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество элементов, и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int>* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++)
    {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}