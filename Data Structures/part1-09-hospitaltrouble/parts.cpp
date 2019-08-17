//
// Created by student on 19.11.2018.
// Korolev Dmitry bse173
//

#include <iostream>
#include "parts.h"

    /// writes down in the console info about subparts
    /// of this Part
    void Part::describe()
    {
        // in all cases i right name
        std::cout << "Part " << this->name << " subparts are: " << std::endl;

        Childs::iterator it = subparts.begin();

        // there are some childs - go list them
        if (it != subparts.end())
            for (it; it != subparts.end(); ++it)
                std::cout << it->second << " " << it->first->name << std::endl;
        else
            // in other case we just write that there are no subparts
            std::cout << "It has no subparts." << std::endl;
    }

    /// counts how many p-passed parts are in THIS part
    /// returns int - amount
    int Part::count_howmany(Part const *p)
    {
        // when reached myself
        if (this == p)
            return 1;

        int amount = 0;

        for (Childs::iterator it = subparts.begin(); it != subparts.end(); ++it)
        {
            amount += it->second * it->first->count_howmany(p);
        }

        return amount;
    }

    /// returns int - amount of inner parts-P in this part.
    /// But finds it in another way - using field Part* parent
    /// so looking up in this method
    int Part::count_howmanyUp(Part *p)
    {
        // here this - howmany of this
        // and p - IN Which (vars changed with each other)
        // in comparison to count_howmany

        // 1 because we will only multiply values
        int amount = 1;

        Part* dad = p;
        Part* child = p;

        while(dad != this)
        {
            dad = dad->parent;
            amount *= dad->subparts[child];
            child = child->parent;
        }

        return amount;
    }

    /// Method finding Part object by name
    /// creates a new Part and adds it to container if not found
    Part* NameContainer::lookup(std::string const &name)
    {
        Names::iterator it = name_map.find(name);

        if (it != name_map.end())
            return it->second;
        else
        {
            // creating new part, inserting it and returning
            Part* part = new Part(name);
            name_map.insert(std::pair<std::string, Part*>(name, part));
            return part;
        }
    }

    //Добавление элемента в контейнер
    void NameContainer::add_part(std::string const& part, int amount, std::string const& subpart)
    {
        // new part to be added
        //Part* newPart = new Part(part);
        // but we dont need to make another one - if it is already in map
        //TODO so we use lookup (bug was here)
        Part* newPart = lookup(part);

        Part* subp = lookup(subpart);

        // added subp to map of newPart
        // it cant be done in this way cause int is not a pointer??
        //newPart->subparts.find(subp)->second = amount;

        // placing right amount using []search
        newPart->subparts[subp] = amount;

        //TODO *****
        // also adding parent in this method
        subp->parent = newPart;
    }

    // deleting every part object
    NameContainer::~NameContainer()
    {
        Names::iterator it;

        for (it = name_map.begin(); it != name_map.end(); ++it)
            delete it->second;
    }
