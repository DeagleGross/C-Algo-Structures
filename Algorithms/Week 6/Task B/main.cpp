#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void sortAlphabetically(vector<pair<string, int>> &names);
void DFS(int index, vector<vector<bool>>& relations, vector<bool>& used, vector<string>& names, stack<int>& inOrder);
vector<pair<string, int>> findIstoki(vector<vector<bool>> relations, vector<string> names);

void DFS(int index, vector<vector<bool>>& relations, vector<bool>& used, vector<string>& names, vector<int>& inOrder)
{
    // placing used flag
    used[index] = true;

    // vector of pairs - all connections from THIS to any node
    // storing to sort them alphabetically
    vector<pair<string,int>> connections = vector<pair<string, int>>();

    // getting vector of pairs inside which there are connections from THIS INDEX
    for (size_t i = 0; i < relations[index].size(); ++i)
    {
        if (!used[i] && relations[i][index]) // if wasnt used in DFS and has road to that node
            connections.push_back(pair<string, int>(names[i], i));
    }

    // sorting connections alphabetically
    sortAlphabetically(connections);

    // through each connection going to DFS
    for (size_t i = 0; i < connections.size(); ++i)
    {
        int newIndex = connections[i].second;
        if (!used[newIndex])
        {
            DFS(newIndex, relations, used, names, inOrder);
        }
    }

    // pushing in the end - post order
    inOrder.push_back(index);
}

/// returns vector of pairs - istoki. Pair has its name and index
vector<pair<string, int>> findIstoki(vector<vector<bool>> relations, vector<string> names)
{
    vector<pair<string, int>> istoki = vector<pair<string,int>>();

    for (int i = 0; i < relations.size(); ++i)
    {
        bool hasConnections = false;

        for (int j = 0; j < relations[i].size(); ++j)
        {
            if (relations[j][i])
            {
                hasConnections = true;
                break;
            }
        }

        if (!hasConnections)
            istoki.push_back(pair<string, int>(names[i],i));
    }

    return istoki;
}

/// transposes vector<vector<bool>>
void transposeRelations(vector<vector<bool>>& relations)
{
    for (int i = 0; i < relations.size(); ++i)
        for (int j = i; j < relations[i].size(); ++j)
            swap(relations[i][j], relations[j][i]);
}

/// sorts vector of pairs <string, int> by its string value
void sortAlphabetically(vector<pair<string, int>> &names)
{
    sort(names.begin(), names.end());
}

/// main function - getting list - dressing room
vector<string> getList(vector<string> &names, vector<vector<bool>> &relations)
{
    // contains order in which nodes to output
    vector<int> inOrder = vector<int>();

    // setting used vector = false in start for each node
    vector<bool> used = vector<bool>(names.size());

    // got string of istoki - going through them
    vector<pair<string,int>> istoki = findIstoki(relations, names);

    // have to sort istoki by its alphabetical meaning
    // sorting by names - string field of pair<string,int>
    sortAlphabetically(istoki);

    // transposed for easy use
    transposeRelations(relations);

    // going through all istoki
    for (int i = 0; i < istoki.size(); ++i)
    {
        int index = istoki[i].second;
        if (!used[index])
        {
            DFS(index, relations, used, names, inOrder);
        }
    }

    // vector of string - result
    vector<string> result = vector<string>();

    // taking and writing from stack
    while(!inOrder.empty())
    {
        int index = inOrder[inOrder.size()-1];
        inOrder.pop_back();

        result.push_back(names[index]);
    }

    return result;
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

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}