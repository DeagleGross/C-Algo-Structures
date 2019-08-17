#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

pair<size_t, size_t> getNotOverflowedValues(size_t left, size_t count) {
    size_t tmp = 1;

    for (size_t i = 0; i < count; ++i) {
        size_t last = tmp;
        tmp *= left;

        if (last != tmp / left)
            return make_pair(last, i);
    }

    return make_pair(tmp, count);
}

void writeNum(fstream &fout, size_t xToIncrement, size_t &pos, size_t &m) {
    if (++pos == m)
        fout << xToIncrement + 1;
    else
        fout << xToIncrement + 1 << " ";

    // for debug
//    if (pos - 1 == m)
//        cout << xToIncrement + 1;
//    else
//        cout << xToIncrement + 1<< " ";
}

void get(size_t N, size_t k, size_t m, size_t& pos, fstream& fout)
{
    --k;

    pair<size_t, size_t > p = getNotOverflowedValues(N, m);
    size_t NpowM = p.first; // max N^M that is not overflowed
    size_t M = p.second; // M that is not making N^M overflowed

    /*
     * already writing a lot of numbers "1" that couldn't be reached
     * because of overflow
     */
    for (int i = 0; i < (int)m - (int)M - 1; ++i) {
        if (i < 0)
            continue;
        writeNum(fout, 0, pos, m);
    }

    /*
     * writing down left numbers
     * NpowM is 64 as an example
     */
    for (int i = (int)m - (int)M - 1; i < (int)m; ++i) {
        if (i < 0)
            continue;

        // need to reduce NpowM because it is max if no overflow happened
        if (M == m)
            NpowM /= N;

        // writing k / NpowM nearly in all conditions
        size_t xToWrite = (NpowM == 0) ? N : k / NpowM;
        writeNum(fout, xToWrite, pos, m);

        // reducing k by this amount
        k -= xToWrite * NpowM;

        // we need to reduce NpowM by N even if (M == m) didn't work before
        if (M != m)
            NpowM /= N;
    }
}

int main()
{
    size_t pos = 0;
    size_t M, N, K;

    fstream fin("input.txt", ios::in);
    fstream fout("output.txt", ios::out);

    fin >> N >> M >> K;

    get(N, K, M, pos, fout);
    fout << "\n";
}