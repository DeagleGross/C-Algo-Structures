#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

void Solve(string& result, vector<int>& a, vector<bool>& s, int t, int m, int N, int& k)
{
    for (int i = 0; i < N; ++i)
    {
        // escaping from recursion really fast
        if (result != "")
            return;

        if (!s[i])
        {
            s[i] = true;
            a[t] = i + 1;
            if (t < m - 1)
                Solve(result, a, s, t + 1, m, N, k);
            else
            {
                --k;
                if (k == 0)
                {
                    // OTVET HERE
                    for (int i = 0; i < a.size() - 1; ++i)
                        result += to_string(a[i]) + ' ';
                    result += to_string(a[a.size()-1]);
                    return;
                }
            }

            s[i] = false;
        }
    }
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N,int k, int m)
{
    vector<bool> s = vector<bool>(N, false);
    vector<int> a = vector<int>(m);

    string result = "";
    Solve(result, a, s, 0, m, N, k);

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