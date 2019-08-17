#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

/// returns integer value - maximum number in array
int getMaxNum(const int* numbers, int array_size)
{
    int max = 0;
    for (int i = 0; i < array_size; ++i)
        if (numbers[i] > max)
            max = numbers[i];

    return max;
}

/// returns amount of digits in number according to CC
int getDigitsNum(int number)
{
    int res = 0;
    while(number != 0)
    {
        number /= 256;
        res++;
    }

    return res;
}

/// returns digit by its index from right.
/// getDigitByIndex(12345433219795464, 256) = ...
int getDigitByIndex(int number, int CC_index)
{
    return (number / CC_index % 256);
}

// Функция сортировки подсчетом
// changed signature cause numbers array has to be changed through pointer
void countingSort(int*& numbers, int array_size, int CC_index)
{
    // only 256 digits are existing
    int countSize = 256;

    // creating array-helper of 256 elements
    int* helper = new int[countSize];

    // array that will be returned
    int* result = new int[array_size];

    // restoring values to zero's
    for (int i = 0; i < countSize + 1; ++i)
        helper[i] = 0;

    // incrementing found values by CC_index
    for (int i = 0; i < array_size; ++i)
        helper[getDigitByIndex(numbers[i], CC_index)]++;

    // setting Index values for each array member
    for (int i = 1; i < countSize + 1; ++i)
        helper[i] += helper[i-1];

    // filling result array
    for (int i = array_size-1; i >= 0; --i)
    {
        result[helper[getDigitByIndex(numbers[i], CC_index)]-1] = numbers[i];
        helper[getDigitByIndex(numbers[i], CC_index)]--;
    }

    // deleted temporary arrays
    delete[] numbers;
    delete[] helper;

    // redirectered numbers to result array
    numbers = result;
}

// Функция цифровой сортировки
// changed signature cause numbers array has to be changed through pointer
void radixSort(int*& numbers, int array_size)
{
    int times = getDigitsNum(getMaxNum(numbers, array_size)) + 1;

    // multiplier by 256
    int k = 1;
    for (int i = 0; i < times; ++i)
    {
        countingSort(numbers, array_size, k);
        k *= 256;
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
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
