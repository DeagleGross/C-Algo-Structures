////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован linked_list.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    /// returns a chain that has unique type of IDs and rising numbers (example: a1, a2, a3)
    /// it is a chain from pNodeBefore->next to pNodeLast (repeating signature of moveNodesAfter method to use in repairDNA)
    /// in start pNodeLast comes as pNodeBefore->next element
    void findAddableChain(const DNARepairer::NodeDNA* pNodeBefore, DNARepairer::NodeDNA* pNodeLast)
    {
        // if there is no elements to add return
        if(pNodeBefore->next == nullptr)
            return;

        // getting id and number of pNodeLast
        std::string id = pNodeLast->value.id;
        int number = pNodeLast->value.number;

        while (pNodeLast->next != nullptr)
        {
            // checking on = Ids and index of number
            if (pNodeLast->next->value.id != id || pNodeLast->next->value.number != ++number)
                return;
            // going up if chain is okay
            pNodeLast = pNodeLast->next;
        }
    }

    /// returns a node to place chain AFTER it
    DNARepairer::NodeDNA* findNodeToPlaceAfter(int number, DNARepairer::DNAChain* chain)
    {
        // going through the chain
        DNARepairer::NodeDNA* head = chain->getPreHead();

        if (head->next == nullptr) // if chain is empty return nullptr
            return head;

        // if it is last and number is not > of this element we are moving
        while (head->next != nullptr && head->next->value.number < number)
            head = head->next;

        return head;
    }

    /// we have to store goodDNAs in _dnaStorage of dna_repairer
    /// so we transform good sorted values from map in method repairDNA to
    /// this type of storage
    void DNARepairer::reformDNAStorage(Id2DnaMap& dNAmap)
    {
        // firstly we delete all nodes from that storage (so we dont lose memory by replacing ->next fields)
        _dnaStorage.deleteNodes(_dnaStorage.getPreHead(), _dnaStorage.getTailNode());

        // then for each string key of map we add element (in this case - NodeDNA* wrapped in Node<>)
        // to storage (this is a type conversion for typedef's in dna_repair.h)
        for (auto i = ++dNAmap.begin(); i != dNAmap.end(); ++i)
            _dnaStorage.addElementToEnd(*i->second);
    }

    /// forms a map with key=id and value=chain of dna's
    /// and stores it to _dnaStorage
    void DNARepairer::repairDNA()
    {
        // map to store sorted chains
        Id2DnaMap mainStorage = std::map<std::string, DNAChain*>();

        // going through all LinkedList<DNAElement>
        NodeDNAChain* chains = _dnaStorage.getPreHead();

        while(chains->next != nullptr)
        {
            chains = chains->next; // firstly we go to next to skip empty prehead

            // going through all Node<DNAElement> in the list (elements of a string of input)
            NodeDNA* nodes = chains->value.getPreHead();

            while(nodes->next != nullptr)
            {
                // setting first and last for further methods
                NodeDNA* first = nodes;
                NodeDNA* last = nodes->next;

                // finding a chain to add
                // last and first are changed in here
                findAddableChain(first, last);

                // setting new DNAChain if there is no chain for such an id
                if(mainStorage[first->next->value.id] == nullptr)
                    mainStorage[first->next->value.id] = new DNAChain();

                // getting node to put chain after it
                NodeDNA* pNodeToPlaceAfter = findNodeToPlaceAfter(first->next->value.number, mainStorage[first->next->value.id]);

                // paste chain in storage
                mainStorage[first->value.id]->moveNodesAfter(pNodeToPlaceAfter, first, last);

                // "nodes" is changed because it is thrown to methods as a pointer as "first" variable
            }
        }

        // converting map -> ListOfDnaChains (_dnaStorage)
        reformDNAStorage(mainStorage);
    }


    /// Выводит содержимое хранилища цепочек ДНК в стандартный поток вывода.
    void DNARepairer::printDNAStorage()
    {
        printToStream(cout);
    }

    /// Конвертирует dnaChain в строку. (Уже реализовано.)
    string DNARepairer::dnaChainToString(NodeDNAChain* dnaChain)
    {
        stringstream ss;

        NodeDNA* it2 = dnaChain->value.getPreHead();
        while (it2->next != nullptr)
        {
            it2 = it2->next;
            //итерация по списку ДНК

            ss << it2->value.id << "" << it2->value.number << ":";
            ss << it2->value.base << "  ";
        }
        return ss.str();
    }

    /// Выводит содержимое хранилища цепочек ДНК в поток вывода outStream.
    void DNARepairer::printToStream(std::ostream& outStream)
    {
        xi::Node<DNARepairer::DNAChain>* it1 = _dnaStorage.getPreHead();
        while (it1->next != nullptr)
        {
            it1 = it1->next;
            outStream << dnaChainToString(it1) << endl;
        }
    }

    /// Загружает отдельные «куски» цепочек ДНК из текстового файла, имя которого
    /// приходит в качестве параметра.
    /// Если файл не может быть открыт, генерирует исключительную ситуацию \c std::runtime_error.
    void DNARepairer::readFile(const string& filename)
    {
        ifstream fin(filename);

        if (!fin)
            throw std::runtime_error("Could not open file");

        readFromStream(fin);
    }

    /// Загружает отдельные «куски» цепочек ДНК из потока inStream.
    /// Если входной поток не может быть распознан, генерирует исключительную ситуацию \c std::runtime_error.
    void DNARepairer::readFromStream(std::istream& inStream)
    {
        // начинаем с головы
        NodeDNAChain* it = _dnaStorage.getPreHead();

        string line;
        while (getline(inStream, line))
        {
            // Создаем узел ДНК на куче
            NodeDNAChain* pNewNode = new NodeDNAChain;

            //Создаем строковый поток для разбора
            istringstream istr(line);

            string strTmp;
            while (istr >> strTmp)                                  // разбиваем поток на слова
            {
                DNAElement tmpDNAElement(strTmp);                   // каждое слово читаем в DNAElement
                pNewNode->value.addElementToEnd(tmpDNAElement);     // добавляем полученный DNAElement в ДНК
            }
            it->next = pNewNode;
            it = it->next;

        }
    }

    /// Возвращает ссылку на хранилище цепочек ДНК
    DNARepairer::ListOfDNAChains &DNARepairer::getDNAStorage()
    {
        return _dnaStorage;
    }
