#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

// to watch how it is done
//        std::cout << "AGES:: i=" << i << ";  ";
//        for (int j = 0; j < size; ++j)
//            std::cout << ages[j] << " ";
//        std::cout << std::endl;

/// returns {left}/{right} child in array (INDEX). +1 is made because starting from zero
int getLeft(int i) { return 2*i + 1; }
int getRight(int i) { return 2*i + 2; }

void heapify(int*& ages, int i, int size)
{
    // setting vars
    int left = getLeft(i);
    int right = getRight(i);
    int idOfMax;

    if (left < size && ages[left] > ages[i])
        idOfMax = left;
    else
        idOfMax = i;

    if (right < size && ages[right] > ages[idOfMax])
        idOfMax = right;

    if (idOfMax != i)
    {
        // using std::swap because it is easy :)
        std::swap(ages[i], ages[idOfMax]);
        heapify(ages, idOfMax, size);
    }
}

//Функция для построения кучи
//Ответ должен лежать в массиве ages
void heapBuild(int*& ages, int n)
{
    // here n doesnt change cause no sorting is done
    // only building heap (again n/2 -1!!! cause of zero)
    for (int i = n/2 -1; i >= 0; i--)
        heapify(ages, i, n);
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

    //Запуск построения кучи, ответ в том же массиве (brr)
    heapBuild(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
