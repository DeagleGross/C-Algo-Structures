#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int getBackpackMoney(unsigned int n, unsigned int m, vector<int>& objects, vector<int>& coins)
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

    return s[n][m];
}

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
        fin >> n >> m;

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

    res = getBackpackMoney(n, m, objects, coins);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}