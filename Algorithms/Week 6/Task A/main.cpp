#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

/// first proxod and order setup
void DFS_1(int index, vector<int>& order, vector<bool>& used, vector<string>& names, vector<vector<bool>>& relations)
{
    // placing used flag
    used[index] = true;
    for (size_t i = 0; i < relations[index].size(); ++i)
        if (!used[i] && relations[index][i]) // if wasnt used in DFS and has road to that node
            DFS_1(i, order, used, names, relations);
    order.push_back(index);
}

/// transposes vector<vector<bool>>
void transposeRelations(vector<vector<bool>>& relations)
{
    for (int i = 0; i < relations.size(); ++i)
        for (int j = i; j < relations[i].size(); ++j)
            swap(relations[i][j], relations[j][i]);
}

/// returns connect-component - vector of strings
void DFS_2(int index, vector<int>& order, vector<bool>& used, vector<string>& names, vector<vector<bool>>& relations, vector<string>& component)
{
    used[index] = true;
    component.push_back(names[index]);
    for (size_t i = 0; i < relations[index].size(); ++i)
        if (!used[i] && relations[index][i])
            DFS_2(i, order, used, names, relations, component);
}

void sortComponentsInside(vector<vector<string>>& components)
{
    for (int i = 0; i < components.size(); ++i)
    {
        sort(components[i].begin(), components[i].end());
    }
}

void sortComponentsOutside(vector<vector<string>>& components)
{
    sort(components.begin(), components.end());
}

/// returns vector of connectivity-components - sorted by first-name in group alphabetically
/// inside each vector there is vector - sorted alphabetically
vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations)
{
    // n - size
    // used - vector containing info about was node visited or not
    unsigned int n = names.size();
    vector<bool> used = vector<bool>(n);

    // contains indexes of names to use in dfs_2
    vector<int> order = vector<int>();

    // doing dfs_1 and setting
    for (int i = 0; i < n; ++i)
        if (!used[i])
            DFS_1(i, order, used, names, relations);

    // transposing relations for dfs_2
    transposeRelations(relations);

    // reassigned - for setting it FALSE again
    used = vector<bool>(n);

    // vector that will be returned
    int k = 0;
    vector<vector<string>> components = vector<vector<string>>();

    for (int i=0; i < n; ++i) {
        int v = order[n-1-i];
        if (!used[v]) {
            components.push_back(vector<string>());
            DFS_2(v, order, used, names, relations, components[k++]);
        }
    }

    /// sorting inside every group
    sortComponentsInside(components);

    /// sort groups by its first elements
    sortComponentsOutside(components);

    return components;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str = "";
        getline(fin, str);

        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}