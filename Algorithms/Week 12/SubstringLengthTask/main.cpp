#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

/// for debug
void showVector(vector<vector<int>>& L)
{
    for (int i = 0; i < L.size(); ++i)
    {
        for (int j = 0; j < L.size(); ++j)
        {
            cout << L[i][j] << " ";
        }

        cout << endl;
    }
}

int getLCS(string x, string y)
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

//    cout << "x = " << x << " ; y = " << y << endl;
//    cout << "x.len = " << len_X << " ; y.len = " << len_Y   << endl;
//    showVector(L);

    // again returning the element on side
    return L[len_X - 1][len_Y - 1];
}

int main()
{
    string x;
    string y;
    int res;

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