////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_element.h"
#include <string>     // std::string, std::stoi

/// Конструктор по умолчанию — нужен контейнерам
    DNAElement::DNAElement(){} // it is just for containers

    /// Конструктор инициализации строкой
    DNAElement::DNAElement(const std::string &description)
    {
        readFromString(description); // as in description of method readfromstring - just launching to create object
    }

    /**
     * \brief Инициализирует объект на основе переданной строки.
     *
     * Fill the fields id, number, base from a description in the format [name][number]:[type] where
     * [id] - a..z
     * [number] - the number of this element in the DNA sequence a1 a2 a3 a4 a5...
     * [base] - biological component of the element (A, C, T or G)
     *
     * So for description "a1:G"
     * name = "a";
     * number = 1;
     * type = "G";
     *
     * Throws invalid_argument if the format is wrong
     *                      or if the type of element is not in [A, C, T, G]
     */
    void DNAElement::readFromString(const std::string &description)
    {
        int amountOfSymbols = 0; // to check only used symbols (test invalid format - ???)
        id = description[0]; // only 1 letter id is allowed in task

        amountOfSymbols++; // for id of DNA

        // because of test - checking that id is in english alphabet:
        if (!(id <= "z" && id >= "a"))
            throw std::invalid_argument("no such id found");

//        if (description[2] == ':')
//            number = std::stoi(description.substr(1, 1)); // if number is 1 symbol
//        else
//            number = std::stoi(description.substr(1, 2)); // if number is 2 symbols

        try
        {
            unsigned int length = description.find(':')-1;
            number = std::stoi(description.substr(1, length)); // remade this method for all different numbers
            amountOfSymbols += length;
        } catch(std::exception ex){
            throw std::invalid_argument("Something wrong with number");
        }


        if (number <= 0)
            throw std::invalid_argument("No number < 0 could be in DNA!");

        char check = description[description.length() - 1];
        if (check != 'A' && check != 'C' && check != 'T' && check != 'G')
            throw std::invalid_argument("No base {" + base + "} found!");
        base = description.substr(description.length()-1, 1);

        amountOfSymbols++;

        if (description.length() != amountOfSymbols + 1)
            throw std::invalid_argument("Not all symbols are okay for format!");
    }
