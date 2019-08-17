#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

/*
 * Only globals saved my speed
 * with such enormous limitations....
 */

size_t pos = 0;
size_t N, k;

fstream fin("input.txt", ios::in);
fstream fout("output.txt", ios::out);

pair<size_t, size_t> getNotOverflowedValues(size_t inputN) {
    size_t N = inputN;
    size_t tmp = 1;

    for (size_t i = 0; i < N; ++i) {
        size_t last = tmp;
        tmp *= inputN;

        // overflow happened
        if (last != tmp / inputN)
            return make_pair(last, i);

        --inputN;
    }

    return make_pair(tmp, N);
}

void writeNum(size_t xToIncrement, size_t& m) {
    if (++pos == m)
        fout << xToIncrement + 1;
    else
        fout << xToIncrement + 1 << " ";

    // for debug
//    if (pos - 1 == m)
//        cout << xToIncrement + 1;
//    else
//        cout << xToIncrement + 1 << " ";
}

void get()
{
    --k;

    pair<size_t, size_t > p = getNotOverflowedValues(N);
    size_t NpowM = p.first; // max N*(N-1)*..*3*2*1 that is not overflowed
    size_t M = p.second; // M that is the position reached. if M = N => no overflow

    /*
     * already writing a lot of numbers "1" that couldn't be reached
     * because of overflow
     */
    for (int i = 0; i < (int)N - (int)M - 1; ++i) {
        if (i < 0)
            continue;
        writeNum(0, N);
    }

    /*
     * writing down left numbers
     * NpowM is 64 as an example
     */
    for (int i = (int)N - (int)M - 1; i < (int)N; ++i) {
        if (i < 0)
            continue;

        // need to reduce NpowM because it is max if no overflow happened
        if (M == N)
            NpowM /= (pos + 1);

        // writing k / NpowM nearly in all conditions
        size_t xToWrite = (NpowM == 0) ? (pos) : k / NpowM;
        writeNum(xToWrite, N);

        // reducing k by this amount
        k -= xToWrite * NpowM;

        // we need to reduce NpowM by N even if (M == m) didn't work before
        if (M != N)
            NpowM /= (pos + 1);
    }
}

int main()
{
    fin >> N >> k;

    get();
    fout << "\n";
}