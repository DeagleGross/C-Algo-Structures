#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

int next(vector<int>& A, int last)
{
    int sum = 0;
    for (int i = last - 2; i >= 0; --i)
    {
        // if a[k-1] > a[k] or left border
        if (A[i - 1] > A[i] || i == 0)
        {
            ++A[i];

            // counting sum
            for (int j = i + 1; j < last; ++j)
                sum += A[j];

            // reassignment
            for (int j = 0; j < sum; ++j)
                A[i + j + 1] = 1;

            // last reinit
            return i + sum;
        }
    }

    // if not found - 1 left
    return 1;
}

void writeVector(vector<int>& A, int last, fstream& fout, bool tab = true)
{
    if (tab)
        fout << "\n";

    for(int i = 0; i < last - 1; ++i)
        fout << A[i] << " ";
    fout << A[last - 1];
}

void get(int N, fstream& fout)
{
    vector<int> A = vector<int>(N, 1);
    int last = N;

    writeVector(A, last, fout, false);

    while(last != 1)
    {
        last = next(A, last);
        writeVector(A, last, fout);
    }
}

int main()
{
    int N;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);

    fin >> N;
    get(N, fout);
    fout << "\n";

    fout.close();
    fin.close();


    return 0;
}