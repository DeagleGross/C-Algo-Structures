#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

// to get vector
vector<vector<int>> getLCSvector(string& x, string& y)
{
    unsigned int len_X = x.length() + 1;
    unsigned int len_Y = y.length() + 1;

    vector<vector<int>> L = vector<vector<int>>(len_X, vector<int>(len_Y, 0));

    for (int i = 1; i < len_X; ++i)
    {
        for (int j = 1; j < len_Y; ++j)
        {
            // if the same symbols -> +1 from diagonal
            if (x[i-1] == y[j-1])
            {
                L[i][j] = L[i-1][j-1] + 1;
            }
            else // picking max value from side values
                L[i][j] = max(L[i][j-1], L[i-1][j]);
        }
    }

    return L;
}

// to re_initialize string
string AssembleLCS(string& x, string& y, vector<vector<int>>& L, int i, int j)
{
    // if nothing to find -> return "";
    if (L[i][j] == 0)
        return "";

    // if both letters are the same - adding it and going to diagonal to top
    // we are passing [length][length] so we have to use -1 here
    if (x[i - 1] == y[j - 1])
        return AssembleLCS(x, y, L, i-1, j-1) + x[i - 1]; // and here x[i !!!!-1!!!!]
    else
    {
        // taking the shortest? path
        if (L[i-1][j] < L[i][j-1])
            return AssembleLCS(x, y, L, i, j-1);
        else
            return AssembleLCS(x, y, L, i-1, j);
    }
}

// main function
string getLCS(string& x, string& y)
{
    vector<vector<int>> L = getLCSvector(x, y);
    return AssembleLCS(x, y, L, x.length(), y.length());
}

int main()
{
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}