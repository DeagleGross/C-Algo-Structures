#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

/// finds a string from filename and tries to insert it in
Dictionary::Dictionary(string filename)
{
    // ADDED LOAD FROM FILE - by string filename

    std::ifstream input(filename);

    if(input.is_open())
    {
        std::string str;

        while(std::getline(input, str))
        {
            insert(str);
        }

        input.close();
    }
}
