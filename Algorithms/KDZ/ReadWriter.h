#include <iostream>
#include <fstream>
#include <vector>

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:
    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    void writeValues(std::string CSV,std::string output, long long& time, std::vector<std::vector<int>>& result, int flow)
    {
        fout.open(output, std::ios::out);

        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << time << "\t" << flow << "\n";

        for (int i = 0; i < result.size(); ++i)
        {
            for (int j = 0; j < result.size(); ++j)
            {
                if (result[i][j] == INT32_MAX)
                    fout << "o" << "\t";
                else
                    fout << result[i][j] << "\t";
            }

            fout << "\n";
        }

        fout.close();

        fout.open(CSV, std::ios::app);

        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << to_string(result.size()) << ";" << to_string(time) << "\n";

        fout.close();
    }

    /* Returns matrix from file
     * if file not found - ios_base::failure
     */
    std::vector<std::vector<int>> getMatrixFromFile(int N, std::string input)
    {
        fin.open(input, std::ios::in);

        if (!fin.is_open())
            throw std::ios_base::failure("file not found");

        // initialization of matrix
        std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(N);
        for (int i = 0; i < matrix.size(); ++i)
            matrix[i] = std::vector<int>(N);

        int tmp;

        // reading rows
        for (int i = 0; i < N; ++i)
        {
            // reading columns
            for (int j = 0; j < N; ++j)
            {
                fin >> matrix[i][j];
            }
        }

        fin.close();
        return matrix;
    }
};