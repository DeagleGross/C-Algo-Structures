#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

fstream fin;
fstream fout;

/// for debug
void showVector(vector<int>& A)
{
    for (int i = 0; i < A.size(); ++i)
        cout << A[i] << " ";
    cout << endl;
}

void getNext(vector<int> &A, int N)
{
    // sum of all numbers to right of position needed to be decremented
    int sum = A[A.size() - 1];

    // going from pre-last element
    for (int i = A.size() - 2; i >=0; --i)
    {
        if (A[i] != 0)
        {
            // decrement this
            --A[i];
            // rewriting left elems to right
            A[i + 1] = sum + 1;

            // reassignment to zeros
            for (int j  = i + 2; j < A.size(); ++j)
                A[j] = 0;

            // debug
            //showVector(A);
            return;
        }

        // doing it after if not to take the position to decrement
        sum +=  A[i];
    }
}

void writeVector(vector<int>& A)
{
    for(int i = 0; i < A.size() - 1; ++i)
        fout << A[i] << " ";
    fout << A[A.size() - 1];
}

void get(int N, int M, int k)
{
    --k;
    vector<int> A = vector<int>(M);
    A[0] = N;

    while (k != 0){
        // debug
        //cout << "k = " << k << "; ";

        getNext(A, N);
        --k;
    }

    writeVector(A);
}

int main()
{
    int N, M, k;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);

    fin >> N >> M >> k;
    get(N, M, k);

    fout.close();
    fin.close();


    return 0;
}