#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/// builds table to get answer
vector<vector<int>> getDynamicTable(unsigned int n, unsigned int m, vector<int>& objects, vector<int>& coins)
{
    vector<vector<int>> s = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 1; w <= m; ++w)
        {
            if (w-objects[i-1] >= 0)
                s[i][w] = max(s[i-1][w], s[i-1][w-objects[i-1]] + coins[i-1]);
            else
                s[i][w] = s[i-1][w];
        }
    }

    return s;
}

/// returns all objects
void getUsedObjects(int n, int m, vector<vector<int>>& s, vector<int>& objects, vector<int>& coins, vector<int>& used_objects_weights, vector<int>& used_objects_coins, int& sum_weight)
{
    used_objects_weights = vector<int>();
    used_objects_coins = vector<int>();
    sum_weight = 0;

    int i = n; int j = m;

    while (s[i][j] != 0)
    {
        if (s[i-1][j] == s[i][j])
        {
            --i;
        }
        else
        {
            // saving results
            used_objects_weights.push_back(objects[i-1]);
            used_objects_coins.push_back(coins[i-1]);
            sum_weight += objects[i-1];

            // moving to upper-left of matrix
            j -= objects[i-1];
            --i;
        }
    }
}

/// main count method
int getBackpackMoney(int n, int m, vector<int>& objects, vector<int>& coins, vector<int>& used_objects_weights, vector<int>& used_objects_coins, int& sum_weight)
{
    vector<vector<int>> s = getDynamicTable(n, m, objects, coins);
    getUsedObjects(n, m, s, objects, coins, used_objects_weights, used_objects_coins, sum_weight);

    return s[n][m];
}

/// Не к всем работам вы стали прикладывать исходные коды
/// поэтому даже не обратил внимание, что они есть
/// Работу сделал в старом стиле с выносом метода расчета вне считывания параметров
int main()
{
    vector<int> objects = vector<int>();
    vector<int> coins = vector<int>();

    unsigned int n, m, a;
    int res;

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        fin >> m;

        for (int i = 0; i < n; ++i)
        {
            fin >> a;
            objects.push_back(a);
        }

        for (int i = 0; i < n; ++i)
        {
            fin >> a;
            coins.push_back(a);
        }

        fin.close();
    }

    vector<int> used_objects_weights = vector<int>();
    vector<int> used_objects_coins = vector<int>();
    int sum_weight;

    res = getBackpackMoney(n, m, objects, coins, used_objects_weights, used_objects_coins, sum_weight);

    fstream fout;
    fout.open("output.txt", ios::out);

    fout << res << "\n";
    fout << sum_weight << "\n";
    fout << used_objects_weights.size() << "\n";

    for (int i = 0; i < used_objects_weights.size(); ++i)
        fout << used_objects_weights[i] << " ";
    fout << "\n";

    for (int i = 0; i < used_objects_coins.size(); ++i)
        fout << used_objects_coins[i] << " ";

    fout.close();

    return 0;
}