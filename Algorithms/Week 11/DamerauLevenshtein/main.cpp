#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

// for debug
void showVectorVectorInt(vector<vector<int>>& d)
{
    for (int i = 0; i < d.size(); ++i)
    {
        for (int j = 0; j < d[i].size(); ++j)
            cout << d[i][j] << " ";
        cout << "\n";
    }

    cout << "\n";
}

/// my own min from 3 elems
int min (int& a, int& b, int& c)
{
    return (a < b) ? (a < c) ?  a : c : (b < c) ? b : c;
}

//Необходимо реализовать метод
//о алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer_for_Damerau_Levenshtein(string& s, string& t)
{
    int m = s.length();
    int n = t.length();

    // easy variant
    if (m == 0) return n;
    if (n == 0) return m;

    // proper initialization
    vector<vector<int>> d = vector<vector<int>>(m + 1, vector<int>(n+1, 0));
    for (int i = 0; i < n + 1; ++i)
        d[0][i] = i;
    for (int i = 0; i < m + 1; ++i)
        d[i][0] = i;

    // for debug
    // showVectorVectorInt(d);

    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            // if symbols are the same - rewriting last value
            if (s[i - 1] == t[j - 1])
                d[i][j] = d[i - 1][j - 1];

            // otherwise getting min of 3 values as done before
            // used my own min from 3 ints - it is faster as contest shows
            else
                d[i][j] = 1 + min(d[i][j - 1], d[i-1][j], d[i-1][j-1]);

            // transposition
            // have to use (i>1) and (j>1) to avoid RE
            if(i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1])
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + 1);
        }
    }

    // check matrix
    // showVectorVectorInt(d);

    return d[m][n];
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main(int argc, const char * argv[])
{
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string N;
        getline(fin,N);
        n = atoi( N.c_str());
        for (int i = 0; i < n; i++) {
            string s;
            string t;
            getline(fin,s);
            getline(fin,t);
            fout << Wagner_Fischer_for_Damerau_Levenshtein(s, t) << (i == n-1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}