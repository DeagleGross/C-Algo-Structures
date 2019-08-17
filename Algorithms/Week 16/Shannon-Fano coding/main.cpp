#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

class ShannonFano
{
private:
    int sum;
    vector<int> nums;
    vector<string> codes;

private:
    // for debug
    void showVector(vector<int> v){
        for (int i : v)
            cout << i << " ";
        cout << endl;
    }

private:
    // left - inclusive
    // right - exclusive
    pair<int,int> getDividePosition(int left, int right, int sum)
    {
        if (left == right - 1)
            return make_pair(-1, -1);

        int E = 0;
        double halfSum = (double)sum / 2;

        for (int i = left; i < right; ++i)
        {
            // condition of coming off the halfsum
            /*
             * ">" to include elem in "3 this->3 1 1 1" case to LEFT part
             * ">=" to include elem in "3 this->3 1 1 1" case to RIGHT part
             */
            if (abs(nums[i] + E - halfSum) >= abs(E - halfSum))
                return make_pair(i - 1, E);
            else
                E += nums[i];
        }
    }

    // left - inclusive
    // div - inclusive in left part, exclusive from right
    // right - exclusive
    void writeCodes(int left, int div, int right)
    {
        for (int i = left; i <= div; ++i)
            codes[i] += '0';
        for (int i = div + 1; i < right; ++i)
            codes[i] += '1';

    }

    // left - inclusive
    // div - inclusive in left part, exclusive from right
    // right - exclusive
    void divide(int left, int div, int right, int sum_left, int sum_right)
    {
        writeCodes(left, div, right);
        pair<int,int> p;

        // left part
        p = getDividePosition(left, div + 1, sum_left);
        if (p.first != -1)
            divide(left, p.first, div + 1, p.second, sum_left - p.second);

        // right part
        p = getDividePosition(div + 1, right, sum_right);
        if (p.first != -1)
            divide(div + 1, p.first, right, p.second, sum_right - p.second);
    }

public:
    ShannonFano()
        : nums(), codes() {
        sum = 0;
    }

    /// main method
    void build()
    {
        int N = nums.size();
        pair<int, int> div_params = getDividePosition(0, N, sum);
        divide(0, div_params.first, N, div_params.second, sum - div_params.second);
    }

    void addChance (int chance)
    {
        nums.push_back(chance);
        sum += chance;
        codes.emplace_back("");
    }

    string get (int i) { return codes[i]; }
};


int main() {

    int n;
    auto * shf = new ShannonFano();

    fstream fin;
    fin.open("input.txt",ios::in);
    if(fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            fin >> x;
            shf->addChance (x);
        }

        fin.close();

        shf->build();

        fstream fout;
        fout.open("output.txt",ios::out);
        for (int i = 0; i < n; i++){
            fout <<shf->get(i) << (i==n-1?"":" ");
        }
        fout.close();

        delete shf;
    }
    return 0;
}