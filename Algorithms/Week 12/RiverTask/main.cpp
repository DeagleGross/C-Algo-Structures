#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string& riverMap)
{
    unsigned int n = riverMap.length();

	// [0][i] - amount pereprav to be on i pos on LEFT
	// [1][i] - amount pereprav to be on i pos on RIGHT
	// x1 x2 x3 x4 ...
	// y1 y2 y3 y4 ...
	vector<vector<int>> roads = vector<vector<int>>(2, vector<int>(n + 1, INT32_MAX));

    // [0][0] = 0 as starting point
    // [1][0] = 1 as LEFT + go to RIGHT road
	roads[0][0] = 0;
    roads[1][0] = 1;

    for (int i = 0; i < n; ++i)
    {
        switch (riverMap[i])
        {
            case 'L':
            {
                // on LEFT: from left + 1 or from right with river
                roads[0][i + 1] = min(roads[0][i] + 1, roads[1][i] + 1);
                // on RIGHT: from right to right without using river or from left + river
                roads[1][i + 1] = min(roads[1][i], roads[0][i] + 1); // mb + 2 ????????????????????????
                break;
            }

            case 'R':
            {
                // on LEFT: from left or from right to left
                roads[0][i + 1] = min(roads[0][i], roads[1][i] + 1);
                // on RIGHT: from right using pereprava + from left using river
                roads[1][i + 1] = min(roads[1][i] + 1, roads[0][i] + 1);
                break;
            }

            case 'B':
            {
                // on LEFT: from left + 1 or from right + 2
                roads[0][i + 1] = min(roads[0][i] + 1, roads[1][i] + 2);
                // on RIGHT: from left + 2 or from right + 1
                roads[1][i + 1] = min(roads[1][i] + 1, roads[0][i] + 2);
                break;
            }

            default: { throw exception(); }
        }
    }

    return roads[1][n];
}


int main()
{
	string riverMap;
	int res;
	
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, riverMap);
		fin.close();
	}
	
	res = countMaxCross(riverMap);
	
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();
	
	return 0;
}
