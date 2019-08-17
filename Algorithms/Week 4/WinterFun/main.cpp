#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных методов для решения задачи.
//Рекомендуется использовать имеющиеся классы Student и Ski для решения задачи.

//// to debug
//void showSkis(Ski* arr, int left, int right)
//{
//    std::cout << "Skis: (left=" << left << ";right=" << right << ")" << std::endl;
//
//    for (int i = left; i < right + 1; ++i)
//    {
//        std::cout << arr[i].getLength() << " ";
//    }
//
//    std::cout << std::endl;
//}
//
//// to debug
//void showStud(Student* arr, int left, int right)
//{
//    std::cout << "Students: (left=" << left << ";right=" << right << ")" << std::endl;
//
//    for (int i = left; i < right + 1; ++i)
//    {
//        std::cout << arr[i].getLength() << " ";
//    }
//
//    std::cout << std::endl;
//}

/// sorts both students and skis arrays by .id fields
/// sorting just by studs.id and making the same swaps in skis array
/// because we need only sorted studs.id, not skis.id
void sharedQuickSort(Student* students, Ski* skis, int left, int right)
{
    if(left >= right)
        return;

    // pivot element
    int pivot = students[(left + right) / 2].id;

    int l = left;
    int r = right;

    while(l < r)
    {
        while(students[l].id < pivot)
            l++;

        while(students[r].id > pivot)
            r--;

        if(l <= r)
        {
            // swaping in both arrays!
            std::swap(students[l], students[r]);
            std::swap(skis[l], skis[r]);

            l++;
            r--;
        }
    }

    // recursive launches of function
    if(left < r)
        sharedQuickSort(students, skis, left, r);
    if(l < right)
        sharedQuickSort(students, skis, l, right);
}

/// returns index of found RIGHT SKI for chosen STUDENT
/// NOTICE: L and R are passed with "&" so -> returned with final values
int winterSortSkis(Student pivot, Ski* skis, int& l, int& r)
{
    int goodSkiPos = 0;

    do
    {
        while (compare(pivot, skis[l]) == -1)
            ++l;
        while (compare(pivot, skis[r]) == 1)
            --r;

        if (l <= r) {
            std::swap(skis[l], skis[r]);

            /* We need to remember position
             * So it is easy not to use 3-way-quicksort
             * with having index in middle - the right one
             *
             * but easy way is to check what we are swapping
             * if it is right ski - remember index
             */

            if(compare(pivot, skis[l]) == 0)
                goodSkiPos = l;
            if(compare(pivot, skis[r]) == 0)
                goodSkiPos = r;

            ++l;
            --r;
        }

    } while (l <= r);

    return goodSkiPos;
}

/// returns index of found RIGHT STUDENT for chosen SKI
/// NOTICE: L and R are passed with "&" so -> returned with final values
int winterSortStud(Ski pivot, Student* students, int& l, int& r)
{
       int goodStudPos = 0;

    do
    {
        while (compare(students[l], pivot) == 1)
            ++l;
        while (compare(students[r], pivot) == -1)
            --r;

        if (l <= r) {
            std::swap(students[l], students[r]);

            /* We need to remember position
             * So it is easy not to use 3-way-quicksort
             * with having index in middle - the right one
             *
             * but easy way is to check what we are swapping
             * if it is right student - remember index
             */

            if (compare(students[l], pivot) == 0)
                goodStudPos = l;
            if (compare(students[r], pivot) == 0)
                goodStudPos = r;

            ++l;
            --r;
        }
    } while (l <= r);

    return goodStudPos;
}

/* Sorting is done in such a way:
 * 1) taking middle ski [(left + right) / 2]
 *
 * 2) sorting all students according to that ski
 *      ( smaller - to left, bigger - to right, suitable - somewhere between)
 *
 * 3) taking that student and doing the same with skis
 *
 * 4) after that controlling such situation: did indexes match?
 *      swapping som elements to make indexes match (goodSki == goodStud)
 *
 * 5) doing recursive launch as always in quickSort
 */
void winterQuickSort(Student *students, Ski *skis, int left, int right)
{
    // doing sorting of student by the pivot ski
    // choosing the middle one in the array
    int l_stud = left;
    int r_stud = right;
    int goodStudPos = winterSortStud(skis[(left + right) / 2], students, l_stud, r_stud);

    // doing sorting of skis by the chosen Stud
    int l_ski = left;
    int r_ski = right;
    int goodSkiPos = winterSortSkis(students[goodStudPos], skis, l_ski, r_ski);

    // swapping for indexes match
    if(r_stud < r_ski)
        std::swap(skis[r_ski], skis[goodSkiPos]);
    if(r_stud > r_ski)
        std::swap(students[r_stud--], students[goodStudPos]);
    if(l_stud > l_ski)
        std::swap(skis[l_ski], skis[goodSkiPos]);
    if(l_stud < l_ski)
        std::swap(students[l_stud++], students[goodStudPos]);

    // launching recursion
    if (left < r_stud)
        winterQuickSort(students, skis, left, r_stud);
    if (l_stud < right)
        winterQuickSort(students, skis, l_stud, right);
}

//Задача - реализовать этот метод.
// Ответ должен быть упорядочен по возрастанию
// номеров студентов(!), то есть их id.
//Ответы должны быть в этих же массивах.
void findPairs(Student* students, Ski* skis, int n)
{
    winterQuickSort(students, skis, 0, n - 1);
    sharedQuickSort(students, skis, 0, n - 1);
};

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}
