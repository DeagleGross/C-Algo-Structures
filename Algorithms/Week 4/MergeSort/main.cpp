#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;

// for debug
// void showArray(int* arr, int left, int right)
// {
//     std::cout << "Array:" << std::endl;
//     for (int i = left; i < right; ++i)
//         std::cout << arr[i] << " ";
// }

int* merged;

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
void MergeSort::sort(int *arr, int length)
{
    merged = new int[length];

    divide_and_merge(arr, 0, length);

    delete[] merged;
}

/*  Parameters:
 *  int* arr         - array, which has two sorted sections and needs to merge them to one sorted section.
 *  int start_first  - index of the start of the first sorted section of the array (inclusive). Non-negative integer value.
 *  int start_second - index of the start of the second sorted section of the array (inclusive). Non-negative integer value.
 *  int end          - bound of both sorted sections (exclusive). Strictly positive integer value.
 */
void MergeSort::merge(int* arr, int first, int second, int end)
{
    int p = 0;

    int i = first;
    int j = second;

    while (true)
    {
        merged[p++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

        if (i == second)
        {
            for (int k = j; k < end; ++k)
                merged[p++] = arr[k];
            break;
        }

        if (j == end)
        {
            for (int k = i; k < second; ++k)
                merged[p++] = arr[k];
            break;
        }
    }

    p = 0;
    for (int k = first; k < end; ++k)
        arr[k] = merged[p++];

    //delete[] merged;
}

/* Parameters:
 *  int* arr  - array to sort.
 *  int left  - left bound (inclusive). Non-negative integer value.
 *  int right - right bound (exclusive). Strictly positive integer value.
 */
void MergeSort::divide_and_merge(int *arr, int left, int right)
{
    if (left < right - 1)
    {
        int m = (left + right) / 2;

        divide_and_merge(arr, left, m);

        divide_and_merge(arr, m, right);

        merge(arr, left, m, right);
    }
}

int main()
{
    ReadWriter rw;

    int *brr = nullptr;
    int length;

    //Read data from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}