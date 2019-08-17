#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

/// for debug
void show(vector<int>& p)
{
    for (int i = 0; i < p.size(); ++i)
        cout << p[i] << " ";
    cout << "\n";
}

/// uppers all numbers
/// from i+1 pos to last
void makeBigger(vector<int>& p, int i)
{
    for (int j = i; j < p.size()-1; ++j)
        p[j + 1] = p[j] + 1;
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N,int k, int m)
{
    vector<int> p = vector<int>();
    for (int i = 1; i <= m; ++i)
        p.push_back(i);

    // for indexes to match
    --m;

    while (m >= 0 && k >= 2)
    {
        // current-index-number didn't reach max
        if (p[m] < N)
        {
            ++p[m];
            makeBigger(p, m);
        }
        else
        {
            // going back to first indexes
            --m;
            // incrementing it
            ++p[m];
            // making bigger every further number
            makeBigger(p, m);
            // going back to that index to increment rightest-numbers
            ++m;
        }

        // debug
        //cout << "k = " << k << "; transpose = ";
        //show(p);
        --k;
    }

    string result = "";
    for (int i = 0; i < p.size() - 1; ++i)
        result += to_string(p[i]) + ' ';
    result += to_string(p[p.size() - 1]);

    return result;
}

int main(int argc, const char * argv[])
{
    int M,N,K;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string str;
        getline(fin,str);
        N = atoi( str.c_str());
        getline(fin,str);
        K = atoi( str.c_str());
        getline(fin,str);
        M = atoi( str.c_str());
        fout << get(N, K, M)<< endl;

        fout.close();
        fin.close();
    }
    return 0;
}