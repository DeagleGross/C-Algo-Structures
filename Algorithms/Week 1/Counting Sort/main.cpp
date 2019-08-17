#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

// Функция сортировки подсчетом
// changed signature cause numbers array has to be changed through pointer
void countingSort(int *&numbers, int array_size)
{
    // Max value in description set to 1000000
    int maxValue = 1000000;

    // creating array-helper of "1000000" elements
    // as said in description  0 <= p <= 1000000
    int* helper = new int[maxValue];

    // array that will be returned
    int* result = new int[array_size];

    // restoring values to zero's
    for (int i = 0; i < maxValue + 1; ++i)
        helper[i] = 0;

    // incrementing found values by index
    for (int i = 0; i < array_size; ++i)
        helper[numbers[i]]++;

    // setting Index values for each array member
    for (int i = 1; i < maxValue + 1; ++i)
        helper[i] += helper[i-1];

    // filling result array
    for (int i = array_size-1; i >= 0; --i)
    {
        result[helper[numbers[i]]-1] = numbers[i];
        helper[numbers[i]] -= 1;
    }

    // deleted temporary arrays
    delete[] numbers;
    delete[] helper;

    // redirectered numbers to result array
    numbers = result;
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
    countingSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
