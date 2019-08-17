#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

/// for debug
void showVector(vector<int>& p)
{
    for (int i = 0; i < p.size(); ++i)
        cout << p[i] << " ";

    cout << "\n";
}

int get_i(vector<int>& p, int N)
{
    for (int i = N-2; i >= 0; --i)
    {
        if (p[i] < p[i+1])
            return i;
    }

    // returns -1 if it was last transposition
    return -1;
}

int get_j(vector<int>& p, int N, int i)
{
    int res = INT32_MAX;
    int index = INT32_MAX;

    for (int j = i+1; j <= N-1; ++j)
    {
        // that is less than res and MORE than P[I]
        if (p[j] < res && p[j] > p[i])
        {
            res = p[j];
            index = j;
        }
    }

    return index;
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get_day(int N,int k)
{
    vector<int> p = vector<int>();
    for (int i = 1; i <= N; ++i)
        p.push_back(i);

    // first initialization
    int i = get_i(p, N);

    // going in a loop
    // when k = 1 -> it is needed transposition
    while (i != -1 && k != 1)
    {
        // getting j index
        int j = get_j(p, N, i);

        // doing transpose of 2 elems
        swap(p[i], p[j]);

        // rewriting all elems
        vector<int> tmp = vector<int>();
        for (int a = N-1; a >= i+1; --a)
            tmp.push_back(p[a]);

        int l = 0;
        for (int b = i+1; b < N; ++b)
            p[b] = tmp[l++];

        i = get_i(p, N);
        --k;
    }

    // we store transposition in vector<int> P
    // filling result string
    string result = "";
    for (int str_i = 0; str_i < N - 1; ++str_i)
        result += to_string(p[str_i]) + ' ';
    result += to_string(p[N-1]);

    return result;
}

int main(int argc, const char * argv[]) {

    int N,K;
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
        fout << get_day(N,K)<< endl;

        fout.close();
        fin.close();
    }

    return 0;
}
