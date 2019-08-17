// ----------------------------------------------------------------
/*
    КДЗ по дисциплине Алгоритмы и структуры данных, 2018-2019 уч.год
    Королев Дмитрий Павлович, группа БПИ-173(1), дата (30.03.2019)
    IDE CLion, состав проекта (файлы *.cpp и *.h)

    Структура:
    ----------
    main.cpp - основной файл проведения эксперимента
    --
    EfimDinitz.h
    FordFulkerson.h --> Классы запуска соответствующих алгоритмов
    EdmondsKarp.h
    --
    ConstValues.h - помощник выгрузки файлов
    Debugger.h - помощник для вывода промежуточных данных в консоль
    AlgoHelper.h - помощник для создания нового или получения существующего истока\стока графа
    ReadWriter.h - помощник для получения графов в виде матриц смежности

    Сделано:
    -----------
    + Алгоритм Форда-Фалкерсона
    + Алгоритм Эдмондса-Карпа
    + Алгоритм Ефима-Динница
    - отчет
    - эксперимент


*/
// ----------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>

#include "EdmondsKarp.h"
#include "FordFulkerson.h"
#include "EfimDinitz.h"

#include "ConstValues.h"
#include "ReadWriter.h"
#include "Debugger.h"

using namespace std;

ReadWriter readWriter;
DebugHelper debugHelper;
ConstValues constValues = ConstValues();

EdmondsKarp edmondsKarp;
FordFulkerson fordFulkerson;
EfimDinitz efimDinitz;

long long getMiddleTime(vector<long long>& times)
{
    if (times.size() == 1)
        return times[0];

    int amount = times.size();
    long long res = 0;

    // ignoring first one
    for (int i = 1; i < amount; ++i)
        res += times[i];

    res /= (amount - 1);

    return res;
}

void showExperiment_Fulkerson(string message, vector<string> strings)
{
    int amountOfTests = fordFulkerson.getAmountOfTests();

    vector<long long> times = vector<long long>();
    long long time;

    int flow = -1;
    string path;
    string subPath;
    string csv = fordFulkerson.getCSVToWrite();

    vector<int> nums = constValues.getNumAmount();

    cout << message << "\n";
    for (int i = 0; i < nums.size(); ++i)
    {
        vector<vector<int>> matrix;

        cout << i+1 << ") " ;
        cout << strings[i] << " ";
        cout << "number of input nodes: " << nums[i] << "; " << endl;
        for (int j = 0; j < amountOfTests; ++j)
        {
            matrix = readWriter.getMatrixFromFile(nums[i], strings[i]);
            flow = fordFulkerson.algorithm(matrix, time);
            cout << "\t test " << j+1 << ") Flow is " << flow << ";";
            times.push_back(time);
            cout << "\t Time wasted (ns): " << time << endl;
            if (time > 200000000000)
                break;
        }

        subPath = strings[i].substr(9, strings[i].length() - 9);
        path = fordFulkerson.getPathToWrite() + subPath;
        time = getMiddleTime(times);
        cout << "time = " << time << endl;
        readWriter.writeValues(csv, path, time, matrix, flow);
    }
}

void showExperiment_Edmonds(string message, vector<string> strings)
{
    int amountOfTests = edmondsKarp.getAmountOfTests();

    vector<long long> times = vector<long long>();
    long long time;
    int flow = -1;

    string path;
    string subPath;
    string csv = edmondsKarp.getCSVToWrite();

    vector<int> nums = constValues.getNumAmount();

    cout << message << "\n";
    for (int i = 0; i < nums.size(); ++i)
    {
        vector<vector<int>> matrix;

        cout << i+1 << ") " ;
        cout << strings[i] << " ";
        cout << "number of input nodes: " << nums[i] << "; " << endl;
        for (int j = 0; j < amountOfTests; ++j)
        {
            matrix = readWriter.getMatrixFromFile(nums[i], strings[i]);
            flow = edmondsKarp.algorithm(matrix, time);
            cout << "\t test " << j+1 << ") Flow is " << flow << ";";
            times.push_back(time);
            cout << "\t Time wasted (ns): " << time << endl;
            if (time > 200000000000)
                break;
        }

        subPath = strings[i].substr(9, strings[i].length() - 9);
        path = edmondsKarp.getPathToWrite() + subPath;
        time = getMiddleTime(times);
        cout << "time = " << time << endl;
        readWriter.writeValues(csv, path, time, matrix, flow);
    }
}

void showExperiment_Dinitz(string message, vector<string> strings)
{
    int amountOfTests = efimDinitz.getAmountOfTests();

    vector<long long> times = vector<long long>();
    long long time;
    int flow = -1;

    string path;
    string subPath;
    string csv = efimDinitz.getCSVToWrite();

    vector<int> nums = constValues.getNumAmount();

    cout << message << "\n";
    for (int i = 0; i < nums.size(); ++i)
    {
        vector<vector<int>> matrix;

        cout << i+1 << ") " ;
        cout << strings[i] << " ";
        cout << "number of input nodes: " << nums[i] << "; " << endl;
        for (int j = 0; j < amountOfTests; ++j)
        {
            matrix = readWriter.getMatrixFromFile(nums[i], strings[i]);
            flow = efimDinitz.algorithm(matrix, time);
            cout << "\t test " << j+1 << ") Flow is " << flow << ";";
            times.push_back(time);
            cout << "\t Time wasted (ns): " << time << endl;
            if (time > 200000000000)
                break;
        }

        subPath = strings[i].substr(9, strings[i].length() - 9);
        path = efimDinitz.getPathToWrite() + subPath;
        time = getMiddleTime(times);
        cout << "time = " << time << endl;
        readWriter.writeValues(csv, path, time, matrix, flow);
    }
}

int main()
{
    showExperiment_Fulkerson("Fulkerson - rarefied", constValues.getRarefiedInputFiles());
    showExperiment_Fulkerson("Fulkerson - medium", constValues.getMediumInputFiles());
    showExperiment_Fulkerson("Fulkerson - tight", constValues.getTightInputFiles());
    showExperiment_Fulkerson("Fulkerson - disco", constValues.getDiscoInputFiles());

    showExperiment_Edmonds("Edmonds - rarefied", constValues.getRarefiedInputFiles());
    showExperiment_Edmonds("Edmonds - medium", constValues.getMediumInputFiles());
    showExperiment_Edmonds("Edmonds - tight", constValues.getTightInputFiles());
    showExperiment_Edmonds("Edmonds - disco", constValues.getDiscoInputFiles());

    showExperiment_Dinitz("Dinitz - rarefied", constValues.getRarefiedInputFiles());
    showExperiment_Dinitz("Dinitz - medium", constValues.getMediumInputFiles());
    showExperiment_Dinitz("Dinitz - tight", constValues.getTightInputFiles());
    showExperiment_Dinitz("Dinitz - disco", constValues.getDiscoInputFiles());

    return 0;
}