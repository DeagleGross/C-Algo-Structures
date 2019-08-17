#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int getResult(int N, int A, int B, int C)
{
    int res = 1;
    vector<int> floors = vector<int>(N+1, -1);
    floors[1] = 1;

    for (int i = 2; i <= N; ++i)
    {
        // if can visit from -A, -B or -C level
        // placing floors[i] != -1 and incrementing res
        if (i - A >= 1 && floors[i - A] != -1)
        {
            floors[i] = 1;
            ++res;
            continue;
        }

        if (i - B >= 1 && floors[i - B] != -1)
        {
            floors[i] = 1;
            ++res;
            continue;
        }

        if (i - C >= 1 && floors[i - C] != -1)
        {
            floors[i] = 1;
            ++res;
            continue;
        }
    }

    return res;
}

int main()
{
    int N;
    int A, B, C;

    int res;

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> N;
        fin >> A >> B >> C;

        fin.close();
    }

    res = getResult(N, A, B, C);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}