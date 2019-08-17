#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

//Необходимо реализовать метод используя рекурсивный подход
int LevenshteinDistance(string& s, int len_s, string& t, int len_t)
{
    /* i tried to implement it using string.substr(0, len_x - 1)
     * but it i couldnt use string& in function as parameter
     *
     * your parameters helped me to understand i can use
     * passing ints as "pseudo-length" and not cut strings
     */

    if (len_s == 0) return len_t;
    if (len_t == 0) return len_s;

    // checked last symbols equality
    // if they are the same - already launching next function
    // because we dont need to + 1 here
    if (s[len_s - 1] == t[len_t - 1])
        return LevenshteinDistance(s, len_s - 1, t, len_t - 1);

    return // + 1 to any command - insert, delete or replace
    1 + min (
            LevenshteinDistance(s, len_s - 1, t, len_t),
        min
        (
            LevenshteinDistance(s, len_s, t, len_t - 1),
            LevenshteinDistance(s, len_s - 1, t, len_t - 1)
        )
    );
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string N;
        getline(fin,N);
        int n = atoi( N.c_str());
        for (int i = 0; i < n; i++) {
            string s;
            string t;
            getline(fin,s);
            getline(fin,t);
            fout << LevenshteinDistance(s,s.length(), t, t.length()) << (i == n-1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}
