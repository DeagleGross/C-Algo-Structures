#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

/// returns {left}/{right} child in array (INDEX). +1 is made because starting from zero
int getLeft(int i) { return 2*i + 1; }
int getRight(int i) { return 2*i + 2; }

/// standart HEAPIFY function for heapSort algorithm
void heapify(int*& arr, int i, int size)
{
    // setting vars
    int left = getLeft(i);
    int right = getRight(i);
    int idOfMax;

    if (left < size && arr[left] > arr[i])
        idOfMax = left;
    else
        idOfMax = i;

    if (right < size && arr[right] > arr[idOfMax])
        idOfMax = right;

    if (idOfMax != i)
    {
        // using std::swap because it is easy :)
        std::swap(arr[i], arr[idOfMax]);
        heapify(arr, idOfMax, size);
    }
}

/// heap is builded from a passed array of ints
void heapBuild(int*& arr, int n)
{
    // here n doesnt change cause no sorting is done
    // only building heap (again n/2 -1!!! cause of zero)
    for (int i = n/2 -1; i >= 0; i--)
        heapify(arr, i, n);
}

//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapSort(int*& numbers, int array_size)
{
    int rootNum = 0;
    heapBuild(numbers, array_size);

    // from last leaf to 0 extract num and call heapify
    for (int i = array_size-1; i >= 0; --i)
    {
        // using std::swap for replacing positions
        std::swap(numbers[rootNum], numbers[i]);

        // calling heapify and reducing size of heap
        heapify(numbers, rootNum, i);
    }
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
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}