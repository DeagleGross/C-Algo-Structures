#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

//Основная задача - реализовать данный метод
//Результат поместить в переменную res, она как раз доступна для изменения
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getBorders(string &s, string& res)
{
    // genius contest task !
    // i can not use array of SUBSTRINGS because it is useless
    // maybe u wanted to make task with all substring borders, not string borders ???

    int len = s.length();
    for (int i = 1; i < len; ++i)
        res += (s.substr(0, i) == s.substr(len - i, i)) ? s.substr(0, i) + "\n" : "";
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string input;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, input);
        fin.close();
    }

    getBorders(input, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
