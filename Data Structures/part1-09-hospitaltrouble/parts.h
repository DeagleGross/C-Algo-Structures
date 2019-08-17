//
// Created by student on 19.11.2018.
// Korolev Dmitry bse173
//

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

//**************** Part ****************
class Part 
{
    // Typedefs made by myself
public:
    /// map-type containing children nodes
    typedef std::map<Part*, int> Childs;

    // name and subparts
public:
    /// name of this part of hospital
    std::string name;
    /// map containing child-objects and values
    Childs subparts;

    //�������������� ������� �� ���������(*), ������� �� �������� �������� ����������!
    //����� �� ������� ��� ������ ����� ������ ����, � ����� ��������� �� parent...
    //Part* parent;
    /// pointer to previous (parent) object
    Part* parent;

public:

    /// returns int - amount of inner parts-P in this part.
    /// But finds it in another way - using field Part* parent
    /// so looking up in this method
    int count_howmanyUp(Part *p);

    Part(std::string const& n) :
    name(n), parent(nullptr)
    {};

    /// writes down in the console info about subparts
    /// of this Part
    void describe();

    /// counts how many p-passed parts are in THIS part
    /// returns int - amount
    int count_howmany(Part const* p);
};

//**************** NameContainer ****************
class NameContainer  
{
private:
    typedef std::map<std::string, Part*> Names;
private:
    Names name_map;

public:
    //����������� �� ���������
    NameContainer() {};

    //����� �� ��� ����������?
    ~NameContainer();

    //����� ������ �����
    Part* lookup(std::string const &name);

    //���������� �������� � ���������
    void add_part(std::string const &x, int amount, std::string const &y);
};

#endif
