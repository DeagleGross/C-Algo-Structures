#include "ReadWriter.h"
#include <ctime>

//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

// for debug
// void showArray(int* arr, int left, int right)
// {
//     std::cout << std::endl << "Array::" << std::endl;
//     for (int i = left; i <= right; ++i)
//         std::cout << arr[i] << " ";
// }

int getPivot(int* arr, int left, int right)
{
    // middle of (left:right)
    //return arr[left + (right - left) / 2];

    // last element as pivot
    return arr[right - 1];

    // random element between left and right
    //return arr[left + rand() % (right - left + 1)];
}

/// Function of participating array and replacing elements
int partition(int*& arr, int left, int right)
{
    // setup of element to participate array
    int pivot = getPivot(arr, left, right);

    int i = left - 1;
    int j = right + 1;

    // forever loop
    while (true)
    {
        // searching leftSide nums > pivot
        do { i++; } while (arr[i] < pivot);
        // searching rightSide nums < pivot
        do { j--; } while (arr[j] > pivot);

        // if sorted using this pivot - go back
        if (i >= j)
            return j;

        std::swap(arr[i], arr[j]);
    }
}

/// Function of launching recurcive funcs
/// made such a decomposition not to ruin
/// already created interface
/// and it is much easier to implement algorithm
/// using signature with passing (int left) and (int right)
void sort(int*& arr, int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);
        sort (arr, left, pivot);
        sort (arr, pivot + 1, right);
    }
}

//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
/// not changing signature
void quickSort(int*& numbers, int array_size)
{
    // launching sort on whole array
    sort (numbers, 0, array_size - 1);
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    quickSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}