#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

/// for debug
void showVectorInt(vector<int>& ints)
{
    for (int i = 0; i < ints.size(); ++i)
        cout << ints[i] << " ";
    cout << "\n";
}

/// returns vector of int - max len of same suff/pre-fix
vector<int> prefixFunction(string& s)
{
    unsigned int len = s.length();
    vector<int> grani = vector<int>(len, 0);

    for (int i = 1; i < len; ++i)
    {
        int tmp = grani[i-1];
        while (tmp > 0 && s[i] != s[tmp])
            tmp = grani[tmp-1];

        if (s[i] == s[tmp])
            ++tmp;

        grani[i] = tmp;
    }

    return grani;
}

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    // SUB!STR
    string shared = substring + "!" + source;

    // got lengths of all strings incoming
    int len_sub = substring.length();
    int len_str = source.length();

    // array of grani
    vector<int> arr = prefixFunction(shared);

    // going form sub!*here*string
    for (int i = len_sub + 1; i < len_sub + 1 + len_str; ++i)
        if (arr[i] == len_sub)
            res.push_back(i - 2 * len_sub);
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}
